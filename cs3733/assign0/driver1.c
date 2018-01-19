#include "myio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        fprintf(stderr,"Wrong ammount of arguments");
        return 1;
    }

    int iMultInt, iMultDoub, iMultLine, iScanfCnt = 0;

    iScanfCnt += sscanf(argv[1],"%d",&iMultInt);
    iScanfCnt += sscanf(argv[2],"%d",&iMultDoub);
    iScanfCnt += sscanf(argv[3],"%d",&iMultLine);

    if(iScanfCnt < 3)
    {
        fprintf(stderr,"ERROR: Count not inputted correctly");
        return 2;
    }
    
    int iMax = 0;
    double dMax = 0.00;
    int iLongLine = 0;
    string szBigLine = NULL;
    //tmp variables
    /*int iTmp = 0;
    double dTmp = 0.00;
    int iTmpLine = 0;
    string szTmpLine = NULL;*/
    int i;
    //reading in the int
    for(i = 0; i < iMultInt;i++)
    {
        int iTmp = ReadInteger();
        if(iTmp > iMax)iMax = iTmp;
    }
    //reading in the doubles
    for(i = 0; i < iMultDoub; i++)
    {
        double dTmp = ReadDouble();
        if(dTmp > dMax)dMax = dTmp;
    }
    //reading in the lines
    for(i = 0; i < iMultLine; i++)
    {
        printf("Please Input a line: \n");
        string szTmpLine = ReadLine();
        int iTmpLine = strlen(szTmpLine);
        if(iTmpLine > iLongLine)
        {
            iLongLine = iTmpLine;
            if(szBigLine != NULL)free(szBigLine);
            szBigLine = (string) malloc(strlen(szTmpLine)+1);
            strcpy(szBigLine,szTmpLine);
        }
        if(szTmpLine != NULL)free(szTmpLine);
    }

    printf("\n****************************************\n\n");
    printf("Max Int: %d\n", iMax);
    printf("Max Double: %.2lf\n", dMax);
    printf("Longest Line: %s\n", szBigLine);
    return 0;
}