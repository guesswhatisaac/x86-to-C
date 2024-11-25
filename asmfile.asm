section .text
  bits 64
  default rel
  global dpasm

dpasm:
    ; rcx = n (size of vectors)
    ; rdx = vecA (pointer to vector A)
    ; r8 = vecB (pointer to vector B)
    
    mov rax, 0           
    mov rbx, 0           

    xorps xmm2, xmm2

dot_product:
    ; Compare loop counter (rax) with n (rcx)
    cmp rax, rcx            
    jge done   

    ; Load A[i] into xmm0 and B[i] into xmm1
    movsd xmm0, [rdx + rax*8]  
    movsd xmm1, [r8 + rax*8]   

    ; Multiply A[i] and B[i], store result in xmm0
    mulsd xmm0, xmm1           

    ; Add the result of A[i] * B[i] to xmm2 (accumulator)
    addsd xmm2, xmm0           

    inc rax                   
    jmp dot_product      

done:
    movsd xmm0, xmm2            
    ret
