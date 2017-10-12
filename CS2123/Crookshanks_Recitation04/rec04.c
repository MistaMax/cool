#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header04.h"//my custom header

int main (int argc, char *argv[])
{
    RectT a, b, *recs;
    InputRect(&a,"a");
    InputRect(&b,"b");
    printf("\na and b do ");
    if(chk_overlap(&a,&b)==0)printf("not");//prints not if they do not overlap
    printf("overlap\n");
    recs = NewArray(50,RectT);//allocates and creates 50 rectangles as an array
    int i;
    for(i=0;i<50;i++)//defines all the rectangles
    {
        recs[i].location.x = rand()%20;
        recs[i].location.y = rand()%20;
        recs[i].w = rand()%20;
        recs[i].h = rand()%20;
    }
    int countOverLap=0;//counts the overlaps
    for(i=0;i<50;i++)countOverLap=countOverLap+chk_overlap(&recs[i], &a);//for loop for checking overlap
    printf("\n %i rectangles overlap with a", countOverLap);
    countOverLap=0;//resets the counter
    for(i=0;i<50;i++)countOverLap=countOverLap+chk_overlap(&recs[i], &b);
    printf("\n %i rectangles overlap with b", countOverLap);
    countOverLap=0;
    for(i=0;i<50;i++)
    {
        if(chk_overlap(&recs[i], &a)==1 && chk_overlap(&recs[i], &b)==1)countOverLap++;
    }
    printf("\n %i rectangles overlap with a and b\n", countOverLap);
    return 0;
}

void InputRect(RectT *r, string text)//used to set the dimentions and location of the rect
{
    printf("\n Input location x for %s\n",text);
    scanf("%lf",&r->location.x);
    printf("\n Input location y for %s\n",text);
    scanf("%lf",&r->location.y);
    printf("\n Input width for %s\n",text);
    scanf("%lf",&r->w);
    printf("\n Input height for %s\n",text);
    scanf("%lf",&r->h);
}

int chk_overlap(RectT *r1, RectT *r2)//checks the overlap
{
    int botXR1=r1->location.x, botYR1=r1->location.y, botXR2=r2->location.x, botYR2=r2->location.y;
    int topXR1=r1->w+botXR1, topYR1=r1->h+botYR1;
    if(botXR2 < topXR1 && botYR2 < topYR1)return 1;//checks to see if the values overlap
    else return 0;
}
