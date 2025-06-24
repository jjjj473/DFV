.intel_syntax noprefix
.globl fast_strlen
.section .rodata
zero:
    .quad 0,0
.text
fast_strlen:
    mov rax, rdi
    pxor xmm0, xmm0
.loop:
    movdqu xmm1, [rax]
    pcmpeqb xmm1, xmm0
    pmovmskb ecx, xmm1
    test ecx, ecx
    jnz .found
    add rax, 16
    jmp .loop
.found:
    bsf ecx, ecx
    add rax, rcx
    sub rax, rdi
    ret
.section .note.GNU-stack,"",@progbits
