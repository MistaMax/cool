#include <stdio.h>
int main(int argc, char *argv[])
{
    double dSum = 0.0;
    int i;
    int iScanfCount;        // count of the successful 
                            // conversions in sscanf
    int iNum;               // number from the command line
    /* check for no arguments */
    if (argc < 2)
    {
        fprintf(stderr, "Error:  must pass values to average");
        return 0;
    }
    for (i = 1; i < argc; i++)
    {
        // convert command argument to int
        iScanfCount = sscanf(argv[i], "%d", &iNum);
        // sscanf returns the number of successful formats
        if (iScanfCount < 1)
        {
            fprintf(stderr, "Invalid command argument: %s"
                        , argv[i]);
            return -1;
        }
        dSum += iNum;
    }
    printf("%lf \n", dSum / (argc - 1));
    return 0;
}
