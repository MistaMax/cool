/**********************************************************************
p3rwu105.c by Max Crookshanks
Purpose:
    This program reads book information and a command file.   It 
    processes the commands against the book information.
    This is the driver code for the routines written by the students.
Command Parameters:
    p3 -b bookFileName -c commandFileName
Input:
    Book	same as Programming Assignment #2 although there is different data.

    Command	This is different from the previous assignment.  The file 
            contains  text in the form of commands.  
        CUSTOMER BEGIN szBookId szCustomerId szCheckedOutDt dLateFeePerDay dMaxLateFee szTitle  
            specifies the beginning of customer request and includes all the 
            identification information from program 2.
        CUSTOMER ADDRESS szStreetAddress,szCity,szStateCd,szZipCd
            specifies the address for a customer (separated by commas)
        CUSTOMER TRANS cTransType    szBookId   szTransDt
            specifies a single book transaction.  Steps:
            -	Print the Transaction Type, Book Id, and Transaction Date 
            -	Lookup the book ID using a binary search.  If not found, print a 
                warning (but do not terminate your program) and return.
            -	If the transaction date is invalid, show a message stating "invalid date", 
                but do not terminate.  Use the validateDate  function.
            -	If the transaction type is C (meaning checkout):
                o	If the book is already checked out, show a message stating 
                    "already checked out", but do not terminate.
                o	Otherwise, check out the book to this customer, setting the book's 
                    customer ID.  The book's checked out date needs to be set to the 
                    transaction's date.
            -	If the transaction type is R (meaning return):
                o	Use dateDiff to subtract the book's szCheckOutDt from the transaction's szTransDt
                o	If the difference is more than 14:
                    --	Determine the number of days late by subtracting 14 from that difference.  
                    --	Compute the late fee by multiplying the number of days late 
                        by the book's dLateFeePerDay.
                    --	If that late fee is greater than the book's dMaxLateFee, 
                        change it to dMaxLateFee.
                    --  Print the late fee.
                    --	Add the computed late fee to the customer's dFeeBalance
                o	Set the book's customer ID to "NONE".
                o	Set the book's check out date to "0000-00-00".
        CUSTOMER COMPLETE
            specifies the completion   of a customer.  Print the total fees for this customer.
        BOOK CHANGE szBookId dLateFeePerDay dMaxLateFee
            change the Late Fee Per Day and Max Late Fee to the specified values
        BOOK SHOW szBookId    
            requests a display of a particular book.  Show all of its information.
               
Results:
    Prints the Books prior to sorting
    Prints the Books after sorting.
    Processes the commands (see above) and shows any errors.
    Prints the resulting Books
Returns:
    0  normal
    -1 invalid command line syntax
    -2 show usage only
    -3 error during processing, see stderr for more information

Notes:
    p3 -?       will provide the usage information.  In some shells,
                you will have to type p3 -\?

**********************************************************************/

// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p3.h"
typedef int bool;//Just because true and false were used

/******************** getBooks **************************************
    int getBooks(Book bookM[], char * pszBookFileName)
Purpose:
    Retrieves the books from the file specified..
Parameters:
    O   Book bookM[]          an array which is used for returning the books.
    I   char *pszBookFileName name of the file containing the book data
Returns:
    A count of the number of read.
Notes:
    1. This opens the file based on the specified file name. 
    2. The data in the data file is in this format
    szBookId szCustomerId szCheckedOutDt dLateFeePerDay dMaxLateFee szTitle
    9s        6s             10s           lf            lf          40s (may contain spaces)
**************************************************************************/

int getBooks(Book bookM[], char * pszBookFileName)
{
    char szInputBuffer[100];		// input buffer for reading data
    int i = 0;                      // subscript in bookM
    int iScanfCnt;                  // returned by sscanf
    FILE *pFileBook;              // Stream Input for Books data. 

    /* open the Books stream data file */
    if (pszBookFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-b");

    pFileBook = fopen(pszBookFileName, "r");
    if (pFileBook == NULL)
        exitError(ERR_BOOK_FILENAME, pszBookFileName);

    /* get book information until EOF
    ** fgets returns null when EOF is reached.
    */

	while (fgets(szInputBuffer, 100, pFileBook) != NULL)
	{
		iScanfCnt=sscanf(szInputBuffer, "%9s %6s %10s %lf %lf %[^\n]\n"
			, bookM[i].szBookId
			, bookM[i].szCustomerId
			, bookM[i].szCheckedOutDt
			, &bookM[i].dLateFeePerDay
			, &bookM[i].dMaxLateFee
			, bookM[i].szTitle);//just scanning the book file and transfering the data to bookM
		
		if (iScanfCnt < 6)
			exitError(ERR_BOOK_DATA, szInputBuffer);
		i++;
	}

    fclose(pFileBook);
    return i;
}

/******************** sortBooks **************************************
    void sortBooks(Book bookM[], int iBookCnt)
Purpose:
Uses the buble sort program to sort the books in alphabetical and numerical order
Parameters:
Book bookM
int iBookCnt
Returns:
nothing
Notes:
    
**************************************************************************/
void sortBooks(Book bookM[], int iBookCnt)
{
	int i, j;
	bool bChange;//detects change, it is only supposed to be either true or false
	Book bookTemp;

	for (i = 0; i < (iBookCnt - 1); i++)
	{
		bChange = FALSE;
		for (j = 0; j < (iBookCnt - i - 1); j++)
		{
			if (strcmp(bookM[j].szBookId,bookM[j+1].szBookId)>0) //if the string szBookId of bookM[j] is more than the szBookId of bookM[j] then they switch posintions while making bChange true
			{
				bookTemp = bookM[j + 1];
				bookM[j + 1] = bookM[j];
				bookM[j] = bookTemp;
				bChange = TRUE;
			}

		}
		if (bChange==FALSE)
			break;
	}
}

/******************** printBooks **************************************
    void printBooks(char *pszHeading, Book bookM[], int iBookCnt)
Purpose:
    Prints each book in a table format
Parameters:
    I char *pszHeading    Heading to print before printing the table of books
    I Book bookM[]        Array of books
    I int iBookCnt        Number of elements in the bookM array.
Returns:
    n/a
Notes:
    
**************************************************************************/
void printBooks(char *pszHeading, Book bookM[], int iBookCnt)
{
    int i;
    printf("\n%s\n", pszHeading);

    // output column headings
    printf("   %-9s %-40s %-8s %-10s %-8s %-8s \n"
        , "Book Id", "Title", "Customer", "Ck Out Dt", "Late Fee", "Max Late");

    // output each book in a table format
    for (i = 0; i < iBookCnt; i++)
    {
        printf("   %-9s %-40s %-8s %-10s %8.2lf %8.2lf \n"
            , bookM[i].szBookId
            , bookM[i].szTitle
            , bookM[i].szCustomerId
            , bookM[i].szCheckedOutDt
            , bookM[i].dLateFeePerDay
            , bookM[i].dMaxLateFee
            );//Pretty sraight forward, just printing all the books and their information
    }
}


/********************processCustomerCommand *****************************
    void processCustomerCommand(Book bookM[], int iBookCnt
     , char *pszSubCommand, char *pszRemainingInput
     , Customer *pCustomer)
Purpose:
    Processes the subcommands associated with the CUSTOMER command:
        CUSTOMER BEGIN szBookId szCustomerId szCheckedOutDt dLateFeePerDay dMaxLateFee szTitle  
            specifies the beginning of customer request and includes all the identification information from program 2.
        CUSTOMER ADDRESS szStreetAddress,szCity,szStateCd,szZipCd
            specifies the address for a customer (separated by commas)
        CUSTOMER TRANS cTransType    szBookId   szTransDt
            specifies a single book transaction.  Steps:
            -	Print the Transaction Type, Book Id, and Transaction Date 
            -	Lookup the book ID using a binary search.  If not found, print a warning (but do not terminate your program) and return.
            -	If the transaction date is invalid, show a message stating "invalid date", but do not terminate.  Use the validateDate  function.
            -	If the transaction type is C (meaning checkout):
                o	If the book is already checked out, show a message stating "already checked out", but do not terminate.
                o	Otherwise, check out the book to this customer, setting the book's customer ID.  The book's checked out date needs to be set to the transaction's date.
            -	If the transaction type is R (meaning return):
                o	Use dateDiff to subtract the book's szCheckOutDt from the transaction's szTransDt
                o	If the difference is more than 14:
                    --	Determine the number of days late by subtracting 14 from that difference.  
                    --	Compute the late fee by multiplying the number of days late by the book's dLateFeePerDay.
                    --	If that late fee is greater than the book's dMaxLateFee, change it to dMaxLateFee.
                    --  Print the late fee.
                    --	Add the computed late fee to the customer's dFeeBalance
                o	Set the book's customer ID to "NONE".
                o	Set the book's check out date to "0000-00-00".
        CUSTOMER COMPLETE
            specifies the completion   of a customer.  Print the total fees for this customer.


Parameters:
    I/O Book bookM[]                  Array of books
    I   int   iBookCnt                Number of elements in bookM[]
    I   char  *pszSubCommand          Should be BEGIN, ADDRESS, REQUEST or COMPLETE
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
    I/O Customer *pCustomer           The BEGIN subcommand begins a new customer.  
Notes:

**************************************************************************/
void processCustomerCommand(Book bookM[], int iBookCnt
    , char *pszSubCommand, char *pszRemainingInput
    , Customer *pCustomer)
{
    int iScanfCnt;
    Transaction transaction;
    double dTransFee;
    // Determine what to do based on the subCommand
    if (strcmp(pszSubCommand, "BEGIN") == 0)
    {
        // get the Customer Identification Information
		iScanfCnt = sscanf(pszRemainingInput, "%6s %lf %40s %30[^\n]\n",
			pCustomer->szCustomerId,
			&pCustomer->dFeeBalance,
			pCustomer->szEmailAddr,
			pCustomer->szFullName);

        // Check for bad customer identification data
        if (iScanfCnt < 4)
            exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);

    }
    else if (strcmp(pszSubCommand, "COMPLETE") == 0)
    {
        // print the customer's total fees
		printf("\n\t\t\t\t\t\t\t\t\tTotal Fees: %.2lf\n\n", pCustomer->dFeeBalance);

    }
    else if (strcmp(pszSubCommand, "ADDRESS") == 0)
    {
        // get the postal address and print it
		iScanfCnt = sscanf(pszRemainingInput, "%30[^,] ,%20[^,] ,%2s ,%5s \n",
			pCustomer->szStreetAddress,
			pCustomer->szCity,
			pCustomer->szStateCd,
			pCustomer->szZipCd);

		printf("\n******************** Library Receipt ***********************\n");

		printf("%s %s %s (previously owed %0.2lf)\n",
			pCustomer->szCustomerId,
			pCustomer->szEmailAddr,
			pCustomer->szFullName,
			pCustomer->dFeeBalance);

		printf("%s \n%s %s %s\n",
			pCustomer->szStreetAddress,
			pCustomer->szCity,
			pCustomer->szStateCd,
			pCustomer->szZipCd);

		if (iScanfCnt < 4)//exit the code displaying and error if the iscanfCnt is less than 4
			exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);

        // print the column heading for the transactions
        printf("\n\t\t\t\t\t%-5s  %-9s  %-10s\n", "Trans", "Book", "Date");

    }
    else if (strcmp(pszSubCommand, "TRANS") == 0)
    {
		iScanfCnt = sscanf(pszRemainingInput, "%1c %9s %10s\n",
			&transaction.cTransType,
			transaction.szBookId,
			transaction.szTransDt);

		if (iScanfCnt < 3)
			exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);

		printf("\t\t\t\t\t%-5c %-9s %-10s ",
			transaction.cTransType,
			transaction.szBookId,
			transaction.szTransDt);
		dTransFee= processTransaction(bookM, iBookCnt, *pCustomer, transaction);
		if (dTransFee > 0)
			pCustomer->dFeeBalance += dTransFee;
        printf("\n");
    }
    else printf("   *** %s %s\n", ERR_CUSTOMER_SUB_COMMAND, pszSubCommand);
}

/********************processBookCommand *****************************
    void processBookCommand(Book bookM[], int iBookCnt
         , char *pszSubCommand, char *pszRemainingInput)
Purpose:
    Processes the subcommands associated with the BOOK command:
        BOOK CHANGE szBookId dLateFeePerDay dMaxLateFee
            change the Late Fee Per Day and Max Late Fee to the specified values
        BOOK SHOW szBookId    
            requests a display of a particular book.  Show all of its information.
                
Parameters:
    I/O Book bookM[]                  Array of books
    I   int   iBookCnt                Number of elements in bookM[]
    I   char  *pszSubCommand          Should be CHANGE or SHOW
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
Notes:

**************************************************************************/
void processBookCommand(Book bookM[], int iBookCnt
                             , char *pszSubCommand, char *pszRemainingInput)
{
    Book book;

    int iScanfCnt;
    int i;
    // Determine what to do based on the subCommand
	if (strcmp(pszSubCommand, "CHANGE") == 0)//changes the book info
	{
		iScanfCnt=sscanf(pszRemainingInput, "%9s %lf %lf\n",
			book.szBookId,
			&book.dLateFeePerDay,
			&book.dMaxLateFee);//scans the input
                i=searchBooks(bookM,iBookCnt,book.szBookId);
		if (iScanfCnt < 3)
			exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);
                if(i<0)
                    printf("*** Book not found\n");
                else
                {
                    bookM[i].dLateFeePerDay=book.dLateFeePerDay;
                    bookM[i].dMaxLateFee=book.dMaxLateFee;
                }
	}
	else if (strcmp(pszSubCommand, "SHOW") == 0)
	{
		iScanfCnt = sscanf(pszRemainingInput, "%9s\n", book.szBookId);//scans for the book id
		if (iScanfCnt < 1)
			exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);
		i = searchBooks(bookM, iBookCnt, book.szBookId);//searches for the book and returning the book location in bookM
		if (i >= 0)
		{
			printf("\n%-9s %-40s %-8s %-14s %-8s %-12s\n"
				, "Book Id"
				, "Book Title"
				, "Customer"
				, "Check Out Date"
				, "Late Fee"
                                , "Max Late Fee");//printing the table headers
			printf("%-9s %-40s %-8s %-14s %-8.2lf %-12.2lf \n\n"
				, bookM[i].szBookId
				, bookM[i].szTitle
				, bookM[i].szCustomerId
				, bookM[i].szCheckedOutDt
				, bookM[i].dLateFeePerDay
                                , bookM[i].dMaxLateFee);//Printing the book info
		}
		else 
                    printf("*** Book not found\n");
	}
	else printf("   *** %s %s\n", ERR_CUSTOMER_SUB_COMMAND, pszSubCommand);
}
/******************** searchBooks *****************************
    int searchBooks(Book bookM[], int iBookCnt, char *pszMatchBookId)
Purpose:
    Using a binary search, it finds the specified book in the booKM array.
Parameters:
    I   Book bookM[]                 Array of books
    I   int   iBookCnt               Number of elements in bookM[]
    I   char *pszMatchBookId         Book Id to find in the array
Returns:
    >= 0   subscript of where the match value was found
    -1     not found
Notes:

**************************************************************************/
int searchBooks(Book bookM[], int iBookCnt, char *pszMatchBookId)
{
	int iLB, iUB, iMID;
	iLB = 0;
	iUB = iBookCnt - 1;
	while (iLB <= iUB)
	{
		iMID = (iLB + iUB) / 2;
		if (strcmp(bookM[iMID].szBookId, pszMatchBookId) == 0)
			return iMID;
		if (strcmp(bookM[iMID].szBookId,pszMatchBookId) > 0)
			iUB = iMID - 1;
		else
			iLB = iMID + 1;
	}
	return -1;
}


/*** include your processTransaction code from program #2 ***/
double processTransaction(Book bookM[], int iBookCnt, Customer customer, Transaction transaction)
{
	int iBookVal = searchBooks(bookM, iBookCnt, transaction.szBookId);//finds the book Id
	int iDateDifference;
	double dLateFee;

	if (iBookVal == -1)//Verifies if the book exists
	{
		printf("\tERROR: Book not found");
		return -1;
	}
	else if (transaction.cTransType == 'R')//Return Transaction
	{
		if (strcmp(bookM[iBookVal].szCustomerId, customer.szCustomerId) != 0)
		{
			printf("\tERROR: Customer does not own book that is being returned");
			return -2;
		}//Not really required, just checking if someone stole a book or something

		iDateDifference = dateDiff(transaction.szTransDt, bookM[iBookVal].szCheckedOutDt);
		dLateFee = bookM[iBookVal].dLateFeePerDay*(iDateDifference - 14);
		//Resetting the book info saying that the book is no longer checked out
		strcpy(bookM[iBookVal].szCustomerId, "NONE");
		strcpy(bookM[iBookVal].szCheckedOutDt, "0000-00-00");
		//Determining the fees that are to be charged on the customer
		if (iDateDifference <= 14)
			return 0;
		else if (dLateFee >= bookM[iBookVal].dMaxLateFee)
			dLateFee = bookM[iBookVal].dMaxLateFee;

		printf("\tLate Fee: %.2lf", dLateFee);
		return dLateFee;
	}
	else if (transaction.cTransType == 'C')//Check Out Transaction
	{
		if (strcmp(bookM[iBookVal].szCustomerId, "NONE") != 0)//check if the book is checked out
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
