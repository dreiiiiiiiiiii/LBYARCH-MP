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
Z_c[0] = 63.142025
Z_c[1] = 66.793571
Z_c[2] = 77.854309
Z_c[3] = 52.520252
Z_c[4] = 22.493546
Z_c[5] = 73.571793
Z_c[6] = 35.335808
Z_c[7] = 60.257801
Z_c[8] = 23.765934
Z_c[9] = 43.021446
```


**ASM Kernel Output**
```text
Z_asm[0] = 63.142025
Z_asm[1] = 66.793571
Z_asm[2] = 77.854309
Z_asm[3] = 52.520252
Z_asm[4] = 22.493546
Z_asm[5] = 73.571793
Z_asm[6] = 35.335808
Z_asm[7] = 60.257801
Z_asm[8] = 23.765934
Z_asm[9] = 43.021446
```


### Timing Results
- **C kernel average time:** 1110.471353 ms 
- **ASM kernel average time:** 1351.300313 ms

Despite both kernels producing correct results, the ASM version was slower by approximately 240.82896 ms. This may be due to the compiler’s ability to apply optimizations in the C version that outpace our scalar manual ASM implementation.

