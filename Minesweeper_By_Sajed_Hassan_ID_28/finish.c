#include "finish.h"


// A structure to get the saved scores to check if the player has an old score
typedef struct
{
    char * name;
    int savedScore ;
} Entry1;



// A structure for players and there scores, to be used is case of showing scores (getting them from files)
typedef struct
{
    char * name;
    int playerScore ;
} Entry2;




// this function show the score from the main menu & after a player win a game
void showScores(char nameOfWinner_InCaseOfWinning[MAXCHAR])
{
    // to handle the console (change it's colors).
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    //getting the number of the saved scores
    FILE * numOfScores = fopen("numOfScores.txt","r");
    int entryCount;
    fscanf(numOfScores,"%i",&entryCount);
    fclose(numOfScores);



    // checking if there is any saved score
    if (entryCount == 0)
    {
        printf("\n\n\n                                                                           No scores found !\n\n\n");
        return;
    }


    //getting the scores from the file where they are saved in into an array of structures.
    FILE * scores = fopen("scores.txt","r");
    Entry2 * entries2 = malloc(sizeof(Entry2) * entryCount);
    int i = 0;
    for (i ; i < entryCount ; i++)
    {
        int nameLen;
        fscanf(scores,"%i",&nameLen);
        entries2[i].name = malloc(sizeof(char) * (nameLen + 1));
        fscanf(scores,"%s %i",entries2[i].name, &entries2[i].playerScore);
    }



    // ================================ SORTING the indexes depending on the scores ============================
    // we are doing this in order not to change the allocated size of memory.
    int arrayOfSortedIndexes[entryCount];
    int j;
    int maxIndex;
    for ( i = 0 ; i < entryCount ; i++)
    {
        int max = -1;
        for ( j = 0 ; j < entryCount ; j++)
        {
            int l;
            int found = 0;
            for ( l = 0 ; l < i ; l++)
            {
                if (j == arrayOfSortedIndexes[l])
                {
                    found = 1;
                }

            }
            if (found)
            {
                continue;
            }
            if ( entries2[j].playerScore > max)
            {
                max = entries2[j].playerScore;
                maxIndex = j;
            }
        }
        arrayOfSortedIndexes[i] = maxIndex;
    }


    // printing the saved scores
    printf("\n\n\n\n\n");
    printf("                                                            ==================================================================\n");
    printf("                                                            Player's rank\t\tPlayer's name\t\tPlayer's score\n\n");

    // getting high score to check if the players has got a NEW HIGH SCORE.
    int highScore = entries2[0].playerScore;
    int highScoreIndex = 0;
    i = 1 ;
    for ( i ; i < entryCount ; i++)
    {
        if ( entries2[i].playerScore > highScore)
        {
            highScore = entries2[i].playerScore;
            highScoreIndex = i;
        }
    }


    int gotNewRecord = 0;
    i = 0 ;
    for ( i ; i < entryCount ; i++)
    {
        if ( !strcasecmp(entries2[arrayOfSortedIndexes[i]].name, nameOfWinner_InCaseOfWinning) )
        {
            if (entries2[arrayOfSortedIndexes[i]].playerScore == highScore)
                gotNewRecord = 1;
            SetConsoleTextAttribute(hConsole, 252);
            printf("                                                                 %d\t\t\t%s\t\t\t\t%d\n",i+1,entries2[arrayOfSortedIndexes[i]].name,entries2[arrayOfSortedIndexes[i]].playerScore);
            SetConsoleTextAttribute(hConsole, 249);
        }
        else
            printf("                                                                 %d\t\t\t%s\t\t\t\t%d\n",i+1,entries2[arrayOfSortedIndexes[i]].name,entries2[arrayOfSortedIndexes[i]].playerScore);
    }


    printf("                                                            ==================================================================\n");



    // showing that the player has got a new high score .
    if (gotNewRecord)
    {
        SetConsoleTextAttribute(hConsole, 252);
        int k = 3;
        while ( k > 0)
        {
            printf("\r                                                                                   ==> New High Score <==");
            setTimeout(750);
            printf("\r                                                                                                            ");
            setTimeout(750);
            k--;
        }
        printf("\r                                                                                   ==> New High Score <==");
        SetConsoleTextAttribute(hConsole, 249);
    }
    printf("\n\n\n\n\n");


    // freeing the memory of the array
    fclose(scores);
    for ( i = 0 ; i < entryCount ; i++)
        free(entries2[i].name);
    free(entries2);

}




// A logo for the game to be printed in the main menu
void logo()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 252);
    printf("\n\n\n\n\n\n\n\n\n");
    printf("                                                                  ******** *******      *********\n");
    printf("                                                                 ******************    ***********\n");
    printf("                                                                 ****   ****   ****    ****\n");
    printf("                                                                 ****   ****   ****    ****\n");
    printf("                                                                 ****   ****   ****    ***********\n");
    printf("                                                                 ****   ****   ****      **********\n");
    printf("                                                                 ****   ****   ****           *****\n");
    printf("                                                                 ****   ****   ****           *****\n");
    printf("                                                                 ****   ****   ****    ***********\n");
    printf("                                                                 ****   ****   ****     *********\n");

    SetConsoleTextAttribute(hConsole, 249);



}



// The available options in the main menu.
void mainMenu()
{
    printf("\n\n                                                                 ............ MAIN MENU ............");

    printf("\n\n\n                                                                 1- Type S to START a new game.\n\n");
    printf("                                                                 2- Type L to LOAD a saved game.\n\n");
    printf("                                                                 3- Type H to SHOW players' progresses.\n\n");
    printf("                                                                 4- Type Q to quit the game.\n");
    printf("\n\n                                                                 ...................................\n");

}






// getting the WINNER NAME and calculating his SCORE .
void getTheScore(char winnerName[MAXCHAR])
{

    // calculating the winner score.
    int playerScore;
    if ((timePassedInSecs+(timePassedInMins*60)) != 0)
    {
        playerScore = (pow(rows, 4) * pow(columns, 4)) / ( (timePassedInSecs+(timePassedInMins*60) )  *  numOfMoves );
    }
    else
    {
        playerScore = (pow(rows, 4) * pow(columns, 4)) / ( 1  *  numOfMoves );
    }



    // getting the number of saved scores.
    FILE * numOfScoresFile;
    numOfScoresFile = fopen("numOfScores.txt", "r");
    int numOfScores;
    fscanf(numOfScoresFile, "%d", &numOfScores);
    fclose(numOfScoresFile);



    // checking if there is any saved scores
    if ( !numOfScores )
    {
        // The case : No saved scores found
        FILE * scores = fopen("scores.txt","a");
        fprintf(scores,"%d %s %d\n",strlen(winnerName),winnerName,playerScore);
        //fprintf(scores,"");
        fclose(scores);

        fopen("numOfScores.txt", "w");
        fprintf(numOfScoresFile, "%d", numOfScores+1);
        fclose(numOfScoresFile);
    }
    else
        // The case : if there were any saved scores
    {
        // getting the number of saved scores .
        int entryCount = numOfScores;
        FILE * scores = fopen("scores.txt","r");

        // allocating a memory for handling saved scores.
        Entry1 * entries1 = malloc(sizeof(Entry1) * entryCount);


        int i = 0;
        int firstWin = 1;
        for (i ; i < entryCount ; i++)
        {
            int nameLen;
            fscanf(scores,"%i",&nameLen);
            entries1[i].name = malloc(sizeof(char) * (nameLen + 1));
            fscanf(scores,"%s %i",entries1[i].name, &entries1[i].savedScore);
            //searching for the winner name if he had an old score
            if (!strcasecmp(entries1[i].name,winnerName))
            {
                firstWin  = 0;
                (entries1[i].savedScore) += playerScore ;
            }
        }
        fclose(scores);


        if (firstWin)
        {
            // saving winner name to list of winners
            fopen("scores.txt", "a");
            fprintf(scores,"%d %s %d\n",strlen(winnerName),winnerName,playerScore);
            fclose(scores);

            // increasing the number of saved scores by 1
            fopen("numOfScores.txt", "w");
            fprintf(numOfScoresFile, "%d", numOfScores+1);
            fclose(numOfScoresFile);
        }
        else
        {
            // if not the first win for the player
            fopen("scores.txt", "w");

            // updating the current list of winners
            for ( i = 0 ; i < entryCount ; i++)
            {
                fprintf(scores,"%d %s %d\n",strlen(entries1[i].name),entries1[i].name,entries1[i].savedScore);
            }
            fclose(scores);
        }

        // freeing the allocated memory
        for ( i = 0 ; i < entryCount ; i++)
            free(entries1[i].name);
        free(entries1);

    }


}




