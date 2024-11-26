section .text
    bits 64
    default rel
    global dot_product_asm

dot_product_asm:
    ; Arguments:
    ; rcx = n (size of vectors)
    ; rdx = vecA (pointer to vector A)
    ; r8  = vecB (pointer to vector B)
    ; r9  = sdot (pointer to the result)

    ; Initialize the accumulator to 0
    xorps xmm0, xmm0       ; xmm0 will accumulate the dot product

.loop:
    ; Check if all elements are processed
    test rcx, rcx
    jz .done

    ; Load A[i] and B[i], multiply and accumulate
    movsd xmm1, [rdx]      ; Load A[i] into xmm1
    movsd xmm2, [r8]       ; Load B[i] into xmm2
    mulsd xmm1, xmm2       ; xmm1 = A[i] * B[i]
    addsd xmm0, xmm1       ; Accumulate in xmm0

    ; Move to the next elements
    add rdx, 8             ; Advance pointer for A
    add r8, 8              ; Advance pointer for B
    dec rcx                ; Decrement counter
    jmp .loop

.done:
    ; Store the final result in the location pointed by r9
    movsd [r9], xmm0
    ret
