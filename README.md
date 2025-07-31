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
Z_c[0] = 83.365547
Z_c[1] = 55.570717
Z_c[2] = 68.906548
Z_c[3] = 34.974667
Z_c[4] = 27.368090
Z_c[5] = 55.475929
Z_c[6] = 37.107937
Z_c[7] = 49.684017
Z_c[8] = 55.941528
Z_c[9] = 21.878452
```


**ASM Kernel Output**
```text
Z_asm[0] = 83.365547
Z_asm[1] = 55.570717
Z_asm[2] = 68.906548
Z_asm[3] = 34.974667
Z_asm[4] = 27.368090
Z_asm[5] = 55.475929
Z_asm[6] = 37.107937
Z_asm[7] = 49.684017
Z_asm[8] = 55.941528
Z_asm[9] = 21.878452
```


### Timing Results
- **C kernel average time:** 950.426950 ms  
- **ASM kernel average time:** 1307.516027 ms

Despite both kernels producing correct results, the ASM version was slower by approximately 357 ms. This may be due to the compiler’s ability to apply optimizations in the C version that outpace our scalar manual ASM implementation.

