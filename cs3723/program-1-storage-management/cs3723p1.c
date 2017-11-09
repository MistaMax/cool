#include <stdio.h>
#include <string.h>
#include "cs3723p1.h"

void * mmAllocate(StorageManager *pMgr, short shDataSize, short shNodeType, char sbData[], MMResult *pmmResult)
{
    char *errMsg;
    FreeNode *pPrev = (FreeNode *)0;
    FreeNode *p = pMgr->pFreeHead;
    InUseNode *pNew = (InUseNode *)0;
    short shDiff;
    int totalSize;

    while(p && (char *)p < pMgr->pEndStorage)
    {
        if(p->shNodeSize >= (shDataSize + NODE_OVERHEAD_SZ))
        {
            shDiff = p->shNodeSize - (shDataSize + NODE_OVERHEAD_SZ);
            if(shDiff >= pMgr->iMinimumNodeSize)
            {
                if(!pPrev)
                    pMgr->pFreeHead = p->pFreeNext;
                else
                    pPrev->pFreeNext = p->pFreeNext;

                totalSize = shDataSize + NODE_OVERHEAD_SZ;
                pNew = (InUseNode *)p;
                pNew->cGC = 'U';
                pNew->shNodeType = shNodeType;
                pNew->shNodeSize = totalSize;
                memcpy((void *)pNew->sbData, (void *)sbData, shDataSize);

                p = (FreeNode *)((char *)p + totalSize);
                p->cGC = 'F';
                p->shNodeSize = shDiff;
                p->pFreeNext = pMgr->pFreeHead;
                pMgr->pFreeHead = p;

            }
            else{
                if(!pPrev)
                    pMgr->pFreeHead = p->pFreeNext;
                else
                    pPrev->pFreeNext = p->pFreeNext;

                pNew = (InUseNode *)p;
                pNew->cGC = 'U';
                pNew->shNodeType = shNodeType;
                memcpy((void *)pNew->sbData, (void *)sbData, shDataSize);
            }

            return pNew->sbData;
        }
        else
        {
            pPrev = p;
            p = p->pFreeNext;
        }
    }

    pmmResult->rc = RC_NOT_AVAIL;
    memcpy((void*)pmmResult->szErrorMessage, errMsg, strlen(errMsg)+1);
    return (void *)0;
}

void mmInit(StorageManager *pMgr)
{
    pMgr->pFreeHead = (FreeNode *)pMgr->pBeginStorage;
    memset((void *)pMgr->pBeginStorage, 0, pMgr->iHeapSize);
    pMgr->pFreeHead->cGC = 'F';
    pMgr->pFreeHead->shNodeSize = pMgr->iHeapSize;
    pMgr->pFreeHead->pFreeNext = (FreeNode *)0;
}

void mmMark(StorageManager *pMgr, MMResult *pmmResult)
{
    char *p;
    short shTempSize;

    for(p = pMgr->pBeginStorage; p < pMgr->pEndStorage; p += shTempSize)
    {
        shTempSize = ((InUseNode *)p)->shNodeSize;
        ((InUseNode *)p)->cGC = 'C';
    }
}

void mmFollow(StorageManager *pMgr, void *pUserData, MMResult *pmmResult)
{
    if(!pUserData)
        return;

    InUseNode *p;
    int iIndex;
    short shNodeType;
    MetaAttr *pAttr;
    void **ppUserData;

    p = (InUseNode *)((char *)pUserData - NODE_OVERHEAD_SZ);
    shNodeType = p->shNodeType;

    switch(p->cGC)
    {
        case 'C':
            p->cGC = 'U';
            for(iIndex = pMgr->nodeTypeM[shNodeType].shBeginMetaAttr; pMgr->metaAttrM[iIndex].shNodeType == shNodeType; iIndex++)
            {
                pAttr = &(pMgr->metaAttrM[iIndex]);
                if(pAttr->cDataType == 'P')
                {
                    ppUserData = (void **)&p->sbData[pAttr->shOffset];
                    mmFollow(pMgr, *ppUserData, pmmResult);
                }
            }
            break;
        case 'U':
            return;
    }
}

void mmCollect(StorageManager *pMgr, MMResult *pmmResult)
{
    char *p;
    char *pTrace;
    char *pPrev = (char *)0;
    FreeNode *pNew;
    short shTempSize;
    int totalSize;
    
    p = pMgr->pBeginStorage;
    while(p < pMgr-> pEndStorage)
    {
        shTempSize = ((FreeNode *)p)->shNodeSize;
        pTrace = p + shTempSize;
        if(((FreeNode *)p)->cGC == 'C')
        {
            if(pTrace < pMgr->pEndStorage && ((FreeNode *)pTrace)->cGC == 'C')
            {
                printf("\tCombining %08lX with %08lX\n", ULAddr(p), ULAddr(pTrace));
                pNew = (FreeNode *)p;
                totalSize = ((FreeNode *)p)->shNodeSize + ((FreeNode *)pTrace)->shNodeSize;
                pNew->shNodeSize = totalSize;
            }

            else
            {
                printf("\tCollecting %08lX\n", ULAddr(p));
                pNew = (FreeNode *)p;
                pNew->pFreeNext = (FreeNode *)pPrev;
                pPrev = p;
                p += shTempSize;
            }
        }
        else
            p += shTempSize;
    }

    pMgr->pFreeHead = (FreeNode *)pPrev;
}

void mmAssoc(StorageManager *pMgr, void *pUserDataFrom, char szAttrName[], void *pUserDataTo, MMResult *pmmResult){

    int i = 0;
    short shOffset;
    bool bFound=false;

    for (i = 0; strcmp(pMgr->metaAttrM[i].szAttrName, "END_OF_ATTR"); i++) {
        if(strcmp(pMgr->metaAttrM[i].szAttrName, szAttrName) == 0) {
            shOffset = pMgr->metaAttrM[i].shOffset;
            if ((pMgr->metaAttrM[i].cDataType) != 'P') {
                pmmResult->rc = RC_ASSOC_ATTR_NOT_PTR;
                strcpy(pmmResult->szErrorMessage, "Not a pointer can't assoc\n");
                return;
            }
            bFound = true;
            break;
        }
    }

    if (!bFound) {
        pmmResult->rc = RC_ASSOC_ATTR_NOT_FOUND;
        strcpy(pmmResult->szErrorMessage,"attb does not exist\n");
        return;
    }

    char *pLoc = (char *)pUserDataFrom - NODE_OVERHEAD_SZ;
    InUseNode *pInUseFrom = (InUseNode *)pLoc;
    void **ppNode = (void **)&(pInUseFrom->sbData[shOffset]);
    *ppNode = pUserDataTo;
    return;
}