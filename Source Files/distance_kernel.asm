section .text

global distance_kernel_asm

distance_kernel_asm:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub rsp, 32

    mov rbx, [rbp + 48]
    mov r10d, [rbp + 56]

    mov r12, rcx
    mov r13, rdx
    mov r14, r8
    mov r15, r9

    xor edi, edi

.loop:
    cmp edi, r10d
    jge .done

    mov eax, edi
    shl eax, 2

    movss xmm0, [r13 + rax]
    movss xmm1, [r12 + rax]
    subss xmm0, xmm1
    movss xmm2, xmm0
    mulss xmm2, xmm0

    movss xmm3, [r15 + rax]
    movss xmm4, [r14 + rax]
    subss xmm3, xmm4
    movss xmm5, xmm3
    mulss xmm5, xmm3

    addss xmm2, xmm5
    sqrtss xmm2, xmm2

    movss [rbx + rax], xmm2

    inc edi
    jmp .loop

.done:
    add rsp, 32
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret
