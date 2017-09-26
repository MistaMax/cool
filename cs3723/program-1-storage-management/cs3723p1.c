#include "cs3723p1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ADD PMM RESULT TO EVERYTHING
void mmInit(StorageManager *pMgr){
    pMgr->pFreeHead = (FreeNode *)pMgr->pBeginStorage;
    memset(pMgr->pBeginStorage,'\0',pMgr->iHeapSize);
    pMgr->pFreeHead->cGC = 'F';
    pMgr->pFreeHead->shNodeSize = pMgr->iHeapSize;
    pMgr->pFreeHead->pFreeNext = (FreeNode *)0;
}

void * mmAllocate(StorageManager *pMgr, short shDataSize, short shNodeType, char sbData[], MMResult *pmmResult)
{
    char *errMsg; //temp pointer for error message
    FreeNode *pPrev = (FreeNode *)0; //previous free node in free list
    FreeNode *pCurr = pMgr->pFreeHead; //the current free node in the list
    InUseNode *pNewNode = (InUseNode *)0; //enhance readability
    short shDiff; //stores leftover space after allocation
    int totalSize; //stores pNewNodes size

    while(pCurr && (char *)pCurr < pMgr->pEndStorage) //traces through free node list
    {
        if(pCurr->shNodeSize >= (shDataSize + NODE_OVERHEAD_SZ)) //find a node large enough to fit another one
        {
            shDiff = pCurr->shNodeSize - (shDataSize + NODE_OVERHEAD_SZ); //check if there's enough space for an in use node + free node
            if(shDiff >= pMgr->iMinimumNodeSize)
            {
                if(!pPrev)
                    pMgr->pFreeHead = pCurr->pFreeNext; //free node is in beginning of list
                else
                    pPrev->pFreeNext = pCurr->pFreeNext; //free node is somewhere else in the list

                totalSize = shDataSize + NODE_OVERHEAD_SZ;
                //totalSize = shDataSize + iMinumumNodeSize;
                pNewNode = (InUseNode *)pCurr;
                pNewNode->cGC = 'U'; //user input mark node as in use
                pNewNode->shNodeType = shNodeType;
                pNewNode->shNodeSize = totalSize;
                memcpy((void *)pNewNode->sbData, (void *)sbData, shDataSize);//allocate user node

                //if enough space is left over for a free node make a new free node
                pCurr = (FreeNode *)((char *)pCurr + totalSize);
                pCurr->cGC = 'F'; //set current to Free
                pCurr->shNodeSize = shDiff;
                pCurr->pFreeNext = pMgr->pFreeHead;
                pMgr->pFreeHead = pCurr; //insert free node at beginning of free list

            } //end if
            else{
                if(!pPrev) //beginning of free list
                    pMgr->pFreeHead = pCurr->pFreeNext;
                else
                    pPrev->pFreeNext = pCurr->pFreeNext;

                pNewNode = (InUseNode *)pCurr;
                pNewNode->cGC = 'U';
                pNewNode->shNodeType = shNodeType;
                memcpy((void *)pNewNode->sbData, (void *)sbData, shDataSize);
            }//end else

            return pNewNode->sbData;
        }//end if large enough node
        else
        {
            pPrev = pCurr;
            pCurr = pCurr->pFreeNext;
        }
    }//end while

    pmmResult->rc = RC_NOT_AVAIL;
    errMsg = "Free node not found";
    memcpy((void*)pmmResult->szErrorMessage, errMsg, strlen(errMsg)+1);
    return (void *)0;
} //end mmAllocate

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
    void **pp;

    pCurr = (InUseNode *)((char *)pUserData - NODE_OVERHEAD_SZ);
    shNodeType = pCurr->shNodeType;
    switch(pCurr->cGC)
    {
        case 'U':
            return;
            //break;
        case 'C':
            pCurr->cGC = 'U';
            for(iAttr = pMgr->nodeTypeM[shNodeType].shBeginMetaAttr; pMgr->metaAttrM[iAttr].shNodeType == shNodeType; iAttr++)
            {
                pAttr = &(pMgr->metaAttrM[iAttr]);
                if(pAttr->cDataType == 'P')
                    pp = (void **)&pCurr->sbData[pAttr->shOffset];
                    mmFollow(pMgr, *pp, pmmResult);
                /*{
                    pp = (void **)&pCurr->sbData[]
                }*/
            }
            break;
    }
}

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

/*void mmCollect(StorageManager *pMgr, MMResult *pmmResult)
{
    char *pCurr;
    char *pTrace;
    char *pPrev = (char *)0;
    FreeNode *pNewNode;
    short shTempSize;
    int totalSize;

    pMgr->pFreeHead = (FreeNode *)0;

    pCurr = pMgr->pBeginStorage;
    while(pCurr < pMgr->pEndStorage)
    {
        shTempSize = ((FreeNode *)pCurr)->shNodeSize;
        pTrace = pCurr + shTempSize;
        if(((FreeNode *)pCurr)->cGC == 'C')\
        {
            if(pTrace < pMgr->pEndStorage && ((FreeNode *)pTrace)->cGC == 'C')
            {
                printf("\tCombining  %08lX with %08lX\n", ULAddr(pCurr), ULAddr(pTrace));
                pNewNode = (FreeNode *)pCurr;
                totalSize = ((FreeNode *)pCurr)->shNodeSize + ((FreeNode *)pTrace)->shNodeSize;
                pNewNode->shNodeSize = totalSize;
            }
            else
            {
                printf("\tCollecting %08lX\n", ULAddr(pCurr));
                pNewNode = (FreeNode *)pCurr;
                pNewNode->cGC = 'F';
                pNewNode->pFreeNext = (FreeNode *)pPrev;
                pPrev = pCurr;
                pCurr += shTempSize;
            }
        }
        else
        {
            pCurr += shTempSize;
        }
    }
    pMgr->pFreeHead = (FreeNode *)pPrev;
}*/

void mmAssoc(StorageManager *pMgr, void *pUserDataFrom, char szAttrName[], void *pUserDataTo, MMResult *pmmResult){
    char *pUserNode;
    MetaAttr *pAttr;
    char *errMsg;
    short shNodeType;
    int iAt;
    void **ppNode;

    pUserNode = (char *)pUserDataFrom - NODE_OVERHEAD_SZ;
    shNodeType = ((InUseNode *)pUserNode)->shNodeType;

    for(iAt = pMgr->nodeTypeM[shNodeType].shBeginMetaAttr; iAt < MAX_NODE_ATTR && pMgr->metaAttrM[iAt].shNodeType == shNodeType; iAt++)
    {

        pAttr = &(pMgr->metaAttrM[iAt]);

        if(strcmp(pAttr->szAttrName, szAttrName) == 0)
        {
            if(pAttr->cDataType == 'P')
            {
                ppNode = (void **)&(((InUseNode *)pUserNode)->sbData[pAttr->shOffset]);
                *ppNode = pUserDataTo;
                return;
            }
            else
            {
                pmmResult->rc = RC_ASSOC_ATTR_NOT_PTR;
                sscanf(errMsg, "Attribute not a pointer: %s", szAttrName);
                memcpy((void *)pmmResult->szErrorMessage, errMsg, strlen(errMsg)+1);
                return;
            }
        }
    }
    pmmResult->rc = RC_ASSOC_ATTR_NOT_FOUND;
    sscanf(errMsg, "Attribute not found: %s", szAttrName);
    memcpy((void *)pmmResult->szErrorMessage, errMsg, strlen(errMsg)+1);
}