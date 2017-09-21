#include "cs3723p1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mmInit(StorageManager *pMgr){
    pMgr->pFreeHead = (FreeNode *)pMgr->pBeginStorage;
    memset(pMgr->pBeginStorage,'\0',pMgr->iHeapSize);
    pMgr->pFreeHead->cGC = 'F';
    pMgr->pFreeHead->shNodeSize = pMgr->iHeapSize + NODE_OVERHEAD_SZ;

}

void * mmAllocate(StorageManager *pMgr, short shDataSize, short shNodeType, char sbData[]){
    FreeNode * p;
    InUseNode * pAlloc;
    short shTotalSize = shDataSize + NODE_OVERHEAD_SZ;
    for(p=pMgr->pFreeHead;p != NULL;p=p->pFreeNext){
        if(p->shNodeSize >= shTotalSize)//add exception if the i minimum node size is not met for the free node
            break;
    }
    //check size
    if(p->shNodeSize < shTotalSize || p == NULL)
    {
        //pmmResult->rc = RC_NOT_AVAIL
        //pmmResult->szErrorMessage = "Not enough space available"
        return NULL;
    }
    //allocate
    
    //set object to beginning of free node
    //remove free node
    //re-allocate free node
}

void mmMark(StorageManager *pMgr){
    //sets the shSize to 0 as an initialization step
    //check shDump
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