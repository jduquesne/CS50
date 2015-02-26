#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int Key;
    string ToEncript;
    int LetterToEncript;
    
    // Get the key (k), a non negative integer

    if (argc != 2)
    {
        printf("return 1\n");
        return 1;
    }
    
    // confirm the key is a positive integer
    else if ((Key = atoi(argv[1])) < 1)
    {
        printf("return a positive integer\n");
        return 1;
    }
    
    else
    {
        // Get the string of text to ciper
        ToEncript = GetString();
        
        // encipher
        if (ToEncript != NULL) 
        {
            // encipher each letter individually
            for (int i = 0, n = strlen(ToEncript); i < n; i++)
            {            
                LetterToEncript = ToEncript[i];

                // to leave non alpha-char uncripted
                if (!isalpha (LetterToEncript))
                {
                    printf("%c", LetterToEncript);
                }  

                // encrypt letters only
                else if (isalpha (LetterToEncript))
                {
                    // encrypt capital letters
                    if (isupper (LetterToEncript))
                    {
                        LetterToEncript = 'A' + (LetterToEncript + Key - 'A') % 26;
                        printf("%c", LetterToEncript);
                    }
                    // encrypt lower case letters
                    else if (islower (LetterToEncript))
                    {
                        LetterToEncript = 'a' + (LetterToEncript + Key - 'a') % 26;
                        printf("%c", LetterToEncript);
                    }
                }
            }
        }
        printf("\n");
    }
    return 0;
}
