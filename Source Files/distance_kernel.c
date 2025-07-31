#include "distance_kernel.h"
#include <math.h>

void distance_kernel_c(float *X1, float *X2, float *Y1, float *Y2, float *Z, uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        float dx = X2[i] - X1[i];
        float dy = Y2[i] - Y1[i];
        Z[i] = sqrtf(dx * dx + dy * dy);
    }
}
