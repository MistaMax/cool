#include "cs3723p1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mmInit(StorageManager *pMgr, MMResult *pmmResult){

}

void * mmAllocate(StorageManager *pMgr, short shDataSize, short shNodeType, char sbData[], MMResult *pmmResult){
}

void mmMark(StorageManager *pMgr, MMResult *pmmResult){
    //sets the shSize to 0 as an initialization step
    short shSizeCurrNodeCount = 0;
    for(char * cursor = pMgr->pBeginStorage;cursor != pMgr->pEndStorage;cursor++)//increments the cursor by 1 byte
    {
        if(shSizeCurrNodeCount == 0)
        {
            cursor->cgC = 'C';
            shSizeCurrNodeCount = cursor->shNodeSize;
        }
        else
            shSizeCurrNodeCount--;
    }
}

void mmFollow(StorageManager *pMgr, void *pUserData, MMResult *pmmResult){
    char * followed[500];//keeps track of all the nodes that have been read completely
    //pMgr->metaAttrM
}

void mmCollect(StorageManager *pMgr, MMResult *pmmResult){
    
    //sets free nodes to F from C
}

void mmAssoc(StorageManager *pMgr, void *pUserDataFrom, char szAttrName[], void *pUserDataTo, MMResult *pmmResult){
}