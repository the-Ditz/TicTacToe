#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string get_name();

int main(void)
{
    string name = get_name(); 
    int fullNameLength = strlen(name); 
    
    int firstWord = 1; // for checking if we have a new name - 1=true / 0=false -
    for (int i = 0; i < fullNameLength; i++)
    {
        if (name[i] != ' ' && firstWord == 1) // 32 is the ASCII value of a space
        {
            printf("%c", toupper(name[i])); //print the character in its capital if it is not a space
            firstWord = 0;
        }
        else if (name[i] == ' ' && firstWord == 0)
        {
            firstWord = 1;
        }
        else 
        {
            /*restart loop*/
        }
    }
    printf("\n");  //for formatting
}


string get_name() // Prompts user for thier name and returns it as a string
{
        //printf("Please provide your full name: "); //spec calls for a prompt but spec images dont show and check50 fails when this is turned on
        string name = get_string();  
        if (name != NULL) //check for invalid inputs as per lecture2 -  not in spec but I think a good design element
        {
         return name;   
        }
        else
        {
            return "The value you have entered is not a valid name.";
        }
        
}

