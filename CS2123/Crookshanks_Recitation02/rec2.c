#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void increaseA(int val) { val++; }
void increaseB(int *pval) { pval++; }
void increaseC(int *pval) { *pval++; }
void increaseD(int *pval) { (*pval)++; }
void exchange(int **a,int **b)
{
    int *c;
    c=*a;
    *a=*b;
    *b=c;
}
int main()
{
    int a=10, b=20, c=30;
    int *pa,*pb,*pc;
    int **ppa, **ppb, **ppc;
    pa=&a;
    pb=&b;
    pc=&c;
    ppa=&pa;
    ppb=&pb;
    ppc=&pc;
    int sum;
    sum=a+ *pb + **ppc;
    printf("%i\n",sum);
    printf("Before:\na=%i b=%i \n",a,b);
    int temp;
    temp = *pa;
    *pa = **ppb;
    **ppb = temp;
    printf("After:\na=%i b=%i \n",a,b);
    int *ptemp;
    ptemp = pa;
    pa = *ppb;
    *ppb = ptemp;
    printf("a=%i b=%i *pa=%i *pb=%i\n",a,b,*pa,*pb);//the reason why the values of a and b have not changed is because they have not been altered, only pa and pb switched addresses therefore *pa = b and *pb = a
    increaseA(a);//this does not increace a at all because it is not editing the place in memory it is at
    printf("a=%i\n",a);
    increaseB(&a);//this does not alter a because this function only increaces an address in memory
    printf("a=%i\n",a);
    increaseC(&a);//this function increaces the memory adress as well
    printf("a=%i\n",a);
    increaseD(&a);//this does increace the value of of a because it prioritises the asterix using the parentheses and then increaces the value of a
    printf("a=%i\n",a);
    printf("pa=%p pb=%p *pa=%d *pb=%d\n",pa,pb,*pa,*pb);
    exchange (&pa, &pb);//This one works because the input is two addresses of 2 pointers which makes switching the pointers an easy task
    printf("pa=%p pb=%p *pa=%d *pb=%d\n",pa,pb,*pa,*pb);
    exchange (&pa, ppb);//this one works because ppb contains the address of the pointer pb and the address of pa is also an input
    printf("pa=%p pb=%p *pa=%d *pb=%d\n",pa,pb,*pa,*pb);
    exchange(ppa,ppb);// finally this one works as well because ppa has the address of pa and ppb has the address of pb
    printf("pa=%p pb=%p *pa=%d *pb=%d\n",pa,pb,*pa,*pb);
}
