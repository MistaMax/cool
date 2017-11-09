#define New(type) ((type) malloc(sizeof *((type) NULL)))
#define NewArray(n,type) ((type) malloc((n) * sizeof((type) NULL)))
#define true 1
#define false 0
typedef int bool;
void printUsageInfo();
void spliceString(char *s, int start, int end, char **str);
bool getInputSwitches(int argc, char *argv[],char **inputFile,char **outputFile);
