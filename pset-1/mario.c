#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int block;
    int height;
    
    // Get user's choice for Mario's half-pyramid height. 
    // Integer must be between 0 and 23.
    
    do
    {
        printf("please choose Mario's height between 1 and 23 : ");
        height = GetInt();
    }     
    while (height < 0 || height > 23);
    
    // create the ## pyramid based on user input. Align right.
    
    for (block = 0; block < height; block++)
    {
        int space;
        int dash;
        
        // "space" is inserted before ## to align right.
        for (space = height-1; space > block; space--)
            printf(" ");
            
        // top of the pyramid gets two dashes, then add one per line going down.
        for (dash = -2; dash < block; dash++)
            printf("#");
            
        printf("\n");
    }
}
