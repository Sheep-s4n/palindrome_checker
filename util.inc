section .text
global reverse
reverse:
    ; save len/2 + 1 in the stack
    mov rdx , 0
    mov rbx , 2
    div rbx 
    dec rax 
    push rax
    ; save start of string
    mov rsi, rdi
    ; repne checks also for ecx to be 0
    xor ecx, ecx
    not ecx
    ; find end of string
    xor al, al
    repne scasb
    dec rdi
    dec rdi
    ; switch characters
  .xchg_loop:
    mov al, [rsi]
    xchg al, [rdi]
    mov [rsi], al
    inc rsi
    dec rdi
    cmp rsi, rdi
    jle .xchg_loop
    ;set rdi to string beginning 
    pop rax 
    sub rdi , rax 
   ret


strcopy:        
    copy_loop:
        mov dl, byte [rdi]   ; Load character from original string
        mov [rsi], dl       ; Store character in new string
        inc rsi             ; Increment new string pointer
        inc rdi             ; Increment original string pointer
        ; Check if we have reached the end of the original string
        cmp dl, 0           ; Check if it is the null terminator
        jne copy_loop       ; If not, continue copying
        
    ret 

strlen: xor   ecx, ecx; ecx = 0

s_loop: cmp   byte [rdi], 0; check if it is the string end
		je    return
		inc   rdi
		inc   rax
		jmp   s_loop

return: ret