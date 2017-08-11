/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

bool searchR();


/**
 * Returns true if value is in array of n values, else false.
 */


    int middle = 0; //inititalize the middle value
    int upperBound = 0;  // inititialize the upper bound
    int lowerBound = 0; // inititilize the lower bound

bool search(int value, int values[], int n)
{
    middle = 0; 
    upperBound = (n - 1);  // sets correct value
    lowerBound = 0; 
    
    do
    {
        middle = ((upperBound + lowerBound) / 2);  // set the middle
        
        
        if (values[middle] == value) //  if this is the value then we found it!
        {
          
           return true;
           
        }
        else if (upperBound <= lowerBound)
        {
            
            return false;
            
        }
        else if (values[middle] > value)  //  if the middle value is bigger than the target value set the new upper bound one below the current middle and the call self.
        {
            
            upperBound = middle - 1;
            
        }
        else if (values[middle] < value)  //  if the middle value is smaller than the target value set the new lower bound one above the current middle and the call self.
        {
            
            lowerBound = middle + 1;
            
        }
        
        
        
        
    }
    while (values[middle] != value);
    
   
    
    return false; // else we didn't find it
}


/*
bool search(int value, int values[], int n)
{
    middle = 0; 
    upperBound = (n - 1);  // sets correct value
    lowerBound = 0; 
    
    searchR(value, values, lowerBound, upperBound);  // write a new method that CAN be recursive. 
    
   
    
    return false; // else we didn't find it
}

bool searchR(int value, int values[], int lower, int upper)
{
    do // while the upper bound is bigger than lower bound
    {
        middle = ((upperBound + lowerBound) / 2);  // set the middle
        
        if (values[middle] == value) //  if this is the value then we found it!
        {
            return true;
        }
        else if (values[middle] > value)  //  if the middle value is bigger than the target value set the new upper bound one below the current middle and the call self.
        {
            upperBound = middle - 1;
            searchR(value, values, lowerBound, upperBound);
        }
        else if (values[middle] < value)  //  if the middle value is smaller than the target value set the new lower bound one above the current middle and the call self.
        {
            
            lowerBound = middle + 1;
            searchR(value, values, lowerBound, upperBound);
        }
        
    }
    while (upper > lower);
   
    return false;
}
*/



void sort(int values[], int n)
{
    int swap = - 1;  // set non zero
    
    while (swap != 0)  // and while it is not zero
    {
        swap = 0; // now it is zero unless
        
        for (int index = 0; index < n - 1; index++)
        {
        
            if (values[index] > values[index + 1])
            {
                int temp = values[index];
                values[index] = values[index + 1];
                values[index + 1] = temp;
                swap++;
            }
        }
    }
    return;
}
    
    

