#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int input=0;
	printf("Enter numbers in figures; use a negative value to stop\n");
	while(input>=0)
	{
		scanf("%i",&input);
		printf("\n");
		printf("Number: %i\n",input);
		if(input<1000000&&input>=0)
		{
			if(input>=0&&input<=19)printOneDigit(input);
			else processThousands(input);
			printf("\n");
		}
		else if(input>=1000000)
		{
			printf("Invalid Input!\n");
		}
	}
	return 0;
}

void printOneDigit(int d)
{
	switch (d) {
	case 0: printf("zero");break;
	case 1: printf("one");break;
	case 2: printf("two");break;
	case 3: printf("three");break;
	case 4: printf("four");break;
	case 5: printf("five");break;
	case 6: printf("six");break;
	case 7: printf("seven");break;
	case 8: printf("eight");break;
	case 9: printf("nine");break;
	case 10: printf("ten");break;
	case 11: printf("eleven");break;
	case 12: printf("twelve");break;
	case 13: printf("thirteen");break;
	case 14: printf("fourteen");break;
	case 15: printf("fifteen");break;
	case 16: printf("sixteen");break;
	case 17: printf("seventeen");break;
	case 18: printf("eighteen");break;
	case 19: printf("nineteen");break;
	}
}

void printAddOns(int d)
{
	switch (d) {
	case 20: printf("twenty");break;
	case 30: printf("thirty");break;
	case 40: printf("fourty");break;
	case 50: printf("fifty");break;
	case 60: printf("sixty");break;
	case 70: printf("seventy");break;
	case 80: printf("eighty");break;
	case 90: printf("ninety");break;
	case 100: printf("hundred");break;
	case 1000: printf("thousand");break;
	}
}

void processTens(int i)
{
	int remainder=i%10;
	int ten=i-remainder;
	if(i>=1&&i<=19)
	{
		printOneDigit(i);
		printf(" ");
	}
	else
	{
		printAddOns(ten);
		printf(" ");
		if(remainder!=0)
		{
			printOneDigit(remainder);
			printf(" ");
		}
	}
}

void processHundreds(int i)
{
	int remainder=i%100;
	int type=i/100;
	if(type!=0)
	{
		printOneDigit(type);
		printf(" ");
		printAddOns(100);
		printf(" ");
	}
	if(remainder!=0)
	{
		processTens(remainder);
	}
}

void processThousands (int i)
{
	int remainder=i%1000;
	int type=i/1000;
	if(type==0)processHundreds(i);
	else
	{
		processHundreds(type);
		printf(" ");
		printAddOns(1000);
		printf(" ");
		processHundreds(remainder);
	}
}
