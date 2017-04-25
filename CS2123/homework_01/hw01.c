#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
int determineBox(int r, int c);

int main(int argc, char *argv[])
{
	int cmd,r,c,i,block,complete=true,blockB;
	int sudoku[9][9];
	scanf("%d\n", &cmd);
	for (r = 0;r < 9;r++)//just scanning and importing the soduku puzzle
	{
		scanf("%d %d %d %d %d %d %d %d %d\n", &sudoku[r][0], &sudoku[r][1], &sudoku[r][2], &sudoku[r][3], &sudoku[r][4], &sudoku[r][5], &sudoku[r][6], &sudoku[r][7], &sudoku[r][8]);
	}
	printf("\n");
	int check[10][3][82], count = 0;
	for (r = 0;r < 9;r++)//records all the filled in cells and puts them into check
	{

		for (c = 0;c < 9;c++)
		{
			if (sudoku[r][c] != 0)
			{
				check[sudoku[r][c]][0][count] = r;//0=rows , 1=collumns, 2=boxes
				check[sudoku[r][c]][1][count] = c;
				check[sudoku[r][c]][2][count] = determineBox(r, c);
				count++;
			}
		}
	}
	if (cmd == 1)
	{
		int poss[9][9][10];//the int array that contains all of the possibility values
		for (r = 0;r < 9;r++)
		{
			for (c = 0;c < 9;c++)
			{
				if (sudoku[r][c] == 0)
				{
					for (i = 0;i < 10;i++)//sets all the poss values to true
					{
						poss[r][c][i] = true;
					}
					for (i = 1;i < 10;i++)
					{
						for (block = 0;block < count;block++)
						{
							if ((check[i][0][block] == r || check[i][1][block] == c) || check[i][2][block] == determineBox(r, c))
							{
								poss[r][c][i] = false;
							}
						}
					}
				}
				else
				{
					poss[r][c][0] = false;//notes that the specific cell is filled
				}
			}
		}
		for (r = 0;r < 9;r++)
		{
			for (c = 0;c < 9;c++)
			{
				if (poss[r][c][0] == true)//Prints all the possibilities for the cell
				{
					printf("Possibilities for Row: %d  Collumn: %d are, ", r, c);
					for (i = 1;i < 10;i++)
					{
						if (poss[r][c][i] == true)
						{
							printf("%d ", i);
						}
					}
					printf("\n");
				}
			}
                }
	}
	else if (cmd == 2)
	{
		if (count != 81)printf("This Solution is Incomplete\n");//checks to see if all the places are filled
		else
		{
			for (i = 1;i < 10;i++)
			{
				for (block = 0;block < count;block++)
				{
					for (blockB = 0;blockB < count;blockB++)
					{
						if (complete == true && block != blockB)//this scans for repetitions
						{
                                                        if ((check[i][0][blockB] == check[i][0][block] || check[i][1][blockB] == check[i][1][block]) || check[i][2][blockB] == check[i][2][block])complete = false;
						}
					}
				}
			}
		}
		if (complete == false)printf("This is not a solution\n");
		else printf("This is a solution\n");
	}
	else return 1;
    return 0;
}

int determineBox(int r, int c)//Box ranges from values 0-8 and each box contains 3 rows and 3 collumns
{
	int dc = c / 3;
	int dr = r / 3;
	return dc + dr*3;
}
