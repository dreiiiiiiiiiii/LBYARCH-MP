#ifndef DISTANCE_KERNEL_H
#define DISTANCE_KERNEL_H

#include <stdint.h>

void distance_kernel_c(float *X1, float *X2, float *Y1, float *Y2, float *Z, uint32_t n);
void distance_kernel_asm(float *X1, float *X2, float *Y1, float *Y2, float *Z, uint32_t n);

#endif
