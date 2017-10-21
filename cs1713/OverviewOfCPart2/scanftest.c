#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc,char *argv[]){
	char szOutput[100];
	int iScanfCheck;
	printf("Please input a few words: \n");
	iScanfCheck = scanf("%99[^\n]\n",szOutput);
	if (iScanfCheck < 1) {
		printf("Invalid Input\n");
		return 0;
	}
	szOutput[strlen(szOutput)] = '\0';
	printf("Your Input Was:\n%s\n", szOutput);
        char szReverseOutput[100];
        int i,j=0;
        for(i=strlen(szOutput)-1;i>=0;i--){
            szReverseOutput[j]=szOutput[i];
            j++;
        }
        szReverseOutput[strlen(szReverseOutput)]='\0';
        printf("The reverse of your input is:\n%s\n",szReverseOutput);
}
