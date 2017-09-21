#include "cs3723p1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mmInit(StorageManager *pMgr){
    pMgr->pFreeHead = (FreeNode *)pMgr->pBeginStorage;
    memset(pMgr->pBeginStorage,'\0',pMgr->iHeapSize);
    pMgr->pFreeHead->cGC = 'F';
    pMgr->pFreeHead->shNodeSize = pMgr->iHeapSize;

}

void * mmAllocate(StorageManager *pMgr, short shDataSize, short shNodeType, char sbData[]){//re-add pmm result
    FreeNode * pPrev;
    FreeNode * p;
    InUseNode * pAlloc = (InUseNode *)0;
    short shDiff; 
    short shTotalSize = shDataSize + NODE_OVERHEAD_SZ;
    for(p=pMgr->pFreeHead;p != NULL;pPrev=p, p=p->pFreeNext){
        if(p->shNodeSize >= shTotalSize)//add exception if the i minimum node size is not met for the free node
            break;
    }
    //check size
    if(p == NULL)
    {
        //pmmResult->rc = RC_NOT_AVAIL
        //pmmResult->szErrorMessage = "Not enough space available"
        return NULL;
    }
    //bridging the gap
    if((shDiff = p->shNodeSize - (shTotalSize)) >= pMgr->iMinimumNodeSize){
        if(!pPrev)
        {
            pMgr->pFreeHead = p->pFreeNext;
        }
        else
        {
            pPrev->pFreeNext = p->pFreeNext;
        }
        
        //setting up pNewNode
        pNewNode = (InUseNode *)p;
        pNewNode->cGC = 'U';
        pNewNode->shNodeSize = shTotalSize;
        pNewNode->nodeTypeM = shNodeType;
        memcpy((void *)pNewNode->sbData, (void *)sbData, shDataSize);
        
        //
        p = (FreeNode *)((char *)p + shTotalSize);
        p->cGC = 'F';
        p->shNodeSize = shDiff;
        p->pFreeNext = pMgr->pFreeHead;
        pMgr->pFreeHead = p;
    }
    else
    {
        if(!pPrev)
        {
            pMgr->pFreeHead = p->pFreeNext;
        }
        else
        {
            pPrev->pFreeNext = p->pFreeNext;
        }

        pNewNode = (InUseNode *)p;
        pNewNode->cGC = 'U';
        pNewNode->shNodeSize = shTotalSize;
        pNewNode->nodeTypeM = shNodeType;
        memcpy((void *)pNewNode->sbData, (void *)sbData, shDataSize);
    }
    //set object to beginning of free node
    //remove free node
    //re-allocate free node
    return pNewNode->sbData;
}

void mmMark(StorageManager *pMgr){
    char * cursor = NULL;
    short shTempSize = 0;
    for(cursor = pMgr->pBeginStorage;cursor < pMgr->pEndStorage;cursor += shTempSize)//increments the cursor by 1 byte
    {
        shTempSize = ((InUseNode *)cursor)->shNodeSize;
        ((InUseNode *)cursor)->cGC = 'C';
    }
}

void mmFollow(StorageManager *pMgr, void *pUserData){
    InUseNode * pCurr;
    int iAt;
    short shNodeType;
    MetaAttr *pAttr;

    pCurr = (InUseNode *)((char *)pUserData - NODE_OVERHEAD_SZ);
    shNodeType = pCurr->shNodeType;
    switch(pCurr->cGC)
    {
        case 'U':
            return;
        break;
        case 'C':
            pCurr->cGC = 'U';
            for(iAt = pMgr->nodeTypeM[shNodeType].shBeginMetaAttr; pMgr->metAttrM[iAt].shNodeType == shNodeType; iAt++)
            {
                pAttr = &(pMgr->metaAttrM[iAt]);
                switch(pAttr->cDataType)
                {
                    case 'P':
                        mmFollow(pMgr, ((char *)pUserData + pAttr->shOffset), pmmResult);
                        break;
                }
            }
    }
}

void mmCollect(StorageManager *pMgr){
    //sets free nodes to F from C
    char * cursor;
    short shTempSize = 0;
    for(cursor = pMgr->pBeginStorage;cursor < pMgr->pEndStorage;cursor += shTempSize)
    {
    }
}

void mmAssoc(StorageManager *pMgr, void *pUserDataFrom, char szAttrName[], void *pUserDataTo){

}