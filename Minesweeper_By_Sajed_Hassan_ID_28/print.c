#include "main.h"
#include "print.h"


// printing the opened grid to a file
void testFile(int rows, int columns,char gridStatues[rows][columns])
{
    FILE * fTestFile;
    fTestFile = fopen("debug.txt","w");





    int i = 0;
    int j = 0;
    fprintf(fTestFile,"=====================================\n");

    int rowsDigit = digit(rows);

    char extraspace = ' ';
    fprintf(fTestFile,"\t   %*c",rowsDigit,extraspace);
    for ( j ; j < columns ; j++)
    {
        fprintf(fTestFile,"%d ",j);
    }



    fprintf(fTestFile,"\n\n");




    i = 0 ;
    j = 0;
    for (i ; i < rows ; i++)
    {
        fprintf(fTestFile,"\t%*d   ",rowsDigit,i);
        for ( j = 0; j < columns ; j++)
        {
            int jDigits = digit(j)*-1;
            fprintf(fTestFile,"%*c ",jDigits,gridStatues[i][j]);
        }
        fprintf(fTestFile,"\n\n");
    }
    fprintf(fTestFile,"=====================================\n");







    fclose(fTestFile);
}










// getting the digits of a number .... to align the grid in case of bigger sizes than 9 * 9 (two digit sizes)
int digit(int n)
{
    int n1 = n;
    int counter = 0;
    while( n1 / 10 != 0)
    {
        counter++;
        n1 /= 10;
    }
    counter++;
    return counter;
}


// a function to print the grid
void printGrid(int rows, int columns, char grid[rows][columns],int timePassedInMins,int timePassedInSecs,int numOfFlags,int numOfQ,int numOfMoves)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i = 0;
    int j = 0;
    //puts( "\033[2J" );
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n                                                                 =====================================\n");

    int rowsDigit = digit(rows);
    // useless int columnsDigit = digit(columns);

    char extraspace = ' ';
    printf("                                                                 \t   %*c",rowsDigit,extraspace);
    for ( j ; j < columns ; j++)
    {
        printf("%d ",j);
    }

    printf("\t\t\tTime passed (Min:sec): %d:%02d",timePassedInMins,timePassedInSecs);
    printf("\n\n");




    i = 0 ;
    j = 0;
    for (i ; i < rows ; i++)
    {
        printf("                                                                 \t%*d   ",rowsDigit,i);
        for ( j ; j < columns ; j++)
        {
            int jDigits = digit(j)*-1;
            printf("%*c ",jDigits,grid[i][j]);
        }
        j = 0;

        if (i == 0)
        {
            printf("\t\t\tNumber of moves      : %d",numOfMoves);
        }
        if (i == 1)
        {
            if (numOfFlags >= (rows * columns / 10)+1)
                SetConsoleTextAttribute(hConsole, 252);

                printf("\t\t\tNumber of Flags      : %d / %d",numOfFlags,((rows * columns / 10)+1));
                SetConsoleTextAttribute(hConsole, 249);
        }
        if (i == 2)
        {
            printf("\t\t\tNumber of Que M      : %d",numOfQ);
        }
        printf("\n\n");
    }
    if ( i < 3 )
    {
        printf("                                                                 \t\t\t\t\t\tNumber of Que M      : %d\n",numOfQ);
    }
    printf("                                                                 =====================================\n");


}
