#include <stdio.h>
#include <time.h>

void function_to_time(void);

int main(void) {
   time_t tend, tstart;  
   //char buffer[26];
   struct tm *torig, *taft;

   time(&tstart);
   function_to_time();
   time(&tend);

   /*torig = localtime(&tstart);
   taft = localtime(&tend);

   char buffStart[26];
   strftime(buffStart, sizeof(buffStart), "%a %Y-%m-%d %H:%M:%S", torig);
   char buffEnd[26];
   strftime(buffEnd, sizeof(buffEnd), "%a %Y-%m-%d %H:%M:%S", taft);*/

   printf("The time before was %s", ctime(&tstart));
   printf("The time after  was %s", ctime(&tend));
   return 0;
}

/*char *transTime(char *buff, struct tm *t)
{
        buffCnt
}*/