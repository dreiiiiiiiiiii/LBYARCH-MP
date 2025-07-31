#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "distance_kernel.h"

#define NUM_TRIALS 30
#define NUM_ELEMENTS 28

// Measures the execution time (in ms) of a kernel function
// kernel: pointer to the kernel function (C or ASM)
// X1, X2, Y1, Y2: input arrays
// Z: output array
// n: number of elements
// Returns: elapsed time in milliseconds
double measure_time(void (*kernel)(float *, float *, float *, float *, float *, uint32_t), float *X1, float *X2, float *Y1, float *Y2, float *Z, uint32_t n) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq); // Get timer frequency
    QueryPerformanceCounter(&start);  // Start timer

    kernel(X1, X2, Y1, Y2, Z, n);    // Run the kernel

    QueryPerformanceCounter(&end);    // End timer
    return (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart; // ms
}

int main() {
    // Number of elements (2^n)
    int n = 1 << NUM_ELEMENTS;

    // Set random seed for different results each run
    srand((unsigned int)time(NULL));

    // Allocate memory for input and output arrays
    float* X1 = (float*)malloc(sizeof(float) * n);
    float* X2 = (float*)malloc(sizeof(float) * n);
    float* Y1 = (float*)malloc(sizeof(float) * n);
    float* Y2 = (float*)malloc(sizeof(float) * n);
    float* Z_c = (float*)malloc(sizeof(float) * n);
    float* Z_asm = (float*)malloc(sizeof(float) * n);

    // Check for allocation failure
    if (!X1 || !X2 || !Y1 || !Y2 || !Z_c || !Z_asm) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize input arrays with random floats in [0, 100)
    for (int i = 0; i < n; i++) {
        X1[i] = (float)rand() / RAND_MAX * 100.0f;
        X2[i] = (float)rand() / RAND_MAX * 100.0f;
        Y1[i] = (float)rand() / RAND_MAX * 100.0f;
        Y2[i] = (float)rand() / RAND_MAX * 100.0f;
    }

    // Run and time the C kernel
    double total_time_c = 0.0, total_time_asm = 0.0;
    for (int trial = 0; trial < NUM_TRIALS; trial++) {
        total_time_c += measure_time(distance_kernel_c, X1, X2, Y1, Y2, Z_c, n);
    }
    for (int trial = 0; trial < NUM_TRIALS; trial++) {
        total_time_asm += measure_time(distance_kernel_asm, X1, X2, Y1, Y2, Z_asm, n);
    }
    double avg_time_c = total_time_c / NUM_TRIALS;
    double avg_time_asm = total_time_asm / NUM_TRIALS;

    // Print the first 10 results and check correctness
    printf("\nFirst 10 results:\n");
    for (int i = 0; i < 10; i++) {
        const char* result;
        if (fabsf(Z_c[i] - Z_asm[i]) < 1e-5) {
            result = "OK";
        } else {
            result = "MISMATCH";
        }
        printf("Z_c[%d] = %f\tZ_asm[%d] = %f\t%s\n", i, Z_c[i], i, Z_asm[i], result);
    }

    // Print timing results
    printf("C kernel average time: %f ms\n", avg_time_c);
    printf("ASM kernel average time: %f ms\n", avg_time_asm);

    // Free allocated memory
    free(X1); free(X2); free(Y1); free(Y2);
    free(Z_c); free(Z_asm);
    return 0;
}