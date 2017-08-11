/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }
    

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int resizeFactor = atoi(argv[1]);
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }   

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    //then wind back and read another copy for my out 
    BITMAPFILEHEADER obf;
    fseek(inptr, -((long)(sizeof(BITMAPFILEHEADER))), SEEK_CUR);
    fread(&obf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    BITMAPINFOHEADER obi;
    fseek(inptr, -((long)sizeof(BITMAPINFOHEADER)), SEEK_CUR);
    fread(&obi, sizeof(BITMAPINFOHEADER), 1, inptr);
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
     
    
    // BITMAPFILEHEADER obf;   //header delarations  - original attepts can be found in footnotes, eventually i had to search the internet for help and found https://github.com/CoreData/cs50/blob/master/pset4/bmp/resize.c to be a good guide - used it to help me clean up the headers implementation  
    // obf = malloc(sizeof(BITMAPFILEHEADER));
    // BITMAPINFOHEADER obi;
    // obi *= malloc(sizeof(BITMAPINFOHEADER));
    //obf = bf;
    //obi = bi;
    obi.biHeight = (bi.biHeight * resizeFactor);
    obi.biWidth = (bi.biWidth * resizeFactor);
    
    // determine padding for scanlines borrowed from copy.c
    int inFilePadding = (4 - (bi.biWidth * 3) % 4) % 4; //determined by infile //for some reason size of RGBTRIPLE throws an erroe, but wee know tihs is a '3' so i've subbed it out here
    int outFilePadding = (4 - (obi.biWidth * 3) % 4) % 4; //determined by outfile
 
    obi.biSizeImage = ((obi.biWidth * (sizeof(RGBTRIPLE))) + outFilePadding) * abs(obi.biHeight);    
    obf.bfSize = obi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
     
    // write outfile's BITMAPFILEHEADER
    fwrite(&obf, sizeof(BITMAPFILEHEADER), 1, outptr);  //when i turn to obf it no longer recognises images... 

    // write outfile's BITMAPINFOHEADER
    fwrite(&obi, sizeof(BITMAPINFOHEADER), 1, outptr);
                                                              
     
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) // iterate over infile's scanlines
    {
        for (int j = 0; j < resizeFactor; j++) // then for as many times as we are stretching do a line by...
        {
            
            for (int k = 0; k < bi.biWidth; k++) // ...iterating over pixels in scanline...
            {
                
                RGBTRIPLE triple; // temporary storage
            
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr); // ...and read the RGB triples from infile...
                    
                        for (int l = 0; l < resizeFactor; l++)
                        {
                        fwrite(&triple, (sizeof(RGBTRIPLE)), 1, outptr); //  ...then write RGB triples to outfile as many times as we are stretching by...
                        }

            }
            
            fseek(inptr, inFilePadding, SEEK_CUR); // ...skip over padding, if any...  (pretty much taken form copy.c)
        
            for (int k = 0; k < outFilePadding; k++) // ...then add it back to the outfile (also borrowed form copy.c)
            {
                fputc(0x00, outptr);
            }
            
            fseek(inptr, -((long)(bi.biWidth * sizeof(RGBTRIPLE)) + inFilePadding), SEEK_CUR);
        }
        fseek(inptr, (bi.biWidth * 3 + inFilePadding), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

//
//
//
//failed partial implementations....


/*
 // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            RGBTRIPLE tempRow[bi.biWidth * resizeFactor];
            
            for (int indexCounter = 0; indexCounter < (bi.biWidth * resizeFactor); indexCounter++)
            {
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            
                // multiply pixels in scanline
                for (int l = 0; l < resizeFactor; l++)
                {
                   tempRow[indexCounter] = triple;
                }
                
            }
            for (int m = 0; m < resizeFactor; m++)
            {
                // write RGB triple to outfile
                fwrite(&tempRow, (sizeof(bi.biWidth)), 1, outptr);
            }
            
            */
            
            
/*

// iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
        
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                // write lines where...
                for (int k = 0; k < resizeFactor; k++)
                {
                    for (int l = 0; l < resizeFactor; l++)
                    {
                    // ...each pixel is written n times
                    fwrite(&triple, (sizeof(RGBTRIPLE)), 1, outptr);
                    }
                    fseek(inptr, -1 * bi.biWidth * factor), SEEK_CUR)  //and then we go back to start of infile line to scan pixels out again
                }
                
///convaluteed first (or third) version of headers                
                
             BITMAPINFOHEADER outInfoH;
    BITMAPFILEHEADER outFileH;
    outFileH = bf;
    outInfoH = bi;
    int inWidth = bi.biWidth;
    int inHeight = bi.biHeight;
    int outWidth = (inWidth * resizeFactor); 
    int outHeight = (inHeight * resizeFactor); 
    int newImageSize = (bi.biSizeImage * resizeFactor);
    
    //bi.biSizeImage = (((sizeof(RGBTRIPLE) * bi.biWidth) + ((4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4)) * abs(bi.Height));
    
    bf.bfSize = newImageSize+ sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);                                                        
          
          
     // determine padding for scanlines
    //int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;    
    
    int inFilePadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biWidth = (bi.biWidth * resizeFactor); 
    bi.biHeight = (bi.biHeight * resizeFactor); 
    
    int outFilePadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
          
    bi.biSizeImage = (((sizeof(RGBTRIPLE) * outWidth) + outFilePadding) * abs(outHeight));
          
                 
                
*/

