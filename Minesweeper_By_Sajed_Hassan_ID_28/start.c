#include "start.h"
#include "main.h"
#include "thread.h"


// the main function (main loop).
void start(int newGame)
{

    //=======================================INITIALIZING SECTION ===========================================

    // to check if the player won
    int numOfOpennedCells = 0;

    //only needed when loading
    int numOfChoosedFile;

    //that would be changed in the case of loading to the value of zero
    int firstMove = 1;


    // initializing the size
    if (newGame)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //fflush(stdin);
        while (1)
        {
        printf("\n\n\n                                                                 Enter the number of rows and columns ( 2 : 30 ): ");
        while (scanf(" %d %d",&rows,&columns) != 2  || rows > 30 || columns > 30 || rows < 2 || columns < 2)
        {
            while( getchar() != '\n'  );
            SetConsoleTextAttribute(hConsole, 252);
            printf("\n                                                                 Enter the number of rows and columns (correctly) ( 2 : 30 ): ");
            SetConsoleTextAttribute(hConsole, 249);
        }
        char garbage = getchar();
        if (garbage != '\n')
        {
            fflush(stdin);
            continue;
        }
        break;
        }
// this to get the new line as we are reading a char in the next scanf

    }
    else
    {
        // initializing the size
        numOfChoosedFile = loadRowsAndColumns(&rows,&columns,&timePassedInMins, &timePassedInSecs, &numOfMoves,&numOfFlags,&numOfQ,&numOfOpennedCells);
        if (numOfChoosedFile == -1)
            return;
        firstMove = 0;
        //printf("%d %d %d %d %d %d %d %d",rows,columns,timePassedInMins,timePassedInSecs,numOfMoves,numOfFlags,numOfQ,numOfOpennedCells);
    }

    // in case of loading we need to initialize the time before making any move as he already started before and there is no first lucky move any more
    if (!newGame)
    {
        time(&currenttime);
        mytime = localtime(&currenttime);
        startingMin = (mytime->tm_min) - (timePassedInMins % 60);
        startingSec = (mytime->tm_sec) - timePassedInSecs;
        startingHour = (mytime->tm_hour) - (timePassedInMins / 60);

    }


    char grid[rows][columns];
    char gridStatues[rows][columns];
    char gridOpennedStatues [rows][columns];

    if ( !newGame)
    {
        //to check for being idle before the player makes his first move --------->> (in case of loading ) << --------
        garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);
    }

    // initializing the grid
    if (newGame)
    {
        int i = 0;
        int j = 0 ;
        for (i ; i < rows ; i++)
        {
            for ( j ; j < columns ; j++)
            {
                gridOpennedStatues[i][j] = '0';
            }
            j = 0;
        }

        i = 0;
        j=0;
        for (i ; i < rows ; i++)
        {
            for ( j ; j < columns ; j++)
            {
                grid[i][j] = 'X';
            }
            j = 0;
        }
    }
    else
    {
        // loading the saved grids (DATA)
        loadGrids(rows, columns, grid,numOfChoosedFile);
        loadGridsStatues(rows, columns,gridStatues,numOfChoosedFile);
        loadGridsOpenedStatues(rows, columns, gridOpennedStatues,numOfChoosedFile);
        testFile(rows, columns, gridStatues);
    }

    printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);





    //====================================== ACTIONS SECTION =================================================
    char action[MAXCHAR];

    int choosedRow, choosedColumn;

    // to check if the player loses
    int playing = 1;


    // =====>>>> MAIN LOOP <<<<=====
    while (playing  &&  numOfOpennedCells < ((rows*columns)-(rows*columns/10)-1))
    {

        // useless
        /*if (!newGame)
        {
            newGame = 1;
        }*/


        // getting the action
        printf("\n                                                                 O to open,  F to put a flag,  q to put a ?   and  v to save  (ex : o 1 1) // R to return\n");
        //printf("                                                                 Make an Action : ");

        // forcing the player to start with an OPENING action
        if ( firstMove)
        {



            while (1)
            {

                printf("\n                                                                 Make an Action : ");

                scanf("%s",action);

                strupr(action);
                if ( strcmp(action, "O")  )
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 252);
                    printf("                                                                 You must (open) a cell in the first move! \n");
                    SetConsoleTextAttribute(hConsole, 249);
                    while(getchar() != '\n');
                    continue;
                }
                if (scanf("%d %d",&choosedRow, &choosedColumn) != 2 || choosedRow > rows-1 || choosedColumn > columns-1 || choosedRow < 0 || choosedColumn < 0 )
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 252);
                    printf("                                                                 This is not an Available Action, Please try again(correctly).\n");
                    SetConsoleTextAttribute(hConsole, 249);
                    while(getchar() != '\n');
                    continue;
                }
                char garbage = getchar();
                if (garbage != '\n')
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 252);
                    printf("                                                                 This is not an Available Action, Please try again(correctly).\n");
                    SetConsoleTextAttribute(hConsole, 249);
                    fflush(stdin);
                    continue;
                }

                break;


                //getchar();

            }
        }
        // other actions after the first move has made (other moves except for the first)
        else
        {


            while (1)
            {

                garbage = pthread_cancel(timer_th);
                garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);

                printf("\n                                                                 Make an Action : ");

                scanf("%s",action);
                if (!strcmp(action, "v")  ||  !strcmp(action, "V"))
                {
                    if (getchar() != '\n')
                    {
                        fflush(stdin);
                        continue;
                    }

                    strupr(action);
                    break;
                }
                else if (!strcmp(action, "r")  ||  !strcmp(action, "R"))
                {
                    strupr(action);
                    break;
                }

                strupr(action);
                if ( strcmp(action, "F") && strcmp(action, "U") &&  strcmp(action, "O")  &&  strcmp(action, "Q") )
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 252);
                    printf("                                                                 This is not an Available Action, Please try again(correctly).\n");
                    SetConsoleTextAttribute(hConsole, 249);
                    while(getchar() != '\n');
                    continue;
                }
                if (scanf("%d %d",&choosedRow, &choosedColumn) != 2 || choosedRow > rows-1 || choosedColumn > columns-1 || choosedRow < 0 || choosedColumn < 0 )
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 252);
                    printf("                                                                 This is not an Available Action, Please try again(correctly).\n");
                    SetConsoleTextAttribute(hConsole, 249);
                    while(getchar() != '\n');
                    continue;
                }
                char garbage = getchar();
                if (garbage != '\n')
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 252);
                    printf("                                                                 This is not an Available Action, Please try again(correctly).\n");
                    SetConsoleTextAttribute(hConsole, 249);
                    fflush(stdin);
                    continue;
                }
                break;


                //getchar();

            }
        }

        // flushing the buffer
        //while(getchar() != '\n');






        // opening action
        if ( strcmp(action, "O") == 0 )
        {
            // in case of starting a new game we need to initialize the time after making his first move and only once (point of starting playing).
            if (newGame && firstMove)
            {
                time(&currenttime);
                mytime = localtime(&currenttime);
                startingMin = mytime->tm_min;
                startingSec = mytime->tm_sec;
                startingHour = mytime->tm_hour;
            }

            // This checks for any change happens to calculate the numOfMoves
            int diffrenceInTheGridChecker = numOfOpennedCells;


            garbage = pthread_cancel(timer_th);
            garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);


            // getting the current time
            time(&currenttime);
            mytime = localtime(&currenttime);
            int currentsec = mytime->tm_sec ;
            int currentmin = mytime->tm_min;
            int currenthour = mytime->tm_hour;
            int differenceInSec = (currentsec-startingSec)+60*(currentmin-startingMin)+3600*(currenthour-startingHour);
            timePassedInMins = differenceInSec / 60;
            timePassedInSecs = differenceInSec % 60;








            // first move operations.
            if (firstMove)
            {

                int i = 0;
                int j=0;
                for (i ; i < rows ; i++)
                {
                    for ( j ; j < columns ; j++)
                    {
                        gridStatues[i][j] = 'X';
                    }
                    j = 0;
                }


                firstMovefun(&firstMove,choosedRow, choosedColumn,rows, columns, gridStatues);

                // a file containing the SOLUTION
                testFile(rows, columns, gridStatues);

                open(choosedRow, choosedColumn,rows, columns,grid,gridStatues,gridOpennedStatues,&playing,&numOfOpennedCells);

                if ( diffrenceInTheGridChecker != numOfOpennedCells)
                {
                    numOfMoves++;
                }


                printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);
                //printGrid(rows, columns, gridStatues,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);

            }
            else
            {
                // ordinary opening action
                open(choosedRow, choosedColumn,rows, columns,grid,gridStatues,gridOpennedStatues,&playing,&numOfOpennedCells);

                if ( diffrenceInTheGridChecker != numOfOpennedCells)
                {
                    numOfMoves++;
                }
                printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);

            }

        }


        // Putting a flag
        else if ( strcmp(action, "F") == 0 )
        {
            //checking for being idle ..
            garbage = pthread_cancel(timer_th);
            garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);



            if (gridOpennedStatues[choosedRow][choosedColumn] == '0' && grid[choosedRow][choosedColumn] == 'X')
            {
                grid[choosedRow][choosedColumn] = 'F';
                numOfFlags++;


                numOfMoves++;

                //getting the time
                time(&currenttime);
                mytime = localtime(&currenttime);
                int currentsec = mytime->tm_sec ;
                int currentmin = mytime->tm_min;
                int currenthour = mytime->tm_hour;
                int differenceInSec = (currentsec-startingSec)+60*(currentmin-startingMin)+3600*(currenthour-startingHour);
                timePassedInMins = differenceInSec / 60;
                timePassedInSecs = differenceInSec % 60;

                printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);
            }





        }

        // putting a ????????
        else if ( strcmp(action, "Q") == 0 )
        {


            garbage = pthread_cancel(timer_th);
            garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);



            if (gridOpennedStatues[choosedRow][choosedColumn] == '0' && grid[choosedRow][choosedColumn] == 'X')
            {
                grid[choosedRow][choosedColumn] = '?';
                numOfQ++;


                numOfMoves++;


                time(&currenttime);
                mytime = localtime(&currenttime);
                int currentsec = mytime->tm_sec ;
                int currentmin = mytime->tm_min;
                int currenthour = mytime->tm_hour;
                int differenceInSec = (currentsec-startingSec)+60*(currentmin-startingMin)+3600*(currenthour-startingHour);
                timePassedInMins = differenceInSec / 60;
                timePassedInSecs = differenceInSec % 60;


                printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);
            }






        }


        // removing a flag or a ?????
        else if ( strcmp(action, "U") == 0 )
        {



            garbage = pthread_cancel(timer_th);
            garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);




            if (gridOpennedStatues[choosedRow][choosedColumn] == '0' && (grid[choosedRow][choosedColumn] == 'F'  ||  grid[choosedRow][choosedColumn] == '?'))
            {
                if (grid[choosedRow][choosedColumn] == 'F')
                {
                    numOfFlags--;
                }
                if (grid[choosedRow][choosedColumn] == '?')
                {
                    numOfQ--;
                }
                grid[choosedRow][choosedColumn] = 'X';



                numOfMoves++;


                time(&currenttime);
                mytime = localtime(&currenttime);
                int currentsec = mytime->tm_sec ;
                int currentmin = mytime->tm_min;
                int currenthour = mytime->tm_hour;
                int differenceInSec = (currentsec-startingSec)+60*(currentmin-startingMin)+3600*(currenthour-startingHour);
                timePassedInMins = differenceInSec / 60;
                timePassedInSecs = differenceInSec % 60;

                printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);
            }







        }

        // saving the game
        else if ( strcmp(action, "V") == 0 )
        {


            time(&currenttime);
            mytime = localtime(&currenttime);
            int currentsec = mytime->tm_sec ;
            int currentmin = mytime->tm_min;
            int currenthour = mytime->tm_hour;
            int differenceInSec = (currentsec-startingSec)+60*(currentmin-startingMin)+3600*(currenthour-startingHour);
            timePassedInMins = differenceInSec / 60;
            timePassedInSecs = differenceInSec % 60;

            garbage = pthread_cancel(timer_th);
            garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);

            save(rows, columns, grid,gridStatues,gridOpennedStatues,timePassedInMins,timePassedInSecs, numOfMoves,numOfFlags,numOfQ,numOfOpennedCells);
            printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);



        }

        if ( strcmp(action, "R") == 0 )
        {
            fflush(stdin);
            garbage = pthread_cancel(timer_th);
            return;
        }


    }
    //pthread_join(timer_th,NULL);    No need to join



    // checking if the player WON
    if (numOfOpennedCells == (rows*columns - (rows*columns/10) -1 )   && playing == 1   )
    {

        // stopping the thread
        garbage = pthread_cancel(timer_th);


        int i,j;
        for (i = 0 ; i < rows ; i++)
        {
            for ( j = 0 ; j < columns ; j++)
            {
                if (grid[i][j] == 'X')
                    grid[i][j] = 'F';
            }
        }
        printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);
        printf("\n\n\n                                                                 ****     ****     ****    ***    *******     ****\n"
               "                                                                 ****    ******    ****    ***    ********    ****\n"
               "                                                                 ****   ********   ****    ***    **** ****   ****\n"
               "                                                                 ****  ****  ****  ****    ***    ****  ****  ****\n"
               "                                                                 **** ****    **** ****    ***    ****   **** ****\n"
               "                                                                 ********      ********    ***    ****    ********\n"
               "                                                                 *******        *******    ***    ****     *******\n");

        char winnerName[MAXCHAR];
        printf("\n\n                                                                 Please enter your (first) name : ");
        scanf("%s", winnerName);
        fflush(stdin);

        // no comment
        getTheScore(winnerName);
        showScores(winnerName);




    }


    // checking if the player LOSE
    if ( playing == 0)
    {
        // stopping the thread
        garbage = pthread_cancel(timer_th);

        int i,j;
        for (i = 0 ; i < rows ; i++)
        {
            for ( j = 0 ; j < columns ; j++)
            {
                if (grid[i][j] == 'F' && gridStatues[i][j] != '*')
                    grid[i][j] = '-';
                if (grid[i][j] != 'F' && gridStatues[i][j] == '*')
                    grid[i][j] = 'M';
                if (grid[i][j] == 'F' && gridStatues[i][j] == '*')
                    grid[i][j] = '*';
            }
        }
        grid[criticalChoosedRow][criticalChoosedColumn] = '!';
        printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);



        printf("\n\n\n");
        printf("                                                                 ****          ***********   ***********   ************\n"
               "                                                                 ****          ***********   ***********   ************\n"
               "                                                                 ****          ****   ****   ***           ***      ***\n"
               "                                                                 ****          ****   ****   ***********   ************\n"
               "                                                                 ****          ****   ****   ***********   ************\n"
               "                                                                 ****          ****   ****           ***   ***\n"
               "                                                                 ***********   ***********   ***********   ************\n"
               "                                                                 ***********   ***********   ***********   ************\n");
    }
}
