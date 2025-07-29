#include <xmmintrin.h>
#include "distance_kernel.h"

// distance_kernel_c:
//   Computes the Euclidean distance for each element:
//     Z[i] = sqrt((X2[i] - X1[i])^2 + (Y2[i] - Y1[i])^2)
//   using scalar SSE intrinsics for single-precision floats.
//
// Parameters:
//   X1, X2, Y1, Y2: input arrays of floats (length n)
//   Z: output array of floats (length n)
//   n: number of elements
//
// This function matches the logic and output of the assembly kernel.
void distance_kernel_c(float *X1, float *X2, float *Y1, float *Y2, float *Z, uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        // Load X1[i], X2[i], Y1[i], Y2[i] as scalar floats into SSE registers
        __m128 x1 = _mm_load_ss(&X1[i]);
        __m128 x2 = _mm_load_ss(&X2[i]);
        __m128 y1 = _mm_load_ss(&Y1[i]);
        __m128 y2 = _mm_load_ss(&Y2[i]);

        // Compute dx = X2[i] - X1[i] and dy = Y2[i] - Y1[i]
        __m128 dx = _mm_sub_ss(x2, x1);
        __m128 dy = _mm_sub_ss(y2, y1);

        // Square dx and dy
        __m128 dx2 = _mm_mul_ss(dx, dx);
        __m128 dy2 = _mm_mul_ss(dy, dy);

        // Add squares and compute square root
        __m128 sum = _mm_add_ss(dx2, dy2);
        __m128 dist = _mm_sqrt_ss(sum);

        // Store result in Z[i]
        _mm_store_ss(&Z[i], dist);
    }
}
