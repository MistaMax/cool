#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 3
#define COL 4

int SearchRest(char temp[], char WordSearch[ROW][COL], int row, int col, int Index, int Ver, int Hor){
	if(temp[Index] == WordSearch[row + Ver][col+ Hor]){
		if(Index == strlen(temp)-1){
			return 1;
		}
		else
			return SearchRest(temp, WordSearch,row + Ver,col + Hor,Index+1, Ver, Hor);
	}
	return 0;
}
int LookUp(char temp[],int URow, int UCol, char WordSearch[ROW][COL]){
	int i, j;
	for(i = 0; i < URow; i++){
		for(j = 0; j < UCol; j++){
		//looks for first letter
			if(WordSearch[i][j] == temp[0]){
				//checks if at end of column
				if(j != UCol -1){
					//checks for second letter
					if(WordSearch[i][j+1] == temp[1]){
						if(SearchRest(temp, WordSearch, i, j+1,2,0,1)){
							printf("The word %s is found horizontally starting at [%d][%d]\n",temp,i,j);
							return 1;
						}
					}
				}
				//checks end of row
				if(i != URow -1){
					//checks for second letter
					if(WordSearch[i+1][j] == temp[1]){
						if(SearchRest(temp, WordSearch, i+1, j,2,1,0)){
							printf("The word %s is found vertically starting at [%d][%d]\n",temp,i,j);						
							return 1;
						}
					}
				}
				//checks end of both
				if(j != UCol -1 && i != URow -1){
					//checks for second letter
					if(WordSearch[i+1][j+1]){
						if(SearchRest(temp, WordSearch, i+1, j+1,2,1,1)){
							printf("The word %s is found diagonally starting at [%d][%d]\n",temp,i,j);	
							return 1;
						}
					}
				}	
			}
		}
	}
	return 0;
}


int main (int argc, char *argv[]){
	int i, j, Flag, UserRow, UserCol, ab, RowFound, ColFound;
	FILE *file;
	char FileName[20], tempm, BUFFER[255], Temp[20];
	char UserIn[3][4] = {};
	int flag = 0;
	//check "-f" flag
	for (i = 1; i < argc; i++){
        if (strcmp(argv[i], "-f") == 0){
			Flag = 1;
			j = 1 + i;
		}
    }
	//if flag found
	if(Flag == 1){	
		strcpy(FileName, argv[j]);
		file = fopen(FileName, "r");
		printf("file name: %s\n", FileName);
		if(file == NULL )
			printf("couldnt open the file\n");
		fgets(BUFFER, 255, file);
		sscanf(BUFFER, "%d %d[1-9]", &UserRow, &UserCol);
		//gets until EoF
		while(fgets(BUFFER, 255, file) != NULL){
			if(sscanf(BUFFER, "%s[^1-9]", &UserIn[flag][0]) == 1){
				flag++;
			}
		}
		//loops the user input words to find
		for(ab = 1; ab < argc-2; ab++){
			strcpy(Temp, argv[ab]);	
			if(LookUp(Temp,UserRow, UserCol, UserIn) == 0){
				printf("%s could not be found\n", Temp);	
			}
		}
	} else{
		char DEFAULT[ROW][COL] = {	{'a','b','c','d'},
									{'d','c','b','a'},
									{'x','y','z','d'}};
		//loops user input words
		for(ab = 1; ab < argc; ab++){
			strcpy(Temp, argv[ab]);	
			if(LookUp(Temp,ROW, COL, DEFAULT) == 0){
				printf("%s could not be found\n", Temp);	
			}
		}
	}
}
