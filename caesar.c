#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string promptText();
string cipherText(string, int, int);
//int keyValue;

int main(int argc, string argv[])
{
    int keyValue = 0;
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    else
    {
        keyValue = atoi(argv[1]);
    }
    
    
    //int keyValue = keyCheck(argc, argv); // console value
    
    string oText = promptText(); //sets phrase to be decrypted
    int messageLength = strlen(oText);
    cipherText(oText, messageLength, keyValue);
    return 0;
}




string promptText() // prompts for code to be encrypted, verifies != null and then returns it.
{
    printf("plaintext: ");
    string oText = get_string();
   
    if (oText == NULL)
    {
        return "FAILURE - NULL VALUE";
    }
    else
    {
        return oText;
    }
}

string cipherText(string oText, int messageLength, int keyValue) //take chars from string and change according to key passed in from console
{
    string newText = oText;
    for (int k = 0; k < messageLength; k++)
    {
        if (oText[k] > 123 || (oText[k]  < 64) || (oText[k] >= 91 && oText[k] <= 96))
        {
            newText[k] = oText[k]; 
        }
        else if ((keyValue + oText[k]) > 122)
        {
            newText[k] = (((oText[k] + keyValue) % 122) + 96); 
        }
        else if ((oText[k] < 91) && ((keyValue + oText[k]) > 91))
        {
            newText[k] = (((oText[k] + keyValue) % 91) + 65); 
        }
        else
        {
            newText[k] = (oText[k] + keyValue);   
        }
    }
    
    printf("ciphertext: %s\n", newText);
    return oText;
}