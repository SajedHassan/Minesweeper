#include "saveAndLoad.h"
#include "main.h"
#include "thread.h"
//A Structure for getting the files associated with the game to be loaded.
typedef struct
{
    char * name;
    int numOfUserFile;
} Entry;





// loading the size and the beside infos.(ex : numOfMoves and so on ).
int loadRowsAndColumns(int * Prows, int * Pcolumns,int * PtimePassedInMins, int * PtimePassedInSecs, int*PnumOfMoves,int*PnumOfFlags,int*PnumOfQ,int*PnumOfOpennedCells)
{
    char loaded_game[MAXCHAR];
    int numOfTheChoosedFile;

    //opening the file containing the number of the saved games
    FILE * NOSG = fopen("NOSG.txt","r");
    int entryCount;
    fscanf(NOSG,"%i",&entryCount);
    fclose(NOSG);


    // checking if there were any saved gamed
    if ( entryCount == 0)
    {
        printf("\n\n\n\n\n                                                                 There is no saved games at the moment !\n\n\n\n");
        return -1;
    }

    //printing the saved games for the user to choose a game to be loaded
    FILE * users = fopen("users.txt","r");

    // allocating a memory for an array of structures to get the saved games with in it.
    Entry * entries = malloc(sizeof(Entry) * entryCount);

    printf("\n\n\n                                                                 ============================");
    int i = 0;
    for (i ; i < entryCount ; i++)
    {
        int nameLen;
        // getting the LEN of every player name to allocate memory for it.
        fscanf(users,"%i",&nameLen);
        entries[i].name = malloc(sizeof(char) * (nameLen + 1));
        fscanf(users,"%s %3d",entries[i].name, &entries[i].numOfUserFile);

        printf("\n\n                                                                 %i. %s\n",i+1,entries[i].name );

    }
    printf("\n                                                                 ============================");


    //getting the number of the file of the choose game to be loaded
    int found_savedGame = 0;
    int firstSearch = 1;
    while (!found_savedGame)
    {
        if (firstSearch)
        {
            printf("\n\n\n\n                                                                 please choose a game to be load : ");
            firstSearch = 0;
        }
        else
        {
            printf("\n                                                                 Not found! please choose a game to load (from the list above): ");
        }
        gets(loaded_game);
        fflush(stdin);
        i = 0;
        for (i ; i < entryCount ; i++)
        {
            if (!strcasecmp(entries[i].name,loaded_game))
            {
                numOfTheChoosedFile = entries[i].numOfUserFile;
                found_savedGame = 1;
                break;
            }
        }
    }
    //getting the name of the file that we just got it's number
    char nameOfChoosedGameFile[FILENAME_MAX];
    snprintf(nameOfChoosedGameFile,FILENAME_MAX,"savedGrid%03d.txt",numOfTheChoosedFile);
    //freeing the memory
    fclose(users);
    for ( i = 0 ; i < entryCount ; i++)
        free(entries[i].name);
    free(entries);
    //opening the file that the game is saved in
    FILE * choosedGame = fopen(nameOfChoosedGameFile,"r");
    //reading data
    fscanf(choosedGame,"%d %d %d %d %d %d %d %d",Prows,Pcolumns,PtimePassedInMins,PtimePassedInSecs,PnumOfMoves,PnumOfFlags,PnumOfQ,PnumOfOpennedCells);
    fclose(choosedGame);
    return numOfTheChoosedFile;
}





// loading the main grid
void loadGrids(int rows, int columns, char grid[rows][columns],int numOfChoosedFile)
{

    int a,s,d,f,g,h,o,k,q1,q2,q3;
    //getting the name of the file that we just got it's number
    char nameOfChoosedGameFile[FILENAME_MAX];
    snprintf(nameOfChoosedGameFile,FILENAME_MAX,"savedGrid%03d.txt",numOfChoosedFile);

    //opening the file that the game is saved in
    FILE * choosedGame = fopen(nameOfChoosedGameFile,"r");
    //reading data
    //fseek(choosedGame,16,SEEK_SET);
    fscanf(choosedGame,"%d %d %d %d %d %d %d %d ",&a,&s,&d,&f,&g,&h,&o,&k);
    // we cannot use seek as the pre data is changing every time we save a game so we do not the spaces to be seek
    printf("\n");

    int j;
    int i;
    int temp;
    for (i=0 ; i < rows ; i++)
    {
        j= 0;
        for ( j ; j < columns ; j ++)
        {
            fscanf(choosedGame,"%d ",&temp);
            grid[i][j] = temp;
        }
        printf("\n");


    }
    //int a1 = 1, b1 = 2, c1 = 3, d1 = 4,e1 = 5 ;

    close(choosedGame);


}

// loading the opened grid. (THE SOLUTION)
void loadGridsStatues(int rows, int columns,char gridStatues[rows][columns],int numOfChoosedFile)
{

    //getting the name of the file that we just got it's number
    char nameOfChoosedGameFile1[FILENAME_MAX];
    snprintf(nameOfChoosedGameFile1,FILENAME_MAX,"savedGridStatues%03d.txt",numOfChoosedFile);

    //opening the file that the game is saved in
    FILE * choosedGame1 = fopen(nameOfChoosedGameFile1,"r");
    //reading data
    printf("\n");

    int j;
    int i;
    int temp;
    for (i=0 ; i < rows ; i++)
    {
        j= 0;
        for ( j ; j < columns ; j ++)
        {
            fscanf(choosedGame1,"%d ",&temp);
            gridStatues[i][j] = temp;
        }

        printf("\n");

    }
    //int a = 1, b = 2, c = 3, d = 4,e = 5 ;


    fclose(choosedGame1);


}


// loading grid of information (OPENED AND NOT OPENED)
void loadGridsOpenedStatues(int rows, int columns,char gridOpennedStatues[rows][columns],int numOfChoosedFile)
{

    //getting the name of the file that we just got it's number
    char nameOfChoosedGameFile2[FILENAME_MAX];
    snprintf(nameOfChoosedGameFile2,FILENAME_MAX,"savedGridOpenedStatues%03d.txt",numOfChoosedFile);

    //opening the file that the game is saved in
    FILE * choosedGame2 = fopen(nameOfChoosedGameFile2,"r");
    //reading data
    printf("\n");

    int j;
    int i;
    int temp;
    for (i=0 ; i < rows ; i++)
    {
        j= 0;
        for ( j ; j < columns ; j ++)
        {
            fscanf(choosedGame2,"%d ",&temp);
            gridOpennedStatues[i][j] = temp ;
        }

        printf("\n");

    }


    fclose(choosedGame2);


}



// saving the game
void save(int rows, int columns, char grid[rows][columns],char gridStatues[rows][columns],char gridOpennedStatues[rows][columns],int timePassedInMins, int timePassedInSecs, int numOfMoves,int numOfFlags,int numOfQ,int numOfOpennedCells)
{
    // getting the player name
    printf("                                                                 please enter your (first) name : ");
    char player_name_Inputted[MAXCHAR];
    scanf("%s", player_name_Inputted);
    fflush(stdin);
    garbage = pthread_cancel(timer_th);
    garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);
    strupr(player_name_Inputted);


    // getting the number of saved gamed already
    FILE * NOSG = fopen("NOSG.txt","r");
    int nummberOfSavedGames;
    fscanf(NOSG, "%d",&nummberOfSavedGames);
    fclose(NOSG);

    //like using int firstSave = !nummberOfSavedGames .... then using if (firstSave)
    // if there was no saved games
    if ( !nummberOfSavedGames )
    {
        // saving the player name and his ID
        FILE * users = fopen("users.txt","a");
        fprintf(users,"%d %s %03d\n",strlen(player_name_Inputted),player_name_Inputted,nummberOfSavedGames);
        //fprintf(users,"");   useless
        fclose(users);

        // giving names for the files to save to game in it.
        char savedFileName1[FILENAME_MAX];
        snprintf(savedFileName1,FILENAME_MAX,"savedGrid%03d.txt",nummberOfSavedGames);

        char savedFileName2[FILENAME_MAX];
        snprintf(savedFileName2,FILENAME_MAX,"savedGridStatues%03d.txt",nummberOfSavedGames);

        char savedFileName3[FILENAME_MAX];
        snprintf(savedFileName3,FILENAME_MAX,"savedGridOpenedStatues%03d.txt",nummberOfSavedGames);


        // increasing the number of saved games by 1
        fopen("NOSG.txt","w");
        nummberOfSavedGames++;
        fprintf(NOSG,"%d",nummberOfSavedGames);
        fclose(NOSG);


        // saving date (printing them to files)
        FILE * savedGrid;
        savedGrid = fopen(savedFileName1,"w");
        int i,j;
        fprintf(savedGrid,"%d %d %d %d %d %d %d %d\n",rows, columns,timePassedInMins,timePassedInSecs,numOfMoves,numOfFlags,numOfQ,numOfOpennedCells);
        for (i=0 ; i < rows ; i++)
        {
            for ( j=0 ; j < columns ; j ++)
            {
                fprintf(savedGrid,"%d ",grid[i][j]);
            }
            fprintf(savedGrid, "\n");
        }
        fclose(savedGrid);

        FILE * savedGridStatues;
        savedGridStatues = fopen(savedFileName2,"w");
        for (i=0 ; i < rows ; i++)
        {
            for ( j=0 ; j < columns ; j ++)
            {
                fprintf(savedGridStatues,"%d ",gridStatues[i][j]);
            }
            fprintf(savedGridStatues, "\n");
        }
        fclose(savedGridStatues);

        FILE * savedGridOpenedStatues;
        savedGridOpenedStatues = fopen(savedFileName3,"w");
        for (i=0 ; i < rows ; i++)
        {
            for ( j=0 ; j < columns ; j ++)
            {
                fprintf(savedGridOpenedStatues,"%d ",gridOpennedStatues[i][j]);
            }
            fprintf(savedGridOpenedStatues, "\n");
        }
        fclose(savedGridOpenedStatues);
    }
    else
    {

        // if there were any saved games
        int entryCount = nummberOfSavedGames;

        // allocating memory for the an array of structures to get the date to handle it
        FILE * users = fopen("users.txt","r");
        Entry * entries = malloc(sizeof(Entry) * entryCount);

        // checking if there is a game saves with the same name
        int i = 0;
        int playerID;
        int savedAlready = 0;
        for (i ; i < entryCount ; i++)
        {
            int nameLen;
            fscanf(users,"%i ",&nameLen);
            entries[i].name = malloc(sizeof(char) * (nameLen + 1));
            fscanf(users,"%s %3d",entries[i].name, &entries[i].numOfUserFile);
            if (!strcmp(entries[i].name,player_name_Inputted))
            {
                savedAlready = 1;
                playerID = i;
            }
        }


        // if there was a saved gamed associated with the player name
        if (savedAlready)
        {
            printf("\n                                                                 This name has an associated saved game, Do you want to override it ?");
            char overrideQuestion[MAXCHAR];
            do
            {
                printf("\n                                                                 (y ->yes ..n ->No) : ");
                gets(overrideQuestion);
                garbage = pthread_cancel(timer_th);
                garbage =  pthread_create(&timer_th, NULL, idle_timer,grid);
                strupr(overrideQuestion);
                fflush(stdin);
            }
            while(strcmp(overrideQuestion,"N") && strcmp(overrideQuestion,"Y"));


            // cancel the saving process
            if ( !strcmp(overrideQuestion,"N"))
            {
                fclose(users);
                int k ;
                for ( k = 0 ; k < entryCount ; k++)
                    free(entries[k].name);
                free(entries);
                return;
            }

            // overriding the current saved file
            else if ( !strcmp(overrideQuestion,"Y"))
            {
                int numOfOverrideFile = entries[playerID].numOfUserFile;

                char savedFile_To_Be_Override1[FILENAME_MAX];
                snprintf(savedFile_To_Be_Override1,FILENAME_MAX,"savedGrid%03d.txt",numOfOverrideFile);

                char savedFile_To_Be_Override2[FILENAME_MAX];
                snprintf(savedFile_To_Be_Override2,FILENAME_MAX,"savedGridStatues%03d.txt",numOfOverrideFile);

                char savedFile_To_Be_Override3[FILENAME_MAX];
                snprintf(savedFile_To_Be_Override3,FILENAME_MAX,"savedGridOpenedStatues%03d.txt",numOfOverrideFile);

                fclose(users);
                for ( i = 0 ; i < entryCount ; i++)
                    free(entries[i].name);
                free(entries);



                FILE * savedGrid;
                savedGrid = fopen(savedFile_To_Be_Override1,"w");
                i=0;
                int j=0;
                fprintf(savedGrid,"%d %d %d %d %d %d %d %d\n",rows, columns,timePassedInMins,timePassedInSecs,numOfMoves,numOfFlags,numOfQ,numOfOpennedCells);
                for (i=0 ; i < rows ; i++)
                {
                    for ( j=0 ; j < columns ; j ++)
                    {
                        fprintf(savedGrid,"%d ",grid[i][j]);
                    }
                    fprintf(savedGrid, "\n");
                }

                fclose(savedGrid);



                FILE * savedGridStatues;
                savedGridStatues = fopen(savedFile_To_Be_Override2,"w");

                for (i=0 ; i < rows ; i++)
                {
                    for ( j=0 ; j < columns ; j ++)
                    {
                        fprintf(savedGridStatues,"%d ",gridStatues[i][j]);
                    }
                    fprintf(savedGridStatues, "\n");
                }

                fclose(savedGridStatues);


                FILE * savedGridOpenedStatues;
                savedGridOpenedStatues = fopen(savedFile_To_Be_Override3,"w");

                for (i=0 ; i < rows ; i++)
                {
                    for ( j=0 ; j < columns ; j ++)
                    {
                        fprintf(savedGridOpenedStatues,"%d ",gridOpennedStatues[i][j]);
                    }
                    fprintf(savedGridOpenedStatues, "\n");
                }

                fclose(savedGridOpenedStatues);
            }
        }
        else
        {
            // if there were no associated saved gamed with the player name


            // freeing the memory as we no more need them
            fclose(users);
            for ( i = 0 ; i < entryCount ; i++)
                free(entries[i].name);
            free(entries);


            // saving the date to files
            FILE * users = fopen("users.txt","a");
            fprintf(users,"%d %s %03d\n",strlen(player_name_Inputted),player_name_Inputted,nummberOfSavedGames);
            // useless fprintf(users,"");
            fclose(users);

            char savedFileName1[FILENAME_MAX];
            snprintf(savedFileName1,FILENAME_MAX,"savedGrid%03d.txt",nummberOfSavedGames);

            char savedFileName2[FILENAME_MAX];
            snprintf(savedFileName2,FILENAME_MAX,"savedGridStatues%03d.txt",nummberOfSavedGames);

            char savedFileName3[FILENAME_MAX];
            snprintf(savedFileName3,FILENAME_MAX,"savedGridOpenedStatues%03d.txt",nummberOfSavedGames);


            // increasing the number of saved gamed by 1.
            fopen("NOSG.txt","w");
            nummberOfSavedGames++;
            fprintf(NOSG,"%d",nummberOfSavedGames);
            fclose(NOSG);

            FILE * savedGrid;
            savedGrid = fopen(savedFileName1,"w");
            int i,j;
            fprintf(savedGrid,"%d %d %d %d %d %d %d %d\n",rows, columns,timePassedInMins,timePassedInSecs,numOfMoves,numOfFlags,numOfQ,numOfOpennedCells);
            for (i=0 ; i < rows ; i++)
            {
                for ( j=0 ; j < columns ; j ++)
                {
                    fprintf(savedGrid,"%d ",grid[i][j]);
                }
                fprintf(savedGrid, "\n");
            }
            fclose(savedGrid);


            FILE * savedGridStatues;
            savedGridStatues = fopen(savedFileName2,"w");
            for (i=0 ; i < rows ; i++)
            {
                for ( j=0 ; j < columns ; j ++)
                {
                    fprintf(savedGridStatues,"%d ",gridStatues[i][j]);
                }
                fprintf(savedGridStatues, "\n");
            }
            fclose(savedGridStatues);


            FILE * savedGridOpenedStatues;
            savedGridOpenedStatues = fopen(savedFileName3,"w");
            for (i=0 ; i < rows ; i++)
            {
                for ( j=0 ; j < columns ; j ++)
                {
                    fprintf(savedGridOpenedStatues,"%d ",gridOpennedStatues[i][j]);
                }
                fprintf(savedGridOpenedStatues, "\n");
            }
            fclose(savedGridOpenedStatues);

        }



    }

}

