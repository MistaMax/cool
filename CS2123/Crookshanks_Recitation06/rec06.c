#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* #include "genlib.h"  */
#include "random.h"

int main(void)
{
	int secret, *s_a, attempt, ans, *a_a, inPlace, outPlace, dne, i, j, miss;			/*  Declare variables */
	Randomize();
        s_a=NewArray(4,int);
        a_a=NewArray(4,int);
	while (1) {
		secret = RandomInteger(1000, 9999);
		getDigits(secret, &(s_a), 1000);
		if (isDifferent(s_a) == true)
		{
			for (attempt = 1; attempt <= 40; i++) {
				//reset the analyzing variables
				inPlace = 0;
				outPlace = 0;
				dne = 0;//dne means does not exist
                                miss=false;
				//gets the guessed number
				printf("Enter your guess : ");
				scanf("%d", &ans);
				printf("\n");
				//breaks up the number into digits which are stored at the array a_a
				getDigits(ans, &(a_a), 1000);
				if (isDifferent(a_a) == false)
				{
					printf("ERROR: you did not enter a 4 digit number that has completely different digits\n");
					attempt--;//sets attempt back one so the user still has the same ammount of tries after the error
				}
				else
				{
					for (i = 0;i < 4;i++)
					{
                                                if(a_a[i]==s_a[i])inPlace++;
                                                else
                                                {
                                                        miss=true;//miss stands for missing
                                                        for(j=0;j<4;j++)
                                                        {
                                                                if(a_a[j]==s_a[i])
                                                                {
                                                                        outPlace++;
                                                                        miss=false;
                                                                        break;
                                                                }
                                                        }
                                                        if(miss==true)dne++;
                                                }
					}
					//now time to analyze the results
					if (inPlace == 4)//breaks the loop if all the digits are correct and in place
					{
						printf("You found the secret number!!!\n");
						break;//ends the loop because the user got it correct
					}
					else//prints out what is wrong if the number was not found
					{
						//prints out what digits are in place and what are out of place and what digits do not exist
						if (inPlace == 1)
							printf("1 digit is in place\n");
						else
							printf("%i digits are in place\n", inPlace);
						if (outPlace == 1)
							printf("1 digit is out of place\n");
						else
							printf("%i digits are out of place place\n", outPlace);
						if (dne == 1)
							printf("1 digit does not exist\n");
						else
							printf("%i digits do not exist\n", dne);
					}
				}
			}
		}
	}
	return 0;
}
