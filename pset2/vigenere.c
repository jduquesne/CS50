#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string Key;
    string ToEncript;
    int LetterToEncript;
    int KeyModulo;
    int KeyLetterCount;
    int EncriptKey;
    
    // Get the key (k), a succession of letters
    
    // check we have one, and only key
    if (argc != 2)
    {
        printf("return 1\n");
        return 1;
    }
    
    else
    {
        Key = argv[1];
        
        // check the key is alphabetic only
        for (int i = 0, n = strlen(Key); i < n; i++)
        {
            if (isdigit (Key[i]))
            {
                printf("Letters only please\n");
                return 1;
            }
            else if (ispunct (Key[i]))
            {
                printf("Letters only please\n");
                return 1;
            }
        }

        // Get the string of text to ciper
        ToEncript = GetString();
        
        // encipher
        if (ToEncript != NULL) 
        {
            KeyLetterCount = 0;
            
            // encipher each letter individually
            for (int i = 0, n = strlen(ToEncript); i < n; i++)
            {            

                LetterToEncript = ToEncript[i];
                
                // to leave non alpha-char uncripted
                if (!isalpha (LetterToEncript))
                {
                    printf("%c", LetterToEncript);
                }   
                   
                else
                {         
                    KeyModulo = KeyLetterCount % strlen(Key);
                    
                    // encrypt capital letters
                    if (isupper (LetterToEncript))
                    {

                        // formula is key casing case different from LetterToEncript casing
                        if (islower (Key[KeyModulo]))
                        {
                            EncriptKey = (Key[KeyModulo] - 'a');
                            LetterToEncript = 'A' + (LetterToEncript + EncriptKey - 'A') % 26;
                            printf("%c", LetterToEncript);
                        }
                        
                        // formula is key casing case is the same as LetterToEncript casing
                        else
                        {
                            EncriptKey = (Key[KeyModulo] - 'A');
                            LetterToEncript = 'A' + (LetterToEncript + EncriptKey - 'A') % 26;
                            printf("%c", LetterToEncript);
                        }
                    }
                    // encrypt lower case letters
                    else
                    {
                        // formula is key casing case different from LetterToEncript casing
                        if (isupper (Key[KeyModulo]))
                        {
                            EncriptKey = (Key[KeyModulo] - 'A');
                            LetterToEncript = 'a' + (LetterToEncript + EncriptKey - 'a') % 26;
                            printf("%c", LetterToEncript);
                        }

                        // formula is key casing case is the same as LetterToEncript casing
                        else
                        {
                            EncriptKey = (Key[KeyModulo] - 'a');
                            LetterToEncript = 'a' + (LetterToEncript + EncriptKey - 'a') % 26;
                            printf("%c", LetterToEncript);
                        }
                    }
                    KeyLetterCount++;
                }
            }               
        }
    }
    printf("\n");
return 0;
}
