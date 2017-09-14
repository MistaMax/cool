#include "cs3723p1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mmInit(StorageManager *pMgr){
    pMgr->pFreeHead = (FreeNode *)pMgr->pBeginStorage;
    pMgr->pFreeHead->cGC = 'F';
    pMgr->pFreeHead->shNodeSize = pMgr->iHeapSize;
}

void * mmAllocate(StorageManager *pMgr, short shDataSize, short shNodeType, char sbData[]){
    FreeNode * f;
    for(f=pMgr->pFreeHead;f != NULL;f=f->pFreeNext){
        if(f->shNodeSize >= shDataSize + pMgr->nodeTypeM[shNodeType]->shNodeTotalSize){//add exception if the i minimum node size is not met for the free node
            f->shNodeSize = f->shNodeSize - shDataSize - pMgr->nodeTypeM[shNodeType]->shNodeTotalSize;
            //finding the memory address for the allocated space
            char * pTemp = (char *) f;
            pTemp += shDataSize + pMgr->nodeTypeM[shNodeType]->shNodeTotalSize;
            //add part where you define the Node
            break;
        }
    }
}

void mmMark(StorageManager *pMgr){
    //sets the shSize to 0 as an initialization step
    short shSizeCurrNodeCount = 0;
    char * cursor = NULL;
    for(cursor = pMgr->pBeginStorage;cursor != pMgr->pEndStorage;cursor++)//increments the cursor by 1 byte
    {
        if(shSizeCurrNodeCount == 0)
        {
            //add
            cursor->cgC = 'C';
            shSizeCurrNodeCount = cursor->shNodeSize;
        }
        else
            shSizeCurrNodeCount--;
    }
}

void mmFollow(StorageManager *pMgr, void *pUserData){
    char * followed[500];//keeps track of all the nodes that have been read completely
}

void mmCollect(StorageManager *pMgr){
    
    //sets free nodes to F from C
}

void mmAssoc(StorageManager *pMgr, void *pUserDataFrom, char szAttrName[], void *pUserDataTo){
}