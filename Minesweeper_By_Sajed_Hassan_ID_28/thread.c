#include "thread.h"

// a function for escaping a certain time like delay and usleeo functions as there were a problem with usleep
void setTimeout(int milliseconds)
{
    // a current time of milliseconds
    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;

    // needed count milliseconds of return from this timeout
    int end = milliseconds_since + milliseconds;

    // wait while until needed time comes
    do
    {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    }
    while (milliseconds_since <= end);
}



// A function to be used as a thread for counting the time from the last move the player has made
void  idle_timer(char grid[][columns])
{
    //to make it able to be canceled
    //usleep(100);    ------> it's not working properly.

    int i = 0;
    while (1)
    {
        setTimeout(1000);
        //usleep(10000);
        i++;

        // testing for any move the player made
        pthread_testcancel();
        if ( i % 5 == 0 )
        {
            // getting the new time passed
            time(&currenttime);
            mytime = localtime(&currenttime);
            int currentsec = mytime->tm_sec ;
            int currentmin = mytime->tm_min;
            int currenthour = mytime->tm_hour;
            int differenceInSec = (currentsec-startingSec)+60*(currentmin-startingMin)+3600*(currenthour-startingHour);
            timePassedInMins = differenceInSec / 60;
            timePassedInSecs = differenceInSec % 60;

            // updating the grid with the new time passed.
            printGrid(rows, columns, grid,timePassedInMins,timePassedInSecs,numOfFlags,numOfQ,numOfMoves);
            // we may wait for a while then reprint it to decrease overriding

            // the player MUST complete his PREVIOUS movement .
            printf("\n                                                                 O to open,  F to put a flag,  q to put a ?   and  v to save  (ex : o 1 1) // R to return\n");
            printf("\n                                                                 (Complete) your previous Action : ");
        }
    }

}


