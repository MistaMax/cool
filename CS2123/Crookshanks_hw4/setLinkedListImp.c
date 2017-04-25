#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxBuffer 100;

typedef struct cell{
	setElementT x;
	cellT *link;
}cellT;

struct setCDT {
	cellT *start;
	cellT *cursor;
}; 

setADT setNew() /* create a new empty set */
{
	setADT tmp;
	tmp = (setADT)malloc(sizeof(struct setCDT));
	tmp->start = (cellT *)malloc(sizeof(cellT));
	tmp->cursor = tmp->start;
	tmp->cursor->x=NULL;
	return tmp;
}

void setFree(setADT S) /* free the space allocated for the set S */
{
	myDataT *temp, *curr;
	for(curr=a->start; curr != NULL; curr=temp)
	{
		temp = curr->next;
		free(curr);
	}
	free(S);
}

int setInsertElementSorted(setADT S, setElementT E)
{
	cellT *b, *prev, *curr;
	b = (cellT *)malloc(sizeof(cellT));
	if (b == NULL) return;
	b->x = E;
	b->next = NULL;
	prev = NULL;
	curr = S->start;
	while (curr) {
		if (curr->x >= b->x) break;
		prev = curr;
		curr = curr->next;
	}
	if(curr->x!=b->x)
	{
		if (prev == NULL) {
			b->next = S->start;
			S->start = b;
		}
		else {
			b->next = prev->next;
			prev->next = b;
		}
	}
}
	
/* if not successful, return 0; otherwise, return the num of elements after the insertion.
Also note that the elements might be given in different orders, but your function should always
keep the set in a sorted manner after each insertion */
setADT setUnion(setADT A, setADT B) /* returns a new set containing A ∪ B */
{
	setADT c;
	cellT *U=NULL, *target, *tmp, *end, *a, *b;
	a=A->start;
	b=B->start;
	c=(setADT)malloc(sizeof(setADT));
	while(a || b)
	{
		tmp = (cellT *) malloc(sizeof(cellT));
		if(tmp==NULL){
			printf("memory can not be allocated\n");
			exit(-1);
		}
		tmp->next = NULL;
		if(U==NULL)
			U=tmp;
		else
			end->next=tmp;
		end = tmp;
		
		if(a && b && a->x == b->x){
			target = a;
			a = a->next;
			b = b->next;
		}
		else if(b==NULL || a && a->x < b->x){
				target=a;
			a=a->next;
		}
		else{
			target=b;
			b=b->next;
		}
		tmp->x = target->x;
	}
        c->start=U;
	return c;
	
}
setADT setIntersection(setADT A, setADT B); /* returns a new set containing A ∩ B */
{
        setADT c;
        c=(setADT)malloc(sizeof(setADT));
	cellT *U=NULL, *target, *tmp, *end, *a, *b;
	a=A->start;
	b=B->start;
	while(a || b)
	{
		tmp = (cellT *) malloc(sizeof(cellT));
		if(tmp==NULL){
			printf("memory can not be allocated\n");
			exit(-1);
		}
		tmp->next = NULL;
		if(U==NULL)
			U=tmp;
		else
			end->next=tmp;
		end = tmp;
		
		if((a && b) && a->x == b->x){
			target = a;
			a = a->next;
			b = b->next;
		}
		else if(b==NULL || (a && a->x < b->x)){
			a=a->next;
		}
		else{
			b=b->next;
		}
		tmp->x = target->x;
	}
        c->start=U;
	return U;
}

setADT setDifference(setADT A, setADT B);  /* returns a new set containing A \ B */
{
	
	setADT c;
        c=(setADT)malloc(sizeof(setADT));
        c->start=NULL;
        cellT *tmp, *a, *b;
	int k;
	for(a=A->start; a == NULL; a=a->pNext)
	{
		k = 0;
		for(b=B->start; b == NULL; b=b->pNext)
		{
			if(b->x == a->x)
				k++;
		}
		if(k == 0)
		{
                        if(c->start==NULL)
                        {
                                tmp=(cellT *)malloc(sizeof(cellT));
                                tmp->next=NULL;
                                c->start=tmp;
                        }
                        else
                        {
                                tmp->next=(cellT *)malloc(sizeof(cellT));
                                tmp=tmp->next;
                        }
			tmp = a;
		} 
	}
	return c;
}

int setCardinality(setADT S); /* return the number of elements in S */
{
    int count
    cellT *p;
    for(p=S->start;p!=NULL;p=p->next)
    {
        count++;
    }
    return count;
}

void setPrint(setADT S, char *name); /* print elements of S, A = {2, 5, 7} */
{
	cellT *p;
	printf("%s:",name);
	for(p=S->start;p != NULL; p=p->next)
	{
		printf("%i", p->x);
		if(p->next != NULL)printf(", ");
	}
	printf("}\n");
}
