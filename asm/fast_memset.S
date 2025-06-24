.globl fast_memset
fast_memset:
    push rdi
    mov rcx, rdx    # size
    mov al, sil     # value in low byte of rsi
    rep stosb
    pop rax         # return original dest
    ret
