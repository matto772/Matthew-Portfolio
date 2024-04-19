BITS 32
section .data
    prompt DB 'Please enter a string.',10,0
    prompt_len EQU $-prompt
    result_true DB 'It is a palindrome.',10,0
    true_len EQU $-result_true
    result_false DB 'It is NOT a palindrome.',10,0
    false_len EQU $-result_false
    
section .text
    global addstr
    global is_palindrome
    global factstr
    global palindrome_check
    extern fact
    extern atoi
    extern is_palindrome_c

addstr:
    push ebp
    mov ebp, esp
    push ebx

    ;calling atoi for parameter 1
    mov eax, [ebp+8]
    push eax
    call atoi
    add esp, 4
    ;save 1st result for adding
    mov ebx, eax

    ;calling atoi for parameter 2
    mov eax, [ebp+12]
    push eax
    call atoi
    add esp, 4

    ;add results
    add eax, ebx

    ;restore and returns
    pop ebx
    mov esp, ebp
    pop ebp
    ret

;is_palindrome function here C -> ASM
is_palindrome:
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi

    ;variables initialized here
    xor ebx, ebx 
    xor esi, esi 

    ; Find the length of the string
    mov edi, dword [ebp+8] ; pointer to the string
    mov ecx, 0 ; Counter for the length 
    mov al, byte [edi+ecx] 

;Loop to find the end of the string for the length
find_end:
    cmp al, 0 
    je compare 
    inc ecx 
    mov al, byte [edi+ecx] 
    jmp find_end 

    ;setup for the comapre loop
    compare:
        dec ecx 
        mov esi, ecx 

        mov ecx, ebx 

        ;compare loop to compare the characters from beginning and end to the middle to see ifthere is a palindrome
        compare_loop:
            cmp ecx, esi 
            jge palindrome 

            mov al, byte [edi+ecx] ;beginning
            mov ah, byte [edi+esi] ;end
            cmp al, ah 

            ; If the characters are not equal the string is not a palindrome
            jne not_palindrome

            inc ecx 
            dec esi 
            jmp compare_loop 

    ; The string is a palindrome
    palindrome:
        mov eax, 1 
        jmp end

    ; The string is not a palindrome
    not_palindrome:
        xor eax, eax 

    end:
        ;Restore registers and return
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp

        ret


factstr:
    push ebp
    mov ebp, esp

    ;getting the num from C driver
    mov eax, [ebp + 8]

    ;converting the string to an int using atoi
    push eax
    call atoi
    add esp, 4

    ;calling the fact function to get the factorial
    push eax
    call fact
    add esp, 4

    ;save and get the result
    pop ebp
    ret

;palidnrome check ASM -> C here
palindrome_check:
    push ebp
    mov ebp, esp

    ;getting the input
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, prompt_len
    int 0x80

    ;making room for the string
    sub esp, 256
    mov esi, esp


    ;reading in the string here
    mov eax, 3
    mov edx, 0
    mov ecx, esi
    mov edx, 256
    int 0x80

    ;calling the is_palindrome C version
    push esi
    call is_palindrome_c
    add esi, 4

    ;echecking the result and printing the right message
    cmp eax, 1
    je yes_palindrome
    jmp no_palindrome

yes_palindrome:
    mov eax, 4
    mov ebx, 1
    mov ecx, result_true
    mov edx, true_len
    int 0x80
    jmp end_check

no_palindrome:
    mov eax, 4
    mov ebx, 1
    mov ecx, result_false
    mov edx, false_len
    int 0x80
    jmp end_check

end_check:
    mov esp, ebp
    pop ebp
    ret


























































