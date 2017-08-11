#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    char *infile = argv[1];
    uint8_t buffer[512]; // does this need to be 511? ------------------
    // open input file 
    FILE *inptr = fopen(infile, "r");   //reads the input file
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);  //returns an error if unreadable
        return 2;
    }                                                                                                                             //OPEN CARD FILE
    
    bool jpeg = false;
    int filecount = 0;
    FILE *img = NULL; 
    //long buffer[512];
    //starts the number of jpegs found at zero
    //fread(buffer, 1, 512, inptr); // reads input file into a 'buffer' in 512 single byte blocks
    
    
    
    
    while (fread(buffer, 512, 1, inptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) 
        {
            char filename[8]; //3 digits, a point, a 'jpg' and the string end char. 
            sprintf(filename, "%03i.jpg", filecount);  //then create a new file name called "00X.pjpg"
            filecount++;                            //increment the jpeg counter
            img = fopen(filename, "w");       // open the new file named as above
            fwrite(buffer, 1, 512, img);       // and write the block to it
            jpeg = true; //indicate that we have started a jpeg file 
            printf("Wegott'em!\n");
        }
        else if (jpeg == true)
        {
            fwrite(buffer, 1, 512, img);       // and write the block to it
        }
        else if (jpeg == false)
        {
            //printf("false\n");
        }
        else
        {
            // how do we get to having a jpeg, not being new and not writing the data... end? 
        }
    }
}
    
    //start of new jpeg?
    
        // yes ..
        
        //no...
    
    //already found jpeg?
    
        //no,..
        
        
        // yes
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//     do
//     {
//         fread(buffer, 1, 512, inptr);
//         if (jpeg == true)                                                                                                         //DO WE HAVE AN OPEN JPEG?
//         {
//             if  (buffer[0] == 0xff && buffer[1] == 0xff && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)                       //START OF JPEG?
//             {
//                 char filename[8]; //3 digits, a point, a 'jpg' and the string end char. 
//                 sprintf(filename, "%03i.jpg", filecount);  //then create a new file name called "00X.pjpg"
//                 filecount++;                            //increment the jpeg counter
//                 img = fopen(filename, "w");       // open the new file named as above
//                 fwrite(buffer, 1, 512, img);       // and write the block to it
//                 jpeg = true; //indicate that we have started a jpeg file 
                
//             }
//             else
//             {
//                 fwrite(buffer, 1, 512, img);       // and write the block to it
//             }
//         }
//         else
//         {
//             if  (buffer[0] == 0xff && buffer[1] == 0xff && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
//             {
//                 char filename[8]; //3 digits, a point, a 'jpg' and the string end char. 
//                 sprintf(filename, "%03i.jpg", filecount);  //then create a new file name called "00X.pjpg"
//                 filecount++;                            //increment the jpeg counter
//                 img = fopen(filename, "w");       // open the new file named as above
//                 fwrite(buffer, 1, 512, img);       // and write the block to it
//                 jpeg = true; //indicate that we have started a jpeg file 
                
//             }
//         }
//     }
//     while (fread(buffer, 1, 512, inptr) == 512);                                                                           //REPEAT UNTIL END OF CARD


//     //fclose(inptr);
    
//     return 0;




//     // int filecount = 0; //starts the number of jpegs found at zero
    
//     // do
//     // {
        
        
//     //     if  (buffer[0] == 0xff && //IF THE FIRST 4 BYTES OF THE BLOCK ARE THE HEADER OF A JPEG...
//     //         buffer[1] == 0xff &&
//     //         buffer[2] == 0xff &&
//     //         (buffer[3] & 0xf0) == 0xe0)
//     //         {
//     //             char filename[8]; //3 digits, a point, a 'jpg' and the string end char. 
//     //             sprintf(filename, "%03i.jpg", filecount);  //then create a new file name called "00X.pjpg"
//     //             filecount++;                            //increment the jpeg counter
//     //             FILE *img = fopen(filename, "w");       // open the new file named as above
//     //             fwrite(buffer, 1, 512, img);       // and write the block to it
//     //         }
//     //     else
//     //     {
//     //         fwrite(buffer, 1, 512, img);    // write the block to the file. - gotta get a check in here to get the file first, it shouldn't write if no file is found  
//     //     }
            
//     // }
//     // // while 
    
        
        
// }