#include "actions.h"
#include "main.h"

//opening the opened cell again .
void reopen(int choosedRow, int choosedColumn,int rows, int columns,char grid[rows][columns],char gridStatues[rows][columns],char gridOpennedStatues[rows][columns],int * Pplaying,int *PnumOfOpennedCells)
{

    // if there was a number in the cell we reopening it
    if (grid[choosedRow][choosedColumn] != ' ')
    {

        // we need to look around the opened cell but not the choose cell itself
        int i = choosedRow;
        int j = choosedColumn;
        char counter = '0';

        // bounding the looking area bu the size of the grid
        int i_initial = i-1;
        if (i_initial < 0)i_initial++;



        int i_final = i+1;
        if (i_final >= rows )i_final--;

        int j_final = j+1;
        if (j_final >= columns)j_final--;




        for ( i_initial ; i_initial <= i_final  ; i_initial++)
        {
            int j_initial = j-1;
            if (j_initial < 0)j_initial++;

            for ( j_initial ; j_initial <= j_final ; j_initial++)
            {
                if (i_initial != i   ||   j_initial != j)
                {
                    if (grid[i_initial][j_initial] == 'F')
                    {
                        counter++;
                    }
                }
            }
        }


        // if there were enough flags : take an action
        if ( counter >= grid[choosedRow][choosedColumn])
        {
            int i = choosedRow;
            int j = choosedColumn;
            int i_initial = i-1;
            if (i_initial < 0)i_initial++;



            int i_final = i+1;
            if (i_final >= rows )i_final--;

            int j_final = j+1;
            if (j_final >= columns)j_final--;




            for ( i_initial ; i_initial <= i_final  ; i_initial++)
            {
                int j_initial = j-1;
                if (j_initial < 0)j_initial++;

                for ( j_initial ; j_initial <= j_final ; j_initial++)
                {
                    if ( (i_initial != i   ||   j_initial != j)   &&  gridOpennedStatues[i_initial][j_initial] == '0')
                    {
                        open(i_initial, j_initial,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);
                    }
                }
            }

        }
    }
    else
    {
        // if it was a n empty cell (with no numbers) we need to open the surrounding cells any way

        int i = choosedRow;
        int j = choosedColumn;
        int i_ini = i-1;
        if (i_ini < 0)i_ini++;



        int i_fin = i+1;
        if (i_fin >= rows )i_fin--;

        int j_fin = j+1;
        if (j_fin >= columns)j_fin--;




        for ( i_ini ; i_ini <= i_fin ; i_ini++)
        {
            int j_ini = j-1;
            if (j_ini < 0)j_ini++;

            for ( j_ini ; j_ini <= j_fin ; j_ini++)
            {
                if ((i_ini != i   ||   j_ini != j)  &&  gridOpennedStatues[i_ini][j_ini] == '0')
                {
                    open(i_ini, j_ini,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);
                }
            }
        }
    }
}




//recursion or DFS .. any way ..
void rec(int choosedRow, int choosedColumn,int rows, int columns,char grid[rows][columns],char gridStatues[rows][columns],char gridOpennedStatues[rows][columns],int * Pplaying,int *PnumOfOpennedCells)
{
    // we need them to check the corners as we are moving in just for directions .
    int up = 0;
    int down = 0;
    int right = 0;
    int left = 0;


    while ( choosedRow - 1 >=0 && grid[choosedRow-1][choosedColumn] != 'F' && gridStatues[choosedRow-1][choosedColumn] == ' ' && gridOpennedStatues[choosedRow-1][choosedColumn] == '0')
    {
        // opening the cell.
        open(choosedRow-1, choosedColumn,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);
    }

    if ( choosedRow - 1 >=0 && gridStatues[choosedRow-1][choosedColumn] != ' ' && gridStatues[choosedRow-1][choosedColumn] != '*'&&grid[choosedRow-1][choosedColumn]!='F')
    {
        //it's preventing the function from recalling the function on the opened cell already (the second condition in IF statement)
        // opening the boundary numeric cells but not corners
        grid[choosedRow-1][choosedColumn] = gridStatues[choosedRow-1][choosedColumn] ;
        if (gridOpennedStatues[choosedRow-1][choosedColumn] == '0')
        {
            (*PnumOfOpennedCells)++;
            gridOpennedStatues[choosedRow-1][choosedColumn] = '1';
        }
        //checking for corners .
        up = 1;
    }
    // checking for corners in case of :  A flag stopped the function .
    if (  choosedRow - 1 >=0 && grid[choosedRow-1][choosedColumn] == 'F')
    {
        up = 1;
    }

    // the following is the same description but for the other directions.


    while ( choosedColumn + 1 < columns && grid[choosedRow][choosedColumn+1] != 'F' && gridStatues[choosedRow][choosedColumn+1] == ' ' && gridOpennedStatues[choosedRow][choosedColumn+1] == '0')
    {
        open(choosedRow, choosedColumn+1,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);

    }
    if (choosedColumn + 1 < columns && gridStatues[choosedRow][choosedColumn+1] != ' ' && gridStatues[choosedRow][choosedColumn+1] != '*'&& grid[choosedRow][choosedColumn+1] != 'F'  /*&& gridOpennedStatues[choosedRow][choosedColumn+1] == '0'*/)
    {
        grid[choosedRow][choosedColumn +1] = gridStatues[choosedRow][choosedColumn +1] ;
        if (gridOpennedStatues[choosedRow][choosedColumn +1] == '0')
        {
            (*PnumOfOpennedCells)++;
            gridOpennedStatues[choosedRow][choosedColumn +1] = '1';
        }
        right = 1;
    }
    if (  choosedColumn + 1 < columns && grid[choosedRow][choosedColumn+1] == 'F')
    {
        right = 1;
    }
    while ( choosedRow + 1 < rows && grid[choosedRow+1][choosedColumn] != 'F' && gridStatues[choosedRow+1][choosedColumn] == ' ' && gridOpennedStatues[choosedRow+1][choosedColumn] == '0')
    {
        open(choosedRow+1, choosedColumn,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);

    }
    if ( choosedRow + 1 < rows && gridStatues[choosedRow+1][choosedColumn] != ' ' && gridStatues[choosedRow+1][choosedColumn] != '*' && grid[choosedRow+1][choosedColumn] != 'F'  /*&& gridOpennedStatues[choosedRow+1][choosedColumn] == '0'*/)
    {
        grid[choosedRow+1][choosedColumn] = gridStatues[choosedRow+1][choosedColumn] ;
        if (gridOpennedStatues[choosedRow+1][choosedColumn] == '0')
        {
            (*PnumOfOpennedCells)++;
            gridOpennedStatues[choosedRow+1][choosedColumn] = '1';
        }
        down = 1;
    }
    if (  choosedRow + 1 < rows && grid[choosedRow+1][choosedColumn] == 'F')
    {
        down = 1;
    }
    while ( choosedColumn - 1 >= 0 && grid[choosedRow][choosedColumn-1] != 'F' && gridStatues[choosedRow][choosedColumn-1] == ' ' && gridOpennedStatues[choosedRow][choosedColumn-1] == '0')
    {
        open(choosedRow, choosedColumn-1,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);

    }
    if (choosedColumn - 1 >= 0 && gridStatues[choosedRow][choosedColumn-1] != ' ' && gridStatues[choosedRow][choosedColumn-1] != '*' && grid[choosedRow][choosedColumn-1] != 'F'  /*&& gridOpennedStatues[choosedRow][choosedColumn-1] == '0'*/)
    {
        grid[choosedRow][choosedColumn-1] = gridStatues[choosedRow][choosedColumn-1] ;
        if (gridOpennedStatues[choosedRow][choosedColumn-1] == '0')
        {
            (*PnumOfOpennedCells)++;
            gridOpennedStatues[choosedRow][choosedColumn-1] = '1';
        }
        left = 1;
    }
    if (  choosedColumn - 1 >= 0 && grid[choosedRow][choosedColumn-1] == 'F')
    {
        left = 1;
    }


    // Accessing corners


    if ( right == 1 && up == 1 )
    {
        if (gridStatues[choosedRow-1][choosedColumn+1] != ' '  &&  grid[choosedRow-1][choosedColumn +1] != 'F' /*&& gridOpennedStatues[choosedRow-1][choosedColumn +1] == '0'*/)
        {
            grid[choosedRow-1][choosedColumn +1] = gridStatues[choosedRow-1][choosedColumn+1] ;
            if (gridOpennedStatues[choosedRow-1][choosedColumn +1] == '0')
            {
                (*PnumOfOpennedCells)++;
                gridOpennedStatues[choosedRow-1][choosedColumn +1]  = '1';
            }
        }
        else
        {
            open(choosedRow-1, choosedColumn+1,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);
        }
    }
    if ( right == 1 && down == 1 )
    {
        if (gridStatues[choosedRow+1][choosedColumn+1] != ' ' &&  grid[choosedRow+1][choosedColumn +1] != 'F' /*&&  gridOpennedStatues[choosedRow+1][choosedColumn +1] == '0'*/)
        {
            grid[choosedRow+1][choosedColumn +1] = gridStatues[choosedRow+1][choosedColumn+1] ;
            if (gridOpennedStatues[choosedRow+1][choosedColumn +1]== '0')
            {
                (*PnumOfOpennedCells)++;
                gridOpennedStatues[choosedRow+1][choosedColumn +1] = '1';
            }
        }
        else
        {
            open(choosedRow+1, choosedColumn+1,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);
        }
    }
    if ( left == 1 && up == 1 )
    {
        if (gridStatues[choosedRow-1][choosedColumn-1] != ' '  &&  grid[choosedRow-1][choosedColumn -1] != 'F'/* &&  gridOpennedStatues[choosedRow-1][choosedColumn -1] == '0'*/)
        {
            grid[choosedRow-1][choosedColumn -1] = gridStatues[choosedRow-1][choosedColumn-1] ;
            if (gridOpennedStatues[choosedRow-1][choosedColumn -1] == '0')
            {
                (*PnumOfOpennedCells)++;
                gridOpennedStatues[choosedRow-1][choosedColumn -1]  = '1';
            }
        }
        else
        {
            open(choosedRow-1, choosedColumn-1,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);
        }
    }
    if ( left == 1 && down == 1 )
    {
        if (gridStatues[choosedRow+1][choosedColumn-1] != ' '  &&  grid[choosedRow+1][choosedColumn -1] != 'F' /*&&  gridOpennedStatues[choosedRow+1][choosedColumn -1] == '0'*/)
        {
            grid[choosedRow+1][choosedColumn -1] = gridStatues[choosedRow+1][choosedColumn-1] ;
            if (gridOpennedStatues[choosedRow+1][choosedColumn -1]== '0')
            {
                (*PnumOfOpennedCells)++;
                gridOpennedStatues[choosedRow+1][choosedColumn -1]  = '1';
            }
        }
        else
        {
            open(choosedRow+1, choosedColumn-1,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);
        }
    }


}





// opening function to open a cell
void open(int choosedRow, int choosedColumn,int rows, int columns,char grid[rows][columns],char gridStatues[rows][columns],char gridOpennedStatues[rows][columns],int * Pplaying, int * PnumOfOpennedCells )
{
    // checking if it's not open opened
    if ( grid[choosedRow][choosedColumn] == 'X' || grid[choosedRow][choosedColumn] == '?')
    {
        if ( gridStatues[choosedRow][choosedColumn] == ' ')
        {

            grid[choosedRow][choosedColumn] = gridStatues[choosedRow][choosedColumn] ;
            gridOpennedStatues[choosedRow][choosedColumn] = '1';
            (*PnumOfOpennedCells)++;
            rec(choosedRow, choosedColumn,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);


        }
        else if (gridStatues[choosedRow][choosedColumn] != '*')

        {
            grid[choosedRow][choosedColumn] = gridStatues[choosedRow][choosedColumn] ;
            gridOpennedStatues[choosedRow][choosedColumn] = '1';
            (*PnumOfOpennedCells)++;


        }
        else
        {
            *Pplaying = 0;
            criticalChoosedRow = choosedRow;
            criticalChoosedColumn = choosedColumn;
        }

    }
    // if it's opened before
    else if (grid[choosedRow][choosedColumn] != 'F')
    {
        reopen(choosedRow, choosedColumn,rows, columns,grid,gridStatues,gridOpennedStatues,Pplaying,PnumOfOpennedCells);
    }
    // in case there were any other conditions
    /*else
    {

    }*/


}


// Operations to be done in the first move for the player (first opened cell).
void firstMovefun(int * PfirstMove,int choosedRow, int choosedColumn,int rows, int columns, char gridStatues[rows][columns])
{

    int numberOfMines = 1 + (rows*columns)/10;
    int randomRows[numberOfMines];
    int randomColumns[numberOfMines];
    // do not forget to replace the start point with the time function

    // randomizing the mines
    int i = 0;
    while ( i < numberOfMines)
    {
        int randomRow = (rand()% rows) ;
        int randomColumn = (rand()% columns);
        int j = 0;
        int repeated = 0;
        while ( j < i+1 && !repeated  )
        {
            // replacing mines if it came to the opened cell or a repeated random value
            if ( (randomRow == randomRows[j]  &&  randomColumn == randomColumns[j])        ||      (randomRow == choosedRow  &&  randomColumn == choosedColumn)   )
            {
                repeated = 1;
                break;
            }
            j++;
        }
        if (!repeated)
        {
            randomRows[i] = randomRow;
            randomColumns[i] = randomColumn;
        }
        else
        {
            continue;
        }


        i++;
    }



    // calculating the number of mines around every cell.
    *PfirstMove = 0;
    int k = 0;
    for ( k ; k < numberOfMines ; k++)
    {
        gridStatues[randomRows[k]][randomColumns[k]] = '*';
    }
    i = 0 ;
    for ( i ; i < rows ; i++)
    {
        int j = 0;
        for ( j ; j < columns ; j++)
        {
            if ( gridStatues[i][j] != '*')
            {

                int counter = 0;
                int i_initial = i-1;
                if (i_initial < 0)i_initial++;



                int i_final = i+1;
                if (i_final > rows )i_final--;

                int j_final = j+1;
                if (j_final >= columns)j_final--;




                for ( i_initial ; i_initial <= i_final  ; i_initial++)
                {
                    int j_initial = j-1;
                    if (j_initial < 0)j_initial++;

                    for ( j_initial ; j_initial <= j_final ; j_initial++)
                    {
                        if (i_initial != i   ||   j_initial != j)
                        {
                            if (gridStatues[i_initial][j_initial] == '*')
                            {
                                counter++;
                            }
                        }
                    }
                }

                if (counter == 0)
                {
                    gridStatues[i][j] = ' ';
                }
                else
                {
                    gridStatues[i][j] = '0' + counter;
                }
            }
        }
    }











}


