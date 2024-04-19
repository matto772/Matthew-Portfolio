BITS 32
GLOBAL add
SECTION .text
add: 
    push ebp
    mov ebp,esp

    push ebx

    mov eax, [ebp+8]
    mov eax, [ebp+12]
    add eax, ebx

    pop ebx
    pop ebp
    ret

















