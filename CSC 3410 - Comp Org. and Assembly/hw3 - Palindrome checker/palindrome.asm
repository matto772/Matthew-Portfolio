BITS 32

section .data
    prompt DB 'Please enter a string.',10,0
    prompt_len EQU $-prompt
    palindrome DB 'It is a palindrome.',10,0
    palindrome_len EQU $-palindrome
    not_palindrome DB 'It is NOT a palindrome.',10,0
    not_palindrome_len EQU $-not_palindrome

section .bss
    buffer resb 2064

section .text 
    global _start

_start:
    ;prompting the user here and looping it until the user hits a return (10) to exit
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, prompt_len
    int 0x80
    
    input_loop:
    ;reading in the string here
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 2064
    int 0x80

    ;checking if the user hit return here to exit
    cmp BYTE [buffer], 10
    je exit

    ;calling is_palindrome function here
    dec eax
    dec eax
    push eax
    push buffer
    call is_palindrome

    ;printing the result based on the return of is_palindrome
    cmp eax, 1
    je yes_palindrome

;below is for outputting the results
no_palindrome:
    mov eax, 4
    mov ebx, 1
    mov ecx, not_palindrome
    mov edx, not_palindrome_len
    int 0x80
    jmp _start

yes_palindrome:
    mov eax, 4
    mov ebx, 1
    mov ecx, palindrome
    mov edx, palindrome_len
    int 0x80
    jmp _start

;nicely putting an exit here
exit:
    mov eax, 1
    xor ebx, ebx
    int 0x80

;is_palindrome function here
is_palindrome:
    push ebp
    mov ebp, esp
    ;getting parameters
    mov ecx, [ebp+8] ;buffer
    mov edx, [ebp+12] ;len
    
    ;initializing the counter
    xor eax, eax

    ;loop to compare letters from the back and front to check if the given input is a palindrome
    compare_loop:
        ;getting the chars from both ends
        mov bl, byte [ecx+eax]
        mov bh, byte [ecx+edx]

        ;comparing the characters to check whether or not we have a palindrome
        cmp bl, bh
        jne not_equal

        ;increment the counter and decrement len
        inc eax
        dec edx

        ;if the counter is less than or equal to len, keep going
        cmp eax, edx
        jle compare_loop

        ;if all the characters match we have a palindrome
        mov eax, 1
        jmp end_loop

not_equal:
    xor eax, eax
    
end_loop:
    pop ebp
    ret



