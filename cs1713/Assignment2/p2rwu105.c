/**********************************************************************
p2rwu105.c  (change the name to use your abc123 id)
Purpose:
This program reads customer transactions to produce output
suitable as a Library Receipt.
Command Line Arguments:
p1  -c  customerTransactionFileName
Input:
Stream input file which contains many customers, each
containing possibly many book transactions.  There are three different
kinds of lines of data for each transaction:
- Customer Identification Information:
o One line per customer (separated by spaces)
szCustomerId  dFeeBalanace  szEmailAddr  szFullName
6s              lf           40s           30s (may contain spaces)
o Although szFullName is a maximum of 30 characters, it may
contain spaces; therefore, you cannot simply use %30s.
For szFullName, you will have to use a bracket format
code: %30[^\n] which doesn't have an 's' in it.
- Customer Address Information:
o One line per customer (separated by commas)
o szStreetAddress              szCity   szStateCd   szZipCd
30s (may contain spaces)   20s      2s          5s
o Although szStreetAddress is a maximum of 30 characters,
it may contain spaces; therefore, you cannot simply use %30s.
You will have to use a bracket format code using %[^,]
o You do not need another while loop for this address information
since there is only one per customer.  You will need to use fgets
and an if statement.
- Book Transaction:
o 0 to many book transactions per customer (terminated by END in the Book ID)
o cTransType    szBookId   szTransDt
1c            s9              s10
o cTransType must be either C for check out or R for return

Results:
Prints each Library Receipt in a readable format.
Examples:
******************** Library Receipt ***********************
111111 petem@xyz.net Pete Moss (previously owed 0.75)
123 Boggy Lane
New Orleans LA 70112
Trans  Book       Date
C    JOYPGM001  2016-01-25
C    TECHDR001  2016-01-25
******************** Library Receipt ***********************
222222 pcorn@abc.net Pop Corn (previously owed 0.00)
456 Kernel
San Antonio TX 78210
Trans  Book       Date
C    TECHDR001  2016-01-25
C    TECHDR002  2016-01-25
C    JOYPGM004  2016-01-25
Returns:
0  normal
-1 invalid command line syntax
-2 show usage only
-3 error during processing, see stderr for more information
Notes:
p1 -?  will provide the usage information.  In some shells,
you will have to type reserve -\?

**********************************************************************/
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p2.h"

FILE *pFileCust;//input file for the customer file
FILE *pFileBook;//input file for the book file


int main(int argc, char *argv[])
{
	char *pszCustomerFileName = NULL;
	char *pszBookFileName = NULL;
	Book bookM[MAX_BOOKS];

	processCommandSwitches(argc, argv, &pszCustomerFileName, &pszBookFileName);

	if (pszCustomerFileName == NULL)
		exitError(ERR_MISSING_SWITCH, "-c");//Exits if the customer switch is not there
	if (pszBookFileName == NULL)
		exitError(ERR_MISSING_SWITCH, "-b");//Exits if the book switch is not there
        //openning the files
	pFileCust = fopen(pszCustomerFileName, "r");
	pFileBook = fopen(pszBookFileName, "r");
        //Checking if the file input works for book and customer
	if (pFileCust == NULL)
		exitError(ERR_CUSTOMER_FILENAME, pszCustomerFileName);
	if (pFileBook == NULL)
		exitError(ERR_BOOK_FILENAME, pszBookFileName);
        //reading the file for all the pook information and putting it into the Book  bookM Array
	int iBookCnt = getLibrary(bookM);
        //Processing all the customers and their transactions
	processCustomers(bookM,iBookCnt);
        //Prints the library after all the transactions were processed
	printLibrary(bookM, iBookCnt);
        //Closing all the files
	fclose(pFileCust);
	fclose(pFileBook);
	printf("\n");
	return 0;
}

/****** you need to document and code this function *****/

void processCustomers(Book bookM[],int iBookCount)
{
	int iBookNum;
	char szInputBuffer[100];
	int iAccNum = 0;
	int iscanfCnt;
	double dTotalFees;
	double dProcessOutput;
	Customer customer;
	Transaction transaction;
	int looper = 1;
	printLibrary(bookM, iBookCount);
	while (fgets(szInputBuffer, 100, pFileCust) != NULL)
	{
		iAccNum++;
		iscanfCnt = sscanf(szInputBuffer, "%6s %lf %40s %30[^\n]\n",
			customer.szCustomerId,
			&customer.dFeeBalance,
			customer.szEmailAddr,
			customer.szFullName);//Getting name and information

		if (iscanfCnt < 4)
		{
			fprintf(stderr, "Error: Improper listing on line 1 of Account Number %d \n", iAccNum);
			exit(ERROR_PROCESSING);
		}

		if (fgets(szInputBuffer, 100, pFileCust) == NULL)//exits the program if there is nothing there
		{
			fprintf(stderr, "Error: fgets is null on line 2 of Account Number %d \n", iAccNum);
			exit(ERROR_PROCESSING);
		}

		iscanfCnt = sscanf(szInputBuffer, "%30[^,] ,%20[^,] ,%2s ,%5s \n",
			customer.szStreetAddress,
			customer.szCity,
			customer.szStateCd,
			customer.szZipCd);//scaning for the Address

		if (iscanfCnt < 4)//exit the code displaying and error if the iscanfCnt is less than 4
		{
			fprintf(stderr, "Error: Bad Input for Address Line (line 2) of Account Number %d \n", iAccNum);
			exit(ERROR_PROCESSING);
		}
		//printing the first 2 read lines in the receipt
		printf("******************** Library Receipt ***********************\n");

		printf("%s %s %s (previously owed %0.2f)\n",
			customer.szCustomerId,
			customer.szEmailAddr,
			customer.szFullName,
			customer.dFeeBalance);

		printf("%s \n%s %s %s\n",
			customer.szStreetAddress,
			customer.szCity,
			customer.szStateCd,
			customer.szZipCd);

		printf("%-5s %-4s %-5s \n", "Trans", "Book", "Date");
		iBookNum = 0;
		dTotalFees = customer.dFeeBalance;
		while (fgets(szInputBuffer, 100, pFileCust) != NULL)
		{
			iBookNum++;
			iscanfCnt = sscanf(szInputBuffer, "%1c %9s %10s",
				&transaction.cTransType,
				transaction.szBookId,
				transaction.szTransDt);//Getting Book information

			if (iscanfCnt < 3)
			{
				fprintf(stderr, "Bad Input for Book Number %d on Account Number %d \n", iBookNum, iAccNum);
				exit(ERROR_PROCESSING);
			}

			if (transaction.cTransType == 'X')//This is the end of the book detection sequence, we could also use the parameter transaction.szBookId=="END"
				break;
			printf("%-5c %-4s %-5s ",
				transaction.cTransType,
				transaction.szBookId,
				transaction.szTransDt);
                        //Processing the transaction
			dProcessOutput = processTransaction(bookM, iBookCount, customer, transaction);
			if (dProcessOutput > 0)
				dTotalFees += dProcessOutput;
			printf("\n");
		}
		printf("\t\t\t\tTotal Fees: %.2lf\n", dTotalFees);
	}
}


/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName)
Purpose:
Checks the syntax of command line arguments and returns the filenames.
If any switches are unknown, it exits with an error.
Parameters:
I   int argc                        count of command line arguments
I   char *argv[]                    array of command line arguments
O   char **ppszCustomerFileName     customer transaction file name
Notes:
If a -? switch is passed, the usage is printed and the program exits
with USAGE_ONLY.
If a syntax error is encountered (e.g., unknown switch), the program
prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName, char **ppszBookFileName)
{
	int i;//the section of the code segment
	for (i = 1;i < argc;i++)
	{
		if (argv[i][0] != '-')
			exitUsage(1, ERR_EXPECTED_SWITCH, argv[i]);
		switch (argv[i][1])
		{
		case 'b':
			if (++i >= argc)
				exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
			else
				*ppszBookFileName = argv[i];
			break;

		case 'c':
			if (++i >= argc)
				exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
			else
				*ppszCustomerFileName = argv[i];
			break;

		default:
			exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
		}
	}
}

/******************** exitError *****************************
void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
Prints an error message and diagnostic to stderr.  Exits with
ERROR_PROCESSING.
Parameters:
I char *pszMessage              error message to print
I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
	fprintf(stderr, "Error: %s %s\n"
		, pszMessage
		, pszDiagnosticInfo);
	exit(ERROR_PROCESSING);
}
/******************** exitUsage *****************************
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
If this is an argument error (iArg >= 0), it prints a formatted message
showing which argument was in error, the specified message, and
supplemental diagnostic information.  It also shows the usage. It exits
with ERR_COMMAND_LINE_SYNTAX.

If this is just asking for usage (iArg will be -1), the usage is shown.
It exits with USAGE_ONLY.
Parameters:
I int iArg                      command argument subscript
I char *pszMessage              error message to print
I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
	if (iArg >= 0)
		fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
			, iArg
			, pszMessage
			, pszDiagnosticInfo);
	fprintf(stderr, "p1 -c customerTransactionFile\n");
	if (iArg >= 0)
		exit(-1);
	else
		exit(-2);
}

/******************** getLibrary *****************************
int getLibrary(Book bookM[])
Purpose:
Retrieves the books using the FILE pointer, pFileBook, that
you defined above the main function and returns a count of the number of books.
Parameters:
O   Book bookM[]    an array which is used for returning the books.
Returns:
A count of the number of read.
Notes:
1. Uses pFileBook as the FILE pointer for reading the file.  It must
have been opened with fopen prior to calling this function.
2. The data in the data file is in this format
szBookId szCustomerId szCheckedOutDt dLateFeePerDay dMaxLateFee szTitle
9s        6s             10s           lf            lf          40s (may contain spaces)
**************************************************************************/
int getLibrary(Book bookM[])
{
	int i = 0;
	char szInputBuffer[100];
	int iScanfCnt = 0;
	// Read the books until EOF
	while (fgets(szInputBuffer, 100, pFileBook) != NULL)
	{
		// check for too many books to fit in the bookM array
		if (i >= MAX_BOOKS)
			exitError(ERR_TOO_MANY_BOOKS, szInputBuffer);
		iScanfCnt = sscanf(szInputBuffer, "%9s %6s %10s %lf %lf %[^\n]\n"
			, bookM[i].szBookId
			, bookM[i].szCustomerId
			, bookM[i].szCheckedOutDt
			, &bookM[i].dLateFeePerDay
			, &bookM[i].dMaxLateFee
			, bookM[i].szTitle);

		// It should have populated all six variables, if not exit with
		// an error.
		if (iScanfCnt < 6)
			exitError(ERR_BOOK_DATA, szInputBuffer);
		i++;
	}
	return i;
}
/******************** validateDate ***********************************
int validateDate(char szDate[], UtsaDate *pDate);
Purpose:
Validates the date and returns (via the second parameter) the
UtsaDate.
Parameters:
I char szDate[]         Date as a string in the form "yyyy-mm-dd"
O UtsaDate *pDate       Address of a UtsaDate structure for
returning the date.
Notes:
1. The length must be 10 characters.
2. The date must be in the form "yyyy-mm-dd".
3. The month must be 01-12.
4. The day must be between 1 and the max for each month
Mar 31 Aug 31 Jan 31
Apr 30 Sep 30 Feb 29
May 31 Oct 31
Jun 30 Nov 30
Jul 31 Dec 31
5. If Feb 29 was specified, validate that the year is a leap year.
Return Value:
0     date is valid
1     year is invalid
2     month is invalid
3     day is invalid
4     invalid length or format
**********************************************************************/
int validateDate(char szDate[], UtsaDate *pDate)
{
	static int iDaysPerMonth[] =
	{ 0, 31, 29, 31
		, 30, 31, 30
		, 31, 31, 30
		, 31, 30, 31 };
	int iCharCnt = 0;
	int iScanfCnt;

	// Check for too few characters for the yyy-mm-dd format
	if (strlen(szDate) != 10)
		return 4;  // invalid format due to length

				   // The year should be 4 characters 
	iCharCnt = strspn(szDate, "0123456789");
	if (iCharCnt != 4)
		return 1;  // invalid year

				   // Use sscanf to pluck out the year, month, and day
	iScanfCnt = sscanf(szDate, "%4d-%2d-%2d"
		, &pDate->iYear
		, &pDate->iMonth
		, &pDate->iDay);
	// If sscanf returned less than 3, then something was bad
	if (iScanfCnt < 3)
		return 4;  // invalid format

				   // Validate Month
	if (pDate->iMonth < 1 || pDate->iMonth > 12)
		return 2;  // month invalid

				   // Validate day based on max days per month 
	if (pDate->iDay < 1 || pDate->iDay > iDaysPerMonth[pDate->iMonth])
		return 3;  // day invalid

				   // if the 29th of Feb, check for leap year
	if (pDate->iDay == 29 && pDate->iMonth == 2)
	{
		if (pDate->iYear % 4 == 0 && (pDate->iYear % 100 != 0 || pDate->iYear % 400 == 0))
			return 0;    // it is a leap year
		else return 3;   // not a leap year, so the day is invalid
	}
	return 0;
}

/******************** dateDiff ***********************************
int dateDiff(char szDate1[], char szDate2[])
Purpose:
Validates the dates and returns the difference in days of the
first date minus the second date.
Parameters:
I char szDate1[]        First date as a string in the form "yyyy-mm-dd"
I char szDate2[]        Second date as a string in the form "yyyy-mm-dd"
Notes:
1. We validate/convert the days to UtsaDate format.  If the date is
invalid, we exit and show a message.
2. For each of the dates, we determine the number of days since
"0000-03-01" by starting the count at 1 for 0000-03-01. Using
March 1st eliminates some leap day issues.
3. Return the difference in days
Return Value:
the difference in dates
**********************************************************************/
int dateDiff(char szDate1[], char szDate2[])
{
	UtsaDate date1;
	UtsaDate date2;
	int iJulian1;
	int iJulian2;

	if (validateDate(szDate1, &date1) != 0)
		exitError("Invalid 1st date for dateDiff: ", szDate1);

	if (validateDate(szDate2, &date2) != 0)
		exitError("Invalid 2nd date for dateDiff: ", szDate2);

	iJulian1 = utsaDateToUtsaJulian(date1);
	iJulian2 = utsaDateToUtsaJulian(date2);

	return iJulian1 - iJulian2;
}

/******************** utsaDateToUtsaJulian ***********************************
int utsaDateToUtsaJulian(UtsaDate date)
Purpose:
Converts a date to a UTSA Julian Days value.  This will start numbering
at 1 for 0000-03-01. Making dates relative to March 1st helps eliminate
some leap day issues.
Parameters:
I char szDate1[]        First date as a string in the form "yyyy-mm-dd"
I char szDate2[]        Second date as a string in the form "yyyy-mm-dd"
Notes:
1 We replace the month with the number of months since March.
March is 0, Apr is 1, May is 2, ..., Jan is 10, Feb is 11.
2 Since Jan and Feb are before Mar, we subtract 1 from the year
for those months.
3 Jan 1 is 306 days from Mar 1.
4 The days per month is in a pattern that begins with March
and repeats every 5 months:
Mar 31 Aug 31 Jan 31
Apr 30 Sep 30
May 31 Oct 31
Jun 30 Nov 30
Jul 31 Dec 31
Therefore:
Mon  AdjMon  NumberDaysFromMarch (AdjMon*306 + 5)/10
Jan    10      306
Feb    11      337
Mar     0        0
Apr     1       31
May     2       61
Jun     3       92
Jul     4      122
Aug     5      153
Sep     6      184
Oct     7      214
Nov     8      245
Dec     9      275
5 Leap years are
years that are divisible by 4 and
either years that are not divisible by 100 or
years that are divisible by 400
Return Value:
the number of days since 0000-03-01 beginning with 1 for
0000-03-01.
**********************************************************************/
int utsaDateToUtsaJulian(UtsaDate date)
{
	int iCountDays;
	// Calculate number of days since 0000-03-01

	// If month is March or greater, decrease it by 3.
	if (date.iMonth > 2)
		date.iMonth -= 3;
	else
	{
		date.iMonth += 9;  // adjust the month since we begin with March
		date.iYear--;      // subtract 1 from year if the month was Jan or Feb
	}
	iCountDays = 365 * date.iYear                                // 365 days in a year
		+ date.iYear / 4 - date.iYear / 100 + date.iYear / 400   // add a day for each leap year
		+ (date.iMonth * 306 + 5) / 10                           // see note 4
		+ (date.iDay);                                          // add the days
	return iCountDays;
}
//Prints the library
void printLibrary(Book bookM[], int iBookCount)
{
	int i;
	printf("%-9s %-40s %-8s %-14s %-8s \n"
		, "Book Id"
		, "Book Title"
		, "Customer"
		, "Check Out Date"
		, "Late Fee");//printing the table headers
	for (i = 0;i < iBookCount;i++)//Loop for displaying the book info
	{
		printf("%-9s %-40s %-8s %-14s %-.2lf \n"
			, bookM[i].szBookId
			, bookM[i].szTitle
			, bookM[i].szCustomerId
			, bookM[i].szCheckedOutDt
			, bookM[i].dLateFeePerDay);
	}
}
//Processing all the transactions made by the customer
double processTransaction(Book bookM[], int iBookCnt, Customer customer, Transaction transaction)
{
	int iBookVal = findBook(bookM, iBookCnt, transaction.szBookId);//finds the book Id
	int iDateDifference;
        double dLateFee;

	if (iBookVal == -1)//Verifies if the book exists
	{
            printf("\tERROR: Book not found");
            return -1;
        }
	else if (transaction.cTransType == 'R')//Return Transaction
	{
		if (strcmp(bookM[iBookVal].szCustomerId, customer.szCustomerId)!=0)
                {
			printf("\tERROR: Customer does not own book that is being returned");
                        return -2;
                }//Not really required, just checking if someone stole a book or something
		iDateDifference=dateDiff(transaction.szTransDt, bookM[iBookVal].szCheckedOutDt);
                dLateFee=bookM[iBookVal].dLateFeePerDay*(iDateDifference-14);
                //Resetting the book info saying that the book is no longer checked out
                strcpy(bookM[iBookVal].szCustomerId,"NONE");
                strcpy(bookM[iBookVal].szCheckedOutDt,"0000-00-00");
                //Determining the fees that are to be charged on the customer
		if (iDateDifference < 14)
			return 0;
		else if (dLateFee >= bookM[iBookVal].dMaxLateFee)
			dLateFee=bookM[iBookVal].dMaxLateFee;

		printf("\tLate Fee: %.2lf", dLateFee);
	    	return dLateFee;
	}
	else if (transaction.cTransType == 'C')//Check Out Transaction
	{
		if (strcmp(bookM[iBookVal].szCustomerId,"NONE") != 0)//check if the book is checked out
			printf("\tERROR: Book already checked out by another customer");
		else
		{
			strcpy(bookM[iBookVal].szCustomerId, customer.szCustomerId);
			strcpy(bookM[iBookVal].szCheckedOutDt, transaction.szTransDt);
			return 0;
		}
		return -1;//returns -1 if something went wrong in the checking out process
	}
	else
		exitError("Invalid Transaction Type", "");//exit if there is no transaction type
}
//Simple code to find a book
int findBook(Book bookM[], int iBookCount, char szBookId[])
{
	int i;
	for (i = 0;i < iBookCount;i++)
	{
		if (strcmp(bookM[i].szBookId, szBookId) == 0)
			return i;
	}
	return -1;
}
