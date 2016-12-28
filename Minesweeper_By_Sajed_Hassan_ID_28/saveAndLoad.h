#ifndef SAVEANDLOAD_H_INCLUDED
#define SAVEANDLOAD_H_INCLUDED

int loadRowsAndColumns(int * Prows, int * Pcolumns,int * PtimePassedInMins, int * PtimePassedInSecs, int*PnumOfMoves,int*PnumOfFlags,int*PnumOfQ,int*PnumOfOpennedCells);
void loadGrids(int rows, int columns, char grid[rows][columns],int numOfChoosedFile);
void loadGridsStatues(int rows, int columns,char gridStatues[rows][columns],int numOfChoosedFile);
void loadGridsOpenedStatues(int rows, int columns,char gridOpennedStatues[rows][columns],int numOfChoosedFile);
void save(int rows, int columns, char grid[rows][columns],char gridStatues[rows][columns],char gridOpennedStatues[rows][columns],int timePassedInMins, int timePassedInSecs, int numOfMoves,int numOfFlags,int numOfQ,int numOfOpennedCells);


#endif // SAVEANDLOAD_H_INCLUDED
