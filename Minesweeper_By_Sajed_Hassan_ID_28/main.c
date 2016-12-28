#include "main.h"


int main()
{

    // parameters for handling the console (colors).
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    /*CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Saving current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;*/

    srand(time(NULL)); // that must be made outside any loop to avoid repeated patterns
    while (1)
    {

        numOfFlags = 0;
        numOfQ = 0;
        numOfMoves = 0;
        timePassedInMins = 0;
        timePassedInSecs = 0;

        system("COLOR F1");
        SetConsoleTextAttribute(hConsole, 249);



        logo();
        mainMenu();
        printf("\n\n                                                                 Make a choice : ");




        char menu[MAXCHAR];
        gets(menu);
        strupr(menu);

        // getting an option for the main menu
        while ( strcmp(menu, "S") != 0 && strcmp(menu, "L") != 0 && strcmp(menu, "H") != 0  && strcmp(menu, "Q") != 0 )
        {
            printf("                                                                 This is not an OPTION, Please try again.\n");
            printf("\n\n                                                                 Make a choice : ");
            gets(menu);
            strupr(menu);
        }
        fflush(stdin);



        int newGame = 1;        // starting a new game



        if ( strcmp(menu, "S") == 0 )
        {
            system("cls");
            logo();
            start(newGame);
            printf("\n\n\n\n                                                                 Press Any key to back to main menu");
            getch();
            system("cls");
        }

        // loading a saved game
        else if (strcmp(menu, "L") == 0)
        {
            system("cls");
            start(!newGame);
            printf("\n\n\n\n                                                                 Press Any key to back to main menu");
            getch();
            system("cls");
        }

        // showing the list of scores
        else if (strcmp(menu, "H") == 0)
        {
            system("cls");
            showScores("NULL");
            printf("\n\n\n\n                                                                 Press Any key to back to main menu");
            getch();
            system("cls");
        }
        else if (strcmp(menu, "Q") == 0)
        {
            exit(0);
        }
    }

    return 0;
}


// BAS KDA xD
