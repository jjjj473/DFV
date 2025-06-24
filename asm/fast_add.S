.intel_syntax noprefix
.globl fast_add
fast_add:
    mov rax, rdi
    add rax, rsi
    ret
.section .note.GNU-stack,"",@progbits
