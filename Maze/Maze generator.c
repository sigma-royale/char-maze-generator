#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


//This checks any given coordinates.
int checkForUsedCoords(int usedXCoords[], int usedYCoords[], int size, int x, int y)
{
    int posNum = 0;
    while (posNum < size)
    {
        if ((usedXCoords[posNum] == x && usedYCoords[posNum] == y) || x < 0 || x > 9 || y < 0 || y > 9)
        {
            return 1;
        }
        else
        {
            posNum++;
        }
    }
    return 0;
}

int giveAvailableSpots(int usedXCoords[], int usedYCoords[], int size, int availableCoordsX[], int availableCoordsY[], int x, int y)
{
    //Two arrays are created for storing all possible locations, up, down, left, right.
    int possibleLocationsX[4];
    int possibleLocationsY[4];
    //This stores the possible locations in the arrays.
    possibleLocationsX[0] = x - 1;
    possibleLocationsY[0] = y;
    possibleLocationsX[1] = x + 1;
    possibleLocationsY[1] = y;
    possibleLocationsX[2] = x;
    possibleLocationsY[2] = y - 1;
    possibleLocationsX[3] = x;
    possibleLocationsY[3] = y + 1;

    int posNum = 0;
    int repcount = 0;
    while (repcount <= 3)
    {
        if (checkForUsedCoords(usedXCoords, usedYCoords, size, possibleLocationsX[repcount], possibleLocationsY[repcount]) == 0)
        {
            availableCoordsX[posNum] = possibleLocationsX[repcount];
            availableCoordsY[posNum] = possibleLocationsY[repcount];
            posNum++;
        }
        repcount++;
    }

    return posNum;
}

int main(){
    srand(time(NULL));
    int x = 0, y = 0;
    int usedXCoords[100];
    int usedYCoords[100];
    usedXCoords[0] = 0;
    usedYCoords[0] = 0;
    int posNum = 1;
    int availableCoordsX[4];
    int availableCoordsY[4];
    int altPosNum = 0;
    
    int makeMazeY = 0;
    char maze[21][21];

    
    

    while (makeMazeY < 21)
    {
        int makeMazeX = 0;
        while (makeMazeX < 21)
        {
            maze[makeMazeX][makeMazeY] = '@';

            makeMazeX++;
        }

        makeMazeY++;
    }
    maze[1][1] = ' ';
    maze[0][1] = ' ';
    maze[20][19] = ' ';
    //printf("%d, %d\n", x, y);
    while(posNum < 100)
    {
    
        //Adds the coordinates to the arrays.
        if (checkForUsedCoords(usedXCoords, usedYCoords, posNum, x, y) == 0)
        {
            usedXCoords[posNum] = x;
            usedYCoords[posNum] = y;
            posNum++;
        }
        int availablespots = giveAvailableSpots(usedXCoords, usedYCoords, posNum, availableCoordsX, availableCoordsY, x, y);
        
        if (availablespots != 0)
        {
            //these are snapshots of the x and y coords before they get changed
            //I might change it so it isnt needed but for now its just to help me read it
            int lastX = x;
            int lastY = y;

            int randomArrayChoice = rand() % availablespots;
            x = availableCoordsX[randomArrayChoice];
            y = availableCoordsY[randomArrayChoice];
            //This prints out the coordinates it switches to
            //printf("%d, %d\n", x, y);

            
            if (lastX != x)
            {
                int wallBetweenOpenCells = (lastX*2 + x*2)/2;
                maze[wallBetweenOpenCells+1][y*2+1] = ' ';
            }
            else if (lastY != y)
            {
                int wallBetweenOpenCells = (lastY*2 + y*2)/2;
                maze[x*2+1][wallBetweenOpenCells+1] = ' ';
            }
            maze[x*2+1][y*2+1] = ' ';

            
        }
        else
        {
            if (altPosNum > posNum)
            {
                break;
            }
            x = usedXCoords[altPosNum];
            y = usedYCoords[altPosNum];
            //This prints out the coords of where it starts to pathfind again.
            //printf("%d, %d\n", x, y);

            altPosNum++;
        }


    }
    
    //this part prints out the maze, char by char, line by line
    int arrayGridY = 0;

    while (arrayGridY < 21)
    {
        int arrayGridX = 0;

        while (arrayGridX < 21)
        {
            printf("%c", maze[arrayGridX][arrayGridY]);
            arrayGridX++;
        }
        printf("\n");

        arrayGridY++;
    }
    
    printf("\n");
    
    return 0;
}
