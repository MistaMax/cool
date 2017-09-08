#include "cs3723p1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mmInit(StorageManager *pMgr, MMResult *pmmResult){
    
}

void * mmAllocate(StorageManager *pMgr, short shDataSize, short shNodeType, char sbData[], MMResult *pmmResult){
}

void mmMark(StorageManager *pMgr, MMResult *pmmResult){
}

void mmFollow(StorageManager *pMgr, void *pUserData, MMResult *pmmResult){
}

void mmCollect(StorageManager *pMgr, MMResult *pmmResult){
}

void mmAssoc(StorageManager *pMgr, void *pUserDataFrom, char szAttrName[], void *pUserDataTo, MMResult *pmmResult){
}