//Matthew Ogurkis
//backandforth.c
//Date Started: 11/3/2023
//Date Finished: 11/13/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes
int addstr(char *a, char *b);
int is_palindrome(char *s);
int factstr(char *a);
int fact(int n);
int is_palindrome_c(char *a);
void palindrome_check();
//fact function
int fact(int n)
{
    if(n == 0 || n ==1)
    {
        return 1;
    }
    else
    {
        return n * fact(n-1);
    }
}

//is_palindrome function c edition 
int is_palindrome_c(char *a)
{
    int len = strlen(a);

    //going over the string from both ends
    for(int i = 0, j = len-1; i < j; i++, j--)
    {
        if(a[i] != a[j])
        {
            return 0;
        }
    }
    return 1;
}

//main here
int main()
{
    int choice;
    char myString[100];
    char a[100], b[100];

    //menu shenanigans start here
    do
    {
        printf("\nMenu:\n");
        printf("1: Add two numbers together!\n");
        printf("2: Test if a string is a palindrome! (C -> ASM)\n");
        printf("3: Print the factorial of a number!\n");
        printf("4: Test if a string is a palindrome! (ASM -> C)\n");
        printf("Enter your choice (1-4, 0 to exit): ");
        scanf("%d", &choice);

        //switch statement to handle user decisions regarding the menu
        switch(choice)
        {
            //so the default doesn't throw 0 as invalid
            case 0:
            break;

            //add two nums
            case 1:
                printf("Enter first number: ");
                scanf("%s", a);
                printf("Enter second number: ");
                scanf("%s", b);
                //calling the assembly function here and printing the result
                int result = addstr(a, b);
                printf("Sum of the numbers: %d\n", result);
                break;
            
            //palindrome 
            case 2:
                printf("Please enter a string: ");
                fgets(myString, 100, stdin);
                scanf("%[^\n]%*c", myString);
                int paliResult = is_palindrome(myString);
                if(paliResult == 1)
                {
                    printf("It is a palindrome.\n");
                }
                else
                {
                    printf("It is NOT a palindrome\n");
                }
                break;
            //factorial
            case 3:
                printf("Please enter a number: ");
                scanf("%s", myString);
                int factResult = factstr(myString);
                printf("The factorial is: %d\n", factResult);
                break;
            //palindrome_check
            case 4:
                palindrome_check();
                break;

            default:
                printf("Invalid choice. Please pick 1-4.\n");
        }

    }while(choice != 0);

    return 0;
}