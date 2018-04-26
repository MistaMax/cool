#include "myio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/****************************************************************
 * driver2.c
 * 
 * Description:
 *      Removes extra spaces from an input in and puts
 *      it into an output file out
*****************************************************************/
int main(int argc, char *argv[])
{
    //checks to see if there are the appropriate ammount of args
    if(argc != 3)
    {
        fprintf(stderr,"Wrong ammount of arguments");
        return 1;
    }
    //initializes the variables
    FILE *in, *out;
    string szInFile = NULL, szOutFile = NULL;
    //loads in the file names
    szInFile = argv[1];
    szOutFile = argv[2];
    //checks to see if the file names loaded in propperly
    if(szInFile == NULL || szOutFile == NULL)
    {
        fprintf(stderr,"Error reading in the arguments\n");
        return 2;
    }
    //opening the files
    in = fopen(szInFile,"r");
    out = fopen(szOutFile,"w");
    //checks to see if the files were opened correctly
    if(in == NULL || out == NULL)
    {
        fprintf(stderr,"Error in opening the files");
        return 3;
    }
    
    string line;
    //reads until eof, takes in the line, and removes the extra
    //spaces then prints to the output
    while(line = ReadLineFile(in))
    {
        int i;
        for(i = 0; i < strlen(line); i++)
        {
            fprintf(out,"%c",line[i]);
            //gets rid of the spaces
            if(line[i] == ' ' && line[i+1] == ' ')
            {
                i++;
                for(;i < strlen(line);i++)
                {
                    if(line[i] != ' ')break;
                }
                fprintf(out,"%c",line[i]);
            }
        }
        fprintf(out,"\n");
    }
    //closes the file
    close(in);
    close(out);
    return 0;
}