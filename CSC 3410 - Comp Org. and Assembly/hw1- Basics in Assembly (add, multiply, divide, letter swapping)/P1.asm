BITS 32

SECTION .data ; data segment
    userMsg DB 'Please enter a number: '; asking the user for the first num
    lenUserMsg EQU $-userMsg
    dispMsg DB 'The answer is: '
    lenDispMsg EQU $-dispMsg
    starterMsg DB 'The Adding Program', 0xA
    lenStartMsg EQU $-starterMsg
    newline DB '',0xA
    lenNewLine EQU $-newline 

SECTION .bss ; uninitialized data
    num1 RESB 5
    num2 RESB 5
    sum RESB 5

SECTION .text
    GLOBAL _start

_start:
    ;starting message
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
    mov al,[num1]
    sub al, 48
    mov [num1], al

    ; converting the second number by taking 48 away
    mov al,[num2]
    sub al, 48
    mov [num2], al

    ; adding the numbers here
    mov al,[num1]
    add al,[num2]
    mov [sum], al

    ; converting the answer back here
    mov al,[sum]
    add al, 48
    mov [sum], al

    ; printing the result message here
    mov eax, 4
    mov ebx, 1
    mov ecx, dispMsg
    mov edx, lenDispMsg
    int 0x80

    ; printing the actual number answer here
    mov eax, 4
    mov ebx, 1
    mov ecx, sum
    mov edx, 1
    int 0x80

    ;adding a newline here for formatting purposes 
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, lenNewLine
    int 0x80

    ; exiting the program here
    mov eax, 1
    mov ebx, 0
    int 0x80
