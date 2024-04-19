BITS 32

SECTION .data ; data segment
    userMsg DB 'Please enter a two character string: '; asking the user for the 2 character string
    lenUserMsg EQU $-userMsg
    dispMsg DB 'The answer is: '
    lenDispMsg EQU $-dispMsg
    starterMsg DB 'The Swapping Program', 0xA
    lenStartMsg EQU $-starterMsg
    newline DB '',0xA
    lenNewLine EQU $-newline 

SECTION .bss ; uninitialized data
    userString RESB 3

SECTION .text
    GLOBAL _start

_start:
    ;starting message
    mov eax, 4
    mov ebx, 1
    mov ecx, starterMsg
    mov edx, lenStartMsg
    int 0x80
    
    ;showing the user prompt here
    mov eax, 4
    mov ebx, 1
    mov ecx, userMsg
    mov edx, lenUserMsg
    int 0x80

    ;reading in the string
    mov eax, 3    
    mov ebx, 0      
    mov ecx, userString
    mov edx, 2     
    int 0x80

    ;swapping here by taking the first char and putting it in al, taking the second char and putting it in ah, and then swapping them!
    mov al, [userString]    
    mov ah, [userString + 1]  
    mov [userString], ah    
    mov [userString + 1], al  

    ;printing the answer message here
    mov eax, 4
    mov ebx, 1
    mov ecx, dispMsg
    mov edx, lenDispMsg
    int 0x80

    ;printing the swapped string here
    mov eax, 4
    mov ebx, 1
    mov ecx, userString
    mov edx, 2   
    int 0x80

    ;adding a newline here for formatting purposes 
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, lenNewLine
    int 0x80

    ;exiting the program here
    mov eax, 1
    mov ebx, 0
    int 0x80






























