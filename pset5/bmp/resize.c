/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // create an int "n", a positive integer no bigger than 100, that will be used to resize the file by a factor "n"
    int n = atoi(argv[1]);
    
    if (n < 1 || n > 100)
    {
        printf("return a positive integer between 1 and 100\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_new;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_new = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_new;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_new = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine new dimensions
    bi_new.biHeight = bi.biHeight * n;
    bi_new.biWidth = bi.biWidth * n;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_new =  (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine new image sizes
    bi_new.biSizeImage = (bi_new.biWidth * sizeof(RGBTRIPLE) + padding_new) * abs(bi_new.biHeight);
    bf_new.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi_new.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        
        // iterate n times for each scanline
        for (int j = 0; j < n; j++)
        {
        
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n number of times
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // add padding to the output file
            for (int m = 0; m < padding_new; m++)
            {
                fputc(0x00, outptr);
            }
            
            // reset file position indicator if vertical resizing is not finished for input line
            if (j < n - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over input padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
