#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

void reopen(int choosedRow, int choosedColumn,int rows, int columns,char grid[rows][columns],char gridStatues[rows][columns],char gridOpennedStatues[rows][columns],int * Pplaying,int *PnumOfOpennedCells);
void rec(int choosedRow, int choosedColumn,int rows, int columns,char grid[rows][columns],char gridStatues[rows][columns],char gridOpennedStatues[rows][columns],int * Pplaying,int *PnumOfOpennedCells);
void open(int choosedRow, int choosedColumn,int rows, int columns,char grid[rows][columns],char gridStatues[rows][columns],char gridOpennedStatues[rows][columns],int * Pplaying, int * PnumOfOpennedCells );
void firstMovefun(int * PfirstMove,int choosedRow, int choosedColumn,int rows, int columns, char gridStatues[rows][columns]);



#endif // ACTIONS_H_INCLUDED
