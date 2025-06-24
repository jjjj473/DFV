.intel_syntax noprefix
.globl fast_uppercase
fast_uppercase:
    mov rax, rdi
1:
    mov bl, byte ptr [rax]
    test bl, bl
    je 2f
    cmp bl, 'a'
    jb 3f
    cmp bl, 'z'
    ja 3f
    sub bl, 32
3:
    mov byte ptr [rax], bl
    inc rax
    jmp 1b
2:
    ret
.section .note.GNU-stack,"",@progbits
