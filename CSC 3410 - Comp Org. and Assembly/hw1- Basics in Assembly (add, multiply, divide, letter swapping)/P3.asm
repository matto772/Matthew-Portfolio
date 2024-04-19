BITS 32

SECTION .data ; data segment
    userMsg DB 'Please enter a single digit number: ' ; asking the user for the first num
    lenUserMsg EQU $-userMsg
    dispQuotientMsg DB 'The quotient is: '
    lenQuotientMsg EQU $-dispQuotientMsg
    dispRemainderMsg DB 'The remainder is: '
    lenRemainderMsg EQU $-dispRemainderMsg
    starterMsg DB 'The Dividing Program', 0xA
    lenStartMsg EQU $-starterMsg
    newline DB '',0xA
    lenNewLine EQU $-newline

SECTION .bss ; uninitialized data
    num1 RESB 5
    num2 RESB 5
    quotient RESB 5
    remainder RESB 5

SECTION .text
    GLOBAL _start

_start:
    ; starting message
    mov eax, 4
    mov ebx, 1
    mov ecx, starterMsg
    mov edx, lenStartMsg
    int 0x80
    
    ; user prompt for the first number
    mov eax, 4
    mov ebx, 1
    mov ecx, userMsg
    mov edx, lenUserMsg
    int 0x80

    ; read and store the first input
    mov eax, 3
    mov ebx, 0
    mov ecx, num1
    mov edx, 2 
    int 0x80

    ; user prompt for the second number
    mov eax, 4
    mov ebx, 1
    mov ecx, userMsg
    mov edx, lenUserMsg
    int 0x80

    ; read and store the second input
    mov eax, 3
    mov ebx, 0
    mov ecx, num2
    mov edx, 2  
    int 0x80

    ; converting the first number by taking 48 away
    mov al, [num1]
    sub al, 48
    mov [num1], al

    ; converting the second number by taking 48 away
    mov al, [num2]
    sub al, 48
    mov [num2], al

    ;zero out AH and AL here
    xor ah, ah
    xor al, al

    ; divide the numbers here
    mov al, [num1]
    idiv byte [num2]
    mov [quotient], al
    mov [remainder], ah

    ; converting the quotient and remainder back to strings by adding 48 back
    add byte [quotient], 48
    add byte [remainder], 48

    ; printing the quotient message and quotient
    mov eax, 4
    mov ebx, 1
    mov ecx, dispQuotientMsg
    mov edx, lenQuotientMsg
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, quotient
    mov edx, 1
    int 0x80

    ;adding a newline here for formatting purposes 
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, lenNewLine
    int 0x80

    ; printing the remainder message and remainder
    mov eax, 4
    mov ebx, 1
    mov ecx, dispRemainderMsg
    mov edx, lenRemainderMsg
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, remainder
    mov edx, 1
    int 0x80

    ;adding one more newline for formatting
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, lenNewLine
    int 0x80 

    ; exiting the program here
    mov eax, 1
    mov ebx, 0
    int 0x80