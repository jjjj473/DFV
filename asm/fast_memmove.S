.intel_syntax noprefix
.globl fast_memmove
# void *fast_memmove(void *dest, const void *src, size_t n)
fast_memmove:
    cmp rdi, rsi
    je .ret
    mov rcx, rdx
    cmp rdi, rsi
    ja .back
.forward:
    rep movsb
    jmp .ret
.back:
    lea rsi, [rsi+rcx-1]
    lea rdi, [rdi+rcx-1]
    std
    rep movsb
    cld
.ret:
    mov rax, rdi
    ret
