#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SHOT    200
#define MAX_PLAYERS 20
#define TRUE 1
#define FALSE 0

/* program return codes */
#define ERR_COMMAND_LINE_SYNTAX     -1      // invalid command line syntax
#define USAGE_ONLY                  -2      // show usage only
#define ERROR_PROCESSING            -3

/* error messages */
#define ERR_EXPECTED_SWITCH         "expected switch, found"
#define ERR_MISSING_ARGUMENT        "missing argument for"

/* prototypes */
void exitError(char *pszMessage, char *pszDiagnosticInfo);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);
void getPlayerShootingData();
void processCommandSwitches(int argc, char *argv[], char **ppszShootingFileName);
typedef struct
{
    char szShotType[3];  // FT - free throw, 2P - 2 point, 3P - three point
    char cMadeInd;       // Y - Made the shot, N - did not make it
} Shot;
typedef struct
{
    int iJerseyNr;
    char szPlayerNm[31];
    Shot shotM[MAX_SHOT];
} BPlayer;

FILE *pFilePlayer;
int main(int argc, char *argv[])
{
    char *pszShootingFileNm = NULL;
 
    // Process the command switches
    processCommandSwitches(argc, argv, &pszShootingFileNm);

    // open the Shooting stream data file
    if (pszShootingFileNm == NULL)
        exitError("Missing switch ", "-s");

    pFilePlayer = fopen(pszShootingFileNm, "r");
    if (pFilePlayer == NULL)
        exitError("Invalid shooting file name", pszShootingFileNm);

    getPlayerShootingData();
    printf("\n");
}

// Code for reading player data until eof
// For each player there are multiple shot records 
void getPlayerShootingData()
{
    char szInputBuffer[100];
    int iscanfCnt;
    BPlayer player;
    Shot shot;
    // free throw percentage variables
    int iFTCnt;
    int iFTMadeCnt;
    double dFTPercent;

    printf("%-8s  %-30s\n", "Jersey #", "Player Name");

    // Read player identification information until EOF
    while (fgets(szInputBuffer, 100, pFilePlayer) != NULL)
    {
        iscanfCnt = sscanf(szInputBuffer, "%d %30[^\n]\n"
            , &player.iJerseyNr
            , player.szPlayerNm);
        if (iscanfCnt < 2)
            exitError("Bad Player Identification Data", "");
        printf("%8d  %-30s\n", player.iJerseyNr, player.szPlayerNm);
        iFTCnt = 0;
        iFTMadeCnt = 0;
        printf("\t\t%-10s %-5s\n", "Shot Type", "Made");

        // read shot info until shot.szShotType is "XX"
        while (fgets(szInputBuffer, 100, pFilePlayer) != NULL)
        {
            iscanfCnt = sscanf(szInputBuffer, "%2s %c"
                , shot.szShotType
                , &shot.cMadeInd);
            if (iscanfCnt < 2)
                exitError("Bad Shot Data", "");

            // Check for a shot type of XX which marks end of data
            if (strcmp(shot.szShotType, "XX") == 0)
                break;

            printf("\t\t%-10s %c\n", shot.szShotType, shot.cMadeInd);
            // determine free throw counts
            if (strcmp(shot.szShotType, "FT") == 0)
            {
                iFTCnt++;
                if (shot.cMadeInd == 'Y')
                    iFTMadeCnt++;
            }

        }
        // Show the Free Throw Percentage for the current player
        if (iFTCnt == 0)
            dFTPercent = 0.0;
        else
            dFTPercent = (iFTMadeCnt + 0.0) / iFTCnt * 100.0;
        printf("\t\tFree Throw Percentage = %.1lf%%\n", dFTPercent);
    }
    printf("\n");
}
/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszShootingFileName)
Purpose:
    Checks the syntax of command line arguments and returns the filenames.
    If any switches are unknown, it exits with an error.
Parameters:
    I   int argc                        count of command line arguments
    I   char *argv[]                    array of command line arguments
    O   char **ppszShootingFileName     shooting file name
Notes:
    If a -? switch is passed, the usage is printed and the program exits
    with USAGE_ONLY.
    If a syntax error is encountered (e.g., unknown switch), the program
    prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/

void processCommandSwitches(int argc, char *argv[], char **ppszShootingFileName)
{
    int i;
    int rc = 0; 
    int bShowCommandHelp = FALSE;
    
    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
            case 's':                   // Shooting File Name
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszShootingFileName = argv[i];
                break;
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        }
    }
}

/******************** exitError *****************************
    void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    Prints an error message and diagnostic to stderr.  Exits with
    ERROR_PROCESSING.
Parameters:
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
    fprintf(stderr, "Error: %s %s\n"
        , pszMessage
        , pszDiagnosticInfo);
    exit(ERROR_PROCESSING);
}
/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    If this is an argument error (iArg >= 0), it prints a formatted message
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits
    with ERR_COMMAND_LINE_SYNTAX.

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/

void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    if (iArg >= 0)
        fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
            , iArg
            , pszMessage
            , pszDiagnosticInfo);
    fprintf(stderr, "shooting -s shootingFile\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
