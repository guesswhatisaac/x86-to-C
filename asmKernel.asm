section .text
    bits 64
    default rel
    global dot_product_asm

dot_product_asm:
    xorps xmm0, xmm0

.loop:
    test rcx, rcx
    jz .done

    movsd xmm1, [rdx]
    movsd xmm2, [r8]
    mulsd xmm1, xmm2
    addsd xmm0, xmm1

    add rdx, 8
    add r8, 8
    dec rcx
    jmp .loop

.done:
    movsd [r9], xmm0
    ret
