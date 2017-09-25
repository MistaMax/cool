#include "cs3723p1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ADD PMM RESULT TO EVERYTHING
void mmInit(StorageManager *pMgr, MMResult *pmmResult){
    pMgr->pFreeHead = (FreeNode *)pMgr->pBeginStorage;
    memset(pMgr->pBeginStorage,'\0',pMgr->iHeapSize);
    pMgr->pFreeHead->cGC = 'F';
    pMgr->pFreeHead->shNodeSize = pMgr->iHeapSize;

}

void * mmAllocate(StorageManager *pMgr, short shDataSize, short shNodeType, char sbData[], MMResult *pmmResult){//re-add pmm result
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
        pmmResult->rc = RC_NOT_AVAIL;
        //pmmResult->szErrorMessage = "No Space";
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
        pAlloc = (InUseNode *)p;
        pAlloc->cGC = 'U';
        pAlloc->shNodeSize = shTotalSize;
        pAlloc->shNodeType = shNodeType;
        memcpy((void *)(pAlloc->sbData), (void *)sbData, shDataSize);
        
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

        pAlloc = (InUseNode *)p;
        pAlloc->cGC = 'U';
        pAlloc->shNodeSize = shTotalSize;
        pAlloc->shNodeType = shNodeType;
        memcpy((void *)pAlloc->sbData, (void *)sbData, shDataSize);
    }
    //set object to beginning of free node
    //remove free node
    //re-allocate free node
    return pAlloc->sbData;
}

void mmMark(StorageManager *pMgr, MMResult *pmmResult){
    char * cursor = NULL;
    short shTempSize = 0;
    for(cursor = pMgr->pBeginStorage;cursor < pMgr->pEndStorage;cursor += shTempSize)//increments the cursor by 1 byte
    {
        shTempSize = ((InUseNode *)cursor)->shNodeSize;
        ((InUseNode *)cursor)->cGC = 'C';
    }
}

void mmFollow(StorageManager *pMgr, void *pUserData, MMResult *pmmResult){
    if(!pUserData)
    {
        return;
    }
    InUseNode * pCurr;
    int iAttr;
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
            for(iAttr = pMgr->nodeTypeM[shNodeType].shBeginMetaAttr; pMgr->metaAttrM[iAttr].shNodeType == shNodeType; iAttr++)
            {
                pAttr = &(pMgr->metaAttrM[iAttr]);
                if(pAttr->cDataType == 'P')
                    mmFollow(pMgr, ((char *)pUserData + pAttr->shOffset), pmmResult);
                /*{
                    pp = (void **)&pCurr->sbData[]
                }*/
            }
            break;
    }
}
//cory code
void mmCollect(StorageManager *pMgr, MMResult *pmmResult){
    //sets free nodes to F from C
    char * pCur;
    char * pNext;
    char * pPrev = (char *)0;
    FreeNode * pNewNode;
    short shTempSize;
    int iTotalSize;
    pMgr->pFreeHead = (FreeNode *)0;
    pCur = pMgr->pBeginStorage;
    while(pCur < pMgr->pEndStorage)
    {
        shTempSize = ((FreeNode *)pCur)->shNodeSize;
        pNext = pCur + shTempSize;
        if(((FreeNode *)pCur)->cGC == 'C')
        {
            if(pNext < pMgr->pEndStorage && ((FreeNode *)pNext)->cGC == 'C')
            {
                printf("\tCombining  %08lX with %08lX\n", ULAddr(pCur), ULAddr(pNext));
                pNewNode = (FreeNode *)pCur;
                iTotalSize = ((FreeNode *)pCur)->shNodeSize + ((FreeNode *)pNext)->shNodeSize;
                pNewNode->shNodeSize = iTotalSize;
            }
            else
            {
                printf("\tCollecting %08lX\n", ULAddr(pCur));
                pNewNode = (FreeNode *)pCur;
                pNewNode->cGC = 'F';
                pNewNode->pFreeNext = (FreeNode *)pPrev;
                pPrev = pCur;
                pCur += shTempSize;
            }
        }
        else
        {
            pCur += shTempSize;
        }
    }
    pMgr->pFreeHead = (FreeNode *)pPrev;
}

/*void mmCollect(StorageManager *pMgr)
{
    char * pCur;
    char * pLoop;
    char * pNext;
    char * pPrev = NULL;
    FreeNode * pNewFreeNode = (FreeNode *)0;
    short shTotalNodeSize = 0;
    short shTempSize=0;

    for(pCur = pMgr->pBeginStorage;pCur < pMgr->pEndStorage; pCur = pNext)
    {
        shTotalNodeSize = ((FreeNode *)pCur)->shNodeSize;
        pNext = pCur + shTotalNodeSize;
        if(((FreeNode *)pCur)->cGC == 'C')
        {
            for(pLoop = pNext;((FreeNode *)pLoop)->cGC != 'U' && pLoop < pMgr->pEndStorage;pLoop += shTempSize)
            {
                
            }
        }
    }
}*/

void mmAssoc(StorageManager *pMgr, void *pUserDataFrom, char szAttrName[], void *pUserDataTo, MMResult *pmmResult){
    int iAttr;
    /*for(iAttr = 0;((MetaAttr *)pUserDataFrom[iAttr])->szAttrName != szAttrName; iAttr++)
    {

    }*/
}