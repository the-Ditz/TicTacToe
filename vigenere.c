#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string cipherKey;
string oMessage;
string promptText();
string cipherText();

int main(int argc, string argv[])
{
    
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    else
    {
        cipherKey = argv[1];
        int length = strlen(cipherKey);
        for (int i = 0; i < length; i++)
        {
            if (toupper(cipherKey[i]) > 90 || toupper(cipherKey[i]) < 65)
            {
                //printf("Keyword must be alphabetic.\n");
                printf("Usage: ./vigenere k\n");
                return 1;
            }
            else
            {
                
            }
        }
    }
    
    oMessage = promptText();
    int messageLength = strlen(oMessage);
    string encrypted = cipherText(oMessage, messageLength, cipherKey);
    printf("ciphertext:  %s\n", encrypted);
    
}

string promptText() // prompts for code to be encrypted, verifies != null and then returns it.
{
    printf("plaintext: ");
    oMessage = get_string();
   
    if (oMessage == NULL)
    {
        return "FAILURE - NULL VALUE";
    }
    else
    {
        return oMessage;
    }
}

string cipherText(string oText, int messageLength, string key) //take chars from string and change according to key passed in from console
{
    string newText = oText;
    
    int keyLength = strlen(key);
   
    int keyValue;
    
    int nonChar = 0;
    
    for (int j = 0; j < messageLength; j++)
    {
        
        keyValue = (toupper(key[(j - nonChar) % keyLength]) - 'A');
        
        if (oText[j] > 123 || (oText[j]  < 64) || (oText[j] >= 91 && oText[j] <= 96)) // if not a letter
        {
            newText[j] = oText[j]; 
            nonChar++;
        }
        else if ((keyValue + oText[j]) > 122) // if outside of range, loop back at start, i.e 'a'
        {
            newText[j] = (((oText[j] + keyValue) % 122) + 96); 
        }
        else if ((oText[j] < 91) && ((keyValue + oText[j]) > 91)) // if outside of range, loop back at start, i.e 'A'
        {
            newText[j] = (((oText[j] + keyValue) % 91) + 65); 
        }
        else // if inside range, assign new enciphered value
        {
            newText[j] = (oText[j] + keyValue);   
        }
        
    }
    
    return newText;
    
}