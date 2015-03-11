/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    // open input file 
    FILE* infile = fopen("card.raw", "r");
    
    // check for input file potential errors
    if (infile == NULL)
    {
        fclose(infile);
        printf("Could not open %s.\n", "card.raw");
        return 1;
    }

    // declare output file 
    FILE* outfile = NULL;
    
    // create a counter for the jpeg recovered
    int jpeg = 0;
    
    // create a buffer for each file
    uint8_t buffer[512];
    
    while (!feof (infile))
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // close previous file if open
            if (outfile != NULL)
            {
                fclose(outfile);
            }
            
            // create a new jpeg name
            char filename[8];
            sprintf (filename, "%03d.jpg", jpeg);
            
            // open the new file
            outfile = fopen(filename, "w");
            
            // write buffer into new file
            fwrite(buffer, sizeof(buffer), 1, outfile);
            
            // increment counter
            jpeg++;
        }
        else
        {
            if(jpeg > 0)
            {
                // write buffer into new file
                fwrite(buffer, sizeof(buffer), 1, outfile);
            }
        }
        
        // go to the next jpeg
        fread(buffer, sizeof(buffer), 1, infile);
    }

    // close outfile
    if(jpeg > 0)
    {
        fclose(outfile);
    }

    // close infile
    fclose(infile);

    // that's all folks
    return 0;
}
