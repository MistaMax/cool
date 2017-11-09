#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#define true 1
#define false 0
typedef int bool;

typedef struct point {
	listElementT x;
	struct point *next;
} myDataT;

struct listCDT {
	myDataT *start; // myDataT *header;
	myDataT *end; // myDataT *foother;
};

listADT NewList()
{
	listADT tmp;
	tmp = (listADT)malloc(sizeof(struct listCDT)); // New(listADT);
	if (tmp == NULL) return NULL;
	tmp->start = tmp->end = NULL;
	return tmp;
}

void list_insert_sorted(listADT a, int val)
{
	myDataT *b, *prev, *curr;
	b = (myDataT *)malloc(sizeof(myDataT));
	if (b == NULL) return;
	b->x = val;
	b->next = NULL;
	prev = NULL;
	curr = a->start;
	while (curr) {
		if (curr->x >= b->x) break;
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL) {
		b->next = a->start;
		a->start = b;
	}
	else {
		b->next = prev->next;
		prev->next = b;
	}
	if (b->next == NULL)
		a->end = b;
}

void list_insert_unsorted(listADT a, int val)
// add val the end of the link list
{
	myDataT *b;
	b = (myDataT *)malloc(sizeof(myDataT));	if (b == NULL) return;
	b->x = val;
	b->next = NULL;
	if (a->start == NULL) {
		a->start = b;
	}
	else {
		a->end->next = b;
	}
	a->end = b;
}
//Frees the LL
void FreeList(listADT a)
{
	myDataT *temp, *curr;
	for(curr=a->start; curr; curr=temp)
	{
		temp = curr->next;
		free(curr);
	}
	free(a);
}
//prints the values of the LL
void list_print_values(listADT a, char *name)
{
  myDataT *d;
  printf("list %s contents\n", name);
  for(d = a->start; d != NULL; d = d->next)
  {
    printf("%d\n", d->x);
  }
}
//takes the average of the list
double list_average(listADT a)
{
  int total, count;
  count = 0;
  total = 0;
  myDataT *p;
  for(p = a->start; p!=NULL; p = p->next)
  {
    total += p->x;
    count ++;
  }
  if(count != 0)return total/count;
  return 0;
}
//deletes a certain number
void list_delete_by_value(listADT a, listElementT x)
{
  myDataT *p, *temp;
  bool found = false;
  for(p = a->start; p!= NULL; p = p->next)
  {
    if(p->x == x)
      {
	found = true;
	break;
      }
    else temp = p;
  }
  if(a->start->x== p->x)
  {
    a->start = p->next;
    free(p);
  }
  else
  {
    temp->next = p->next;
    free(p);
  }
  
}
//copies a LL
listADT list_n_copy(listADT a, int n)
{
  listADT d;
  myDataT *p;
  d = NewList();
  int count;
  count = 0;
  if(n >0)
    {
      list_insert_unsorted(d, a->start->x);
      p = a->start->next;
      for(count = 1;count < n && p != NULL; count++, p = p->next)
      {
        list_insert_unsorted(d, p->x);
      }
    }
  return d;
}
