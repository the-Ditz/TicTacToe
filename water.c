#include <stdio.h>
#include <cs50.h>

int minBottle();

int main(void)
{
    
   int i;
    
    do
    {
        printf("Minutes: ");
        i = get_int();
    }
    while (i < 0);
    {
        int n = minBottle(i);
        printf("Bottles: %i\n", n);
    }
    return i;
    
}

int minBottle(int m)
{
    return m * 12;
}

