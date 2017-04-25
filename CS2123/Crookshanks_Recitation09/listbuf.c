/*
 * File: listbuf.c
 * ---------------
 * This file implements the buffer.h abstraction using a linked
 * list to represent the buffer.
 */

#include <stdio.h>
#include <string.h>
#include "genlib.h"
#include "strlib.h"
#include "buffer.h"

/* Types */

typedef struct cellT {
    char ch;
    struct cellT *link;
} cellT;

struct bufferCDT {
    cellT *start;
    cellT *cursor;
};

/*
 * Implementation notes: NewBuffer
 * -------------------------------
 * This function allocates an empty editor buffer, represented
 * as a linked list.  To simplify the link list operation, this
 * implementation adopts the useful programming tactic of
 * keeping an extra "dummy" cell at the beginning of each list,
 * so that the empty buffer has the following representation:
 *
 *     +-------+          +------+
 *     |   o---+-----====>|      |
 *     +-------+    /     +------+
 *     |   o---+---/      | NULL |
 *     +-------+          +------+
 */

bufferADT NewBuffer(void)
{
    bufferADT buffer;

    buffer = New(bufferADT);
    buffer->start = buffer->cursor = New(cellT *);
    buffer->start->link = NULL;
    return (buffer);
}

/*
 * Implementation notes: FreeBuffer
 * --------------------------------
 * FreeBuffer must free every cell in the buffer as well as
 * the buffer storage itself.  Note that the loop structure
 * is not exactly the standard idiom for processing every
 * cell within a linked list, because it is not legal to
 * free a cell and later look at its link field.  To avoid
 * selecting fields in the structure after it has been freed,
 * you have to copy the link pointer before calling FreeBlock.
 */

void FreeBuffer(bufferADT buffer)
{
    cellT *cp, *next;

    cp = buffer->start;
    while (cp != NULL) {
        next = cp->link;
        FreeBlock(cp);
        cp = next;
    }
    FreeBlock(buffer);
}

void MoveCursorForward(bufferADT buffer)
{
    if (buffer->cursor->link != NULL) {
        buffer->cursor = buffer->cursor->link;
    }
}

void MoveCursorBackward(bufferADT buffer)
{
    cellT *cp;

    if (buffer->cursor != buffer->start) {
        cp = buffer->start;
        while (cp->link != buffer->cursor) {
             cp = cp->link;
        }
        buffer->cursor = cp;
    }
}

void MoveCursorToStart(bufferADT buffer)
{
    buffer->cursor = buffer->start;
}

void MoveCursorToEnd(bufferADT buffer)
{
    while (buffer->cursor->link != NULL) {
        MoveCursorForward(buffer);
    }
}

void InsertCharacter(bufferADT buffer, char ch)
{
    cellT *cp;

    cp = New(cellT *);
    cp->ch = ch;
    cp->link = buffer->cursor->link;
    buffer->cursor->link = cp;
    buffer->cursor = cp;
}

void DeleteCharacter(bufferADT buffer)
{
    cellT *cp;

    if (buffer->cursor->link != NULL) {
        cp = buffer->cursor->link;
        buffer->cursor->link = cp->link;
        FreeBlock(cp);
    }
}

void DisplayBuffer(bufferADT buffer)
{
    cellT *cp;

    for (cp = buffer->start->link; cp != NULL; cp = cp->link) {
        printf(" %c", cp->ch);
    }
    printf("\n");
    for (cp = buffer->start; cp != buffer->cursor; cp = cp->link) {
        printf("  ");
    }
    printf("^\n");
}

/* SINGLE LINKED LIST */
//replaces a char in the LL buffer
void ReplaceCharInBuffer(bufferADT buffer, char oldch, char newch)
{
    cellT *tmp;
    for(tmp=buffer->cursor;tmp!=NULL;tmp=tmp->link)
    {
        if(tmp->ch==oldch)
        {
            tmp->ch=newch;
            buffer->cursor=tmp;
            break;
        }
    }
}
//looks for a string in the ll buffer, returns 1 if found, 0 if not
int SearchStrBuffer(bufferADT buffer, char* str)
{
    cellT *found, *tmp;
    int i = 1, iFound = 0;
    for(tmp=buffer->cursor;tmp!=NULL;tmp=tmp->link)
    {
        if(iFound=1)break;
        if(tmp->ch==str[1])
        {
            iFound=1;
            found=tmp->link;
            for(i = 2; i < strlen(str);i++)
            {
                if(found->ch != str[i] || found == NULL) 
                {
                    iFound=0;
                    break;
                }
                found=found->link;
            }
        }
    }
    if(iFound==1)buffer->cursor=tmp;
    return iFound;
}
