#include <stdio.h>

int main(int argc, char *argv[]){
    processCommandSwitches(argc, argv, )
}

void processCommandSwitches(int argc, char *argv[])
{
    int i;
    int rc = 0;
    int bShowCommandHelp = FALSE;

    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-'){
            printf("error, no switch");
            exit();
        }
        // determine which switch it is
        switch (argv[i][1])
        {

        default:
            printf
        }
    }
}