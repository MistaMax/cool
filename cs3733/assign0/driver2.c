#include "myio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr,"Wrong ammount of arguments");
        return 1;
    }

    FILE *in, *out;
    string szInFile = NULL, szOutFile = NULL;

    szInFile = argv[1];
    szOutFile = argv[2];

    if(szInFile == NULL || szOutFile == NULL)
    {
        fprintf(stderr,"Error reading in the arguments\n");
        return 2;
    }

    in = fopen(szInFile,"r");
    out = fopen(szOutFile,"w");

    if(in == NULL || out == NULL)
    {
        fprintf(stderr,"Error in opening the files");
        return 3;
    }

    string line;

    while(line = ReadLineFile(in))
    {
        int i;
        for(i = 0; i < strlen(line); i++)
        {
            fprintf(out,"%c",line[i]);
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

    close(in);
    close(out);
    return 0;
}