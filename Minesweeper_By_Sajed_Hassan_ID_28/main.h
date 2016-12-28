#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <pthread.h>
#include <windows.h>
#include <ctype.h>

// time parameters declared as global variables in order to be able to use them in the thread function
time_t currenttime;
struct tm *mytime ;

int startingMin ;
int startingSec ;
int startingHour ;

// thread to be used for the bonus part
pthread_t timer_th;


// parameters declared as global variables in order to be able to use them in the thread function
int rows,columns ;

int numOfFlags ;
int numOfQ ;
int numOfMoves ;
int timePassedInMins ;
int timePassedInSecs ;



// the cell that made the player lose the game
int criticalChoosedRow;
int criticalChoosedColumn;


// this just to return the values of threads functions and any other function with in it in order to be able to test it
int garbage;


#endif // MAIN_H_INCLUDED
