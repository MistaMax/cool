#include <string.h>

int main(int argc,char *argv[]){
    int i;
    int j=0;
    char szName[21]="Perry";
    char szReversedName[21];
    for(i = strlen(szName) - 1;i>=0;i--){
        szReversedName[j]=szName[i];
        j++;
    }
    szReversedName[strlen(szReversedName)]='\0';
    printf("%s \n",szReversedName);
}
