
section .bss
    IntBuffer resb 100
    IntBufferPos resb 8

section .data 
    newline db 0xa
    doubleQuote db 0x22


%macro printInt 1
    mov rax, %1
    mov rcx, IntBuffer
    mov [IntBufferPos], rcx
    %%storeLoop:
        mov rdx, 0
        mov rbx, 10
        div rbx
        push rax
        add rdx, 48
        mov [rcx] ,dl
        mov rcx, [IntBufferPos]
        inc rcx 
        mov [IntBufferPos], rcx

        pop rax
        cmp rax,0
        jne %%storeLoop
    %%printLoop:
        mov rcx, [IntBufferPos]
        mov rax, 1
        mov rdi, 1
        mov rsi, rcx
        mov rdx ,1 
        syscall

        mov rcx, [IntBufferPos]
        dec rcx 
        mov [IntBufferPos], rcx

        cmp rcx, IntBuffer
        jge %%printLoop 
%endmacro

%macro printString 1
   mov rax , %1
   mov rbx,0
   %%cloop:
        inc rax
        inc rbx
        mov cl, [rax]
        cmp cl, 0
        jne %%cloop
    mov rax, 1
    mov rdi, 1
    pop rsi
    mov rdx, rbx
    ret
%endmacro

%macro endl 0
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx ,1 
    syscall
%endmacro

%macro exit 0
    mov rax,60
    mov rdi,0
    syscall
%endmacro


%macro copyStack 1
    pop %1
    push %1
%endmacro

%macro printDoubleQuote 0
    push rcx 
    push rdx 
    push rsi
    
    mov rdi , 1
    mov rax , 1
    mov rdx , 1
    mov rsi , doubleQuote
    syscall

    pop rsi 
    pop rdx 
    pop rcx
%endmacro