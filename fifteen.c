/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
int blankLocationX;
int blankLocationY;


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

//global vars
blankLocationX = d - 1;
blankLocationY = d - 1;
//int grid[d][d];  // creates 2d array with dimention d (from argv) - out here for scope issue check...

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

 

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
   
   
   int number = ((d * d) - 1); // determines the higest number to start the array with ex. 4x4 grid, 16 numbers, minus 1 is 15. grid[0][0] should be 15, grid[0][1] should be 14, etc.... 
   
   for (int row = 0; row < d; row++) // fills grid
   {
       for (int column = 0; column < d; column++)
       {
           board[row][column] = number;
           number--;
       }
   }
   
   if ( ((d * d) % 2) != 1)  // swaps 1 and 2 if total tiles would be even
   {
       board[d - 1][d -2] = 2;
       board[d - 1][d -3] = 1;
   }
   
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    int number = ((d * d) - 1);
    for (int row = 0; row < d; row++) // fills grid
    {
       for (int column = 0; column < d; column++)
       {
           if (column != (d - 1))  // draws int, with 2digit formatting and a pipe if not on right-most column
           {
                printf(" %2i |", board[row][column]);
                number--;
           }
            else if (board[row][column] == 0) // prints underscore without a pipe if on right-moist column
            {
                printf(" __");
            }
            else if (board[row][column] == 0 && column != (d - 1))  //prints an underscore with a pipe
            {
                printf("  _ |");
            }
            else
           {
                printf(" %2i ", board[row][column]); // draws int, with 2digit formatting 
                number--;
           }
           
       }
       printf("\n");
    }

}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
   int tileLocationX = 0;
   int tileLocationY = 0;
   
   for (int row = 0; row < d; row++) // fills board
   {
       for (int column = 0; column < d; column++)
       {
           if (board[row][column] == tile) // if this location contains this value
           {
               tileLocationX = column; 
               tileLocationY = row;
               
               if (tileLocationX == blankLocationX && ((tileLocationY == blankLocationY + 1) || (tileLocationY == blankLocationY - 1)))  // if the desired tile is within 1 column and the same row as the blank tile then this is a legal move
               {
                   //int temp = tile;
                   board[blankLocationY][blankLocationX] = tile; //where the blank was is now the target tile
                   blankLocationY = row;
                   blankLocationX = column;   // the blank tile is now at the location where the target tile was found and now swapped out of... i hope
                   board[blankLocationY][blankLocationX] = 0;
                   return true;
               }
               else if (((tileLocationX == blankLocationX + 1) || (tileLocationX == blankLocationX - 1)) && tileLocationY == blankLocationY)  // if the desired tile is in the same column and within one row as the blank tile then this is a legal move
               {
                   //int temp = tile;
                   board[blankLocationY][blankLocationX] = tile; //where the blank was is now the target tile
                   blankLocationY = row;
                   blankLocationX = column;   // the blank tile is now at the location where the target tile was found and now swapped out of... i hope
                   board[blankLocationY][blankLocationX] = 0;
                   return true;
               }
               
           }
           
       }
   }
   
   return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
   
   int correctNumber = 1;
   
   for (int row = 0; row < d; row++) // checks final grid
   {
       for (int column = 0; column < d; column++)
       {
           if (board[row][column] != correctNumber)
           {
               return false;
           }
           else if (correctNumber == (d * d) - 1)
           {
               return true;
           }
           else
           {
               //keep looping
           }
           correctNumber++;
       }
   }
    return false;
}
