.intel_syntax noprefix
.globl fast_strcmp
fast_strcmp:
    xor eax, eax
1:
    mov bl, [rdi]
    mov dl, [rsi]
    cmp bl, dl
    jne .diff
    test bl, bl
    je .equal
    inc rdi
    inc rsi
    jmp 1b
.diff:
    movsx eax, bl
    movsx edx, dl
    sub eax, edx
    ret
.equal:
    xor eax, eax
    ret
.section .note.GNU-stack,"",@progbits
