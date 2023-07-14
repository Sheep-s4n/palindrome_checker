sys_write   equ 1
sys_exit    equ 60
sys_stdout  equ 1

%include "util.inc"
%include "lib.inc"

section .data
    error_mesage_nea db "Error (1): not enough argument"
    error_mesage_tma db "Error (2): too much argument"
    palindrome_message db '" is a palindrome'
    no_palindrome_message db '" is not a palindrome'

section .text
    global _start
_start:
    pop rdi ;arg_count
    cmp rdi , 2
    jg _error_exit_tma
    jl _error_exit_nea
    pop rdi ;file name
    pop rdi ;1st arg

    push rdi
    call strlen ;input = rdi/ouput = rax
    pop rsi ; get back i_string
    mov rcx , rax 
    add rdi , rax ; use space after rsi for new string

    cld ; increment each time 
    rep movsb
    ;rdi = need null pointer
    sub rsi , rax;go to string beginning
    push rsi 
    ;don't need rsi

    ;adding null byte to end of string
    mov rbx , rax 
    mov al , 0
    mov rsi , rdi
    stosb
    sub rsi ,rbx;go to string beginning 
    mov rdi , rsi;mov string into rdi

    mov rax , rbx
    push rbx; push strlen   
    call reverse;input = rdi/ouput = rdi

    pop rdx ;strlen
    pop rsi ;original length
    xor rcx , rcx 
    looopie_loop:
    mov al , byte [rsi]
    mov bl , byte [rdi]
    inc rsi 
    inc rdi
    inc rcx
    cmp rcx , rdx ; palindrome if we got to the string end
    je _palindrome
    cmp al , bl ; not palindrome if the two value are not equal
    jne _no_palindrome
    jmp looopie_loop

_palindrome:
printDoubleQuote
sub rsi , rcx 
mov rax , sys_write
mov rdi , sys_stdout
syscall

mov rax , sys_write
mov rdi , sys_stdout
mov rdx , 16
mov rsi , palindrome_message
syscall
exit 

_no_palindrome:
printDoubleQuote
sub rsi , rcx 
mov rax , sys_write
mov rdi , sys_stdout
syscall

mov rax , sys_write
mov rdi , sys_stdout
mov rdx , 20
mov rsi , no_palindrome_message
syscall
exit 

_error_exit_tma:
mov rax , sys_write
mov rdi , sys_stdout
mov rdx , 28
mov rsi , error_mesage_tma
syscall
exit
_error_exit_nea:
mov rax , sys_write
mov rdi , sys_stdout
mov rdx , 30
mov rsi , error_mesage_nea
syscall
exit 
