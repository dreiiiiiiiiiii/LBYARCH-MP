; distance_kernel_asm.asm

; This file implements the distance_kernel_asm function in NASM x86-64 assembly.
; It computes the Euclidean distance for each element:
;   Z[i] = sqrt((X2[i] - X1[i])^2 + (Y2[i] - Y1[i])^2)
; Arguments follow the Windows x64 calling convention:
;   RCX = X1 (float*)
;   RDX = X2 (float*)
;   R8  = Y1 (float*)
;   R9  = Y2 (float*)
;   [RSP+40] = Z (float*)
;   [RSP+48] = n (uint32_t)

section .text

global distance_kernel_asm

distance_kernel_asm:
    ; Prologue: preserve non-volatile registers and set up stack frame
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub rsp, 32                ; shadow space (Windows x64 ABI)

    ; Retrieve Z and n from the stack using correct offsets after pushes
    mov rbx, [rbp + 0x28]        ; rbx = Z (5th argument)
    mov r10d, [rbp + 0x30]       ; r10d = n (6th argument, 32-bit)

    ; Save input array pointers to callee-saved registers for easy access
    mov r12, rcx               ; r12 = X1
    mov r13, rdx               ; r13 = X2
    mov r14, r8                ; r14 = Y1
    mov r15, r9                ; r15 = Y2

    xor edi, edi               ; edi = i = 0 (loop counter)

.loop:
    cmp edi, r10d              ; if (i >= n) break
    jge .done

    mov eax, edi               ; eax = i
    shl eax, 2                 ; eax = i * 4 (float offset)

    ; Compute dx = X2[i] - X1[i]
    movss xmm0, [r13 + rax]    ; xmm0 = X2[i]
    movss xmm1, [r12 + rax]    ; xmm1 = X1[i]
    subss xmm0, xmm1           ; xmm0 = X2[i] - X1[i]
    movss xmm2, xmm0           ; xmm2 = dx
    mulss xmm2, xmm0           ; xmm2 = dx^2

    ; Compute dy = Y2[i] - Y1[i]
    movss xmm3, [r15 + rax]    ; xmm3 = Y2[i]
    movss xmm4, [r14 + rax]    ; xmm4 = Y1[i]
    subss xmm3, xmm4           ; xmm3 = Y2[i] - Y1[i]
    movss xmm5, xmm3           ; xmm5 = dy
    mulss xmm5, xmm3           ; xmm5 = dy^2

    ; Add dx^2 + dy^2 and take sqrt
    addss xmm2, xmm5           ; xmm2 = dx^2 + dy^2
    sqrtss xmm2, xmm2          ; xmm2 = sqrt(dx^2 + dy^2)

    ; Store result in Z[i]
    movss [rbx + rax], xmm2    ; Z[i] = result

    inc edi                    ; i++
    jmp .loop                  ; repeat loop

.done:
    add rsp, 32                ; Restore stack pointer
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp                    ; Restore base pointer
    ret                        ; Return to caller
