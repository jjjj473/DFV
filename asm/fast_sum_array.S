.intel_syntax noprefix
.globl fast_sum_array
# unsigned long fast_sum_array(const unsigned int *arr, size_t n)
fast_sum_array:
    xor rax, rax
    test rsi, rsi
    je .ret
    mov rcx, rsi
    shr rcx, 2
    pxor xmm0, xmm0
.loop:
    movdqu xmm1, [rdi]
    paddd xmm0, xmm1
    add rdi, 16
    dec rcx
    jne .loop
    movhlps xmm1, xmm0
    paddd xmm0, xmm1
    pshufd xmm1, xmm0, 0x1
    paddd xmm0, xmm1
    movd eax, xmm0
    and rsi, 3
    jz .tail_end
.tail:
    add eax, dword ptr [rdi]
    add rdi, 4
    dec rsi
    jne .tail
.tail_end:
.ret:
    ret
