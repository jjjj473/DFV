.intel_syntax noprefix
.globl fast_memcpy
fast_memcpy:
    mov rcx, rdx          # byte count
    shr rcx, 5            # number of 32-byte chunks
    jz .remainder
.loop:
    prefetcht0 [rsi+0x80]
    movdqu xmm0, [rsi]
    movdqu xmm1, [rsi+16]
    movdqu [rdi], xmm0
    movdqu [rdi+16], xmm1
    add rsi, 32
    add rdi, 32
    dec rcx
    jnz .loop
.remainder:
    and rdx, 0x1f
    jz .done
.tail:
    movsb
    dec rdx
    jnz .tail
.done:
    ret
