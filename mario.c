#include <cs50.h>
#include <stdio.h>

int getHeight();
void drawPyramid();
int checkHeight();

int main(void)
{
    int height = getHeight();
    height = checkHeight(height);
    drawPyramid(height);
}


int getHeight()
{
    printf("Height: ");
    int i = get_int(); 
    return i;
}

void drawPyramid(int height)
{
    
    for (int layer = 0; layer < height; layer++)
    {
        int blocks = (1 + layer);
        
        for (int n = 0; n < (height - 1 - layer); n++)
            {
                printf(" ");
            }
        for (int n = blocks; n > 0; n--)
            {
                printf("#");
            }
        printf("  ");
        for (int n = blocks; n > 0; n--)
            {
                printf("#");
            }
        
        printf("\n");
    }
}
    


int checkHeight(int height)
{
    if (height < 0 || height > 23)
    {
        do
        {
            printf("Height: ");
            height = get_int();
        }
        while (height < 0 || height > 23);
        {
            return height;
        }
        
    }
    else if (0 == height && height < 24)
    {
        return height;
    }
    return height; 
}
