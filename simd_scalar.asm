section .data
    result resq 1          ; result
    X1 resq 2097152        ; X1 array
    Y1 resq 2097152        ; Y1 array
    X3 resq 2097152        ; X3 array
    Y3 resq 2097152        ; Y3 array

section .text
    global calculate_distance

calculate_distance:
    xor rax, rax 
    xor rbx, rbx

.loop:
    cmp rax, rdi
    jge .done

    movq xmm0, [X1 + rax*8]
    movq xmm1, [X3 + rax*8]
    subpd xmm0, xmm1

    movq xmm2, [Y1 + rax*8]
    movq xmm3, [Y3 + rax*8]
    subpd xmm2, xmm3

    ; square of differences
    mulpd xmm0, xmm0       
    mulpd xmm2, xmm2

    ; add squares
    addpd xmm0, xmm2 

    ; square root
    sqrtsd xmm0, xmm0 

    movq [result], xmm0 

    inc rax   
    jmp .loop

.done:
    ret