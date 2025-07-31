# LBYARCH MP2: Euclidean Distance Kernel in C and x86-64 Assembly

## Members
- Soper, Heather Lynn  
- Tan, Anthony Andrei

## Description

This project computes 2D Euclidean distances using:

- A **C implementation**
- An **x86-64 assembly implementation** using scalar SIMD instructions (`movss`, `subss`, `mulss`, `sqrtss`)

The formula used is:


Z[i] = sqrt((X2[i] - X1[i])² + (Y2[i] - Y1[i])²)


---

## Sample Output (with 2²⁸ vectors)

### First 10 Results

**C Kernel Output**
```text
Z_c[0] = 78.687569
Z_c[1] = 37.376823
Z_c[2] = 46.805424
Z_c[3] = 14.274357
Z_c[4] = 57.501900
Z_c[5] = 67.956902
Z_c[6] = 15.194291
Z_c[7] = 90.467491
Z_c[8] = 71.966949
Z_c[9] = 59.719151
```


**ASM Kernel Output**
```text
Z_asm[0] = 78.687569
Z_asm[1] = 37.376823
Z_asm[2] = 46.805424
Z_asm[3] = 14.274357
Z_asm[4] = 57.501900
Z_asm[5] = 67.956902
Z_asm[6] = 15.194291
Z_asm[7] = 90.467491
Z_asm[8] = 71.966949
Z_asm[9] = 59.719151
```


### Timing Results
- **C kernel average time:** 871.898743 ms 
- **ASM kernel average time:** 1307.540070 ms

Despite both kernels producing correct results, the ASM version was slower by approximately 435.641327 ms. This may be due to the compiler’s ability to apply optimizations in the C version that outpace our scalar manual ASM implementation.

