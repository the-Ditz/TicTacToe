#include <cs50.h>
#include <stdio.h>
#include <math.h>

float getValue();
float checkValue(float);
void makeChange(float);
int coinOut(int, int);

int main(void)
{
    
    float value = getValue();
    checkValue(value);
    makeChange(value);
    
}



















void makeChange(float value)
{
    
    int cents = (round(value * 100));
    //printf("%i\n", cents);
    
    int coinTotal = 0;
    
    coinTotal = coinTotal + coinOut(cents, 25);
    cents = cents % 25;
    coinTotal = coinTotal + coinOut(cents, 10);
    cents = cents % 10;
    coinTotal = coinTotal + coinOut(cents, 5);
    cents = cents % 5;
    coinTotal = coinTotal + coinOut(cents, 1);
    
    printf("%i\n", coinTotal); 
}

float checkValue(float value)
{
    while (value < 0)
    {
        printf("How much change is owed?\n");
        value = get_float();
    }
    return value;
}

float getValue()
{
    printf("O hai! How much change is owed?\n");
    float value = get_float();
    return value;
}

int coinOut(int cents, int increment)  
{
    int coinCounter = 0;
    while (cents >= increment)
    {
        coinCounter++;
        cents -= increment;
    }
    return coinCounter;
}        

