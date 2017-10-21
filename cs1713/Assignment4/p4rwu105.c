/**********************************************************************
p4rwu105.c by Max Crookshanks
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
#include "cs1713p4.h"
typedef int bool;//Just because true and false were used

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
void printBooks(char *pszHeading, Node *pHead)
{
    int i;
    printf("\n%s\n", pszHeading);
	Node *p;
    // output column headings
    printf("   %-9s %-40s %-8s %-10s %-8s %-8s \n"
        , "Book Id", "Title", "Customer", "Ck Out Dt", "Late Fee", "Max Late");

    // output each book in a table format
	for (p = pHead; p != NULL ; p=p->pNext)
    {
        printf("   %-9s %-40s %-8s %-10s %8.2lf %8.2lf \n"
            , p->book.szBookId
            , p->book.szTitle
            , p->book.szCustomerId
            , p->book.szCheckedOutDt
            , p->book.dLateFeePerDay
            , p->book.dMaxLateFee);//Pretty sraight forward, just printing all the books and their information
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
void processCustomerCommand(Node **ppHead
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
		dTransFee= processTransaction(ppHead, *pCustomer, transaction);
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
void processBookCommand(Node **ppHead
	, char *pszSubCommand, char *pszRemainingInput)
{
    Book book;
	Node *p;
	Node *pPrecedes;
    int iScanfCnt;
    int i;
    // Determine what to do based on the subCommand
	if (strcmp(pszSubCommand, "CHANGE") == 0)//changes the book info
	{
		iScanfCnt=sscanf(pszRemainingInput, "%9s %lf %lf\n",
			book.szBookId,
			&book.dLateFeePerDay,
			&book.dMaxLateFee);//scans the input
		p = searchLL(*ppHead, book.szBookId, &pPrecedes);
		if (iScanfCnt < 3)
			exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);
                if(p == NULL)
                    printf("*** Book not found\n");
                else
                {
                    (*ppHead)->book.dLateFeePerDay=book.dLateFeePerDay;
                    (*ppHead)->book.dMaxLateFee=book.dMaxLateFee;
                }
	}
	else if (strcmp(pszSubCommand, "SHOW") == 0)
	{
		iScanfCnt = sscanf(pszRemainingInput, "%9s\n", book.szBookId);//scans for the book id
		if (iScanfCnt < 1)
			exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);
		p = searchLL(*ppHead, book.szBookId, &pPrecedes);//searches for the book and returning the book location in bookM
		if (p != NULL)
		{
			printf("\n%-9s %-40s %-8s %-14s %-8s %-12s\n"
				, "Book Id"
				, "Book Title"
				, "Customer"
				, "Check Out Date"
				, "Late Fee"
                , "Max Late Fee");//printing the table headers
			printf("%-9s %-40s %-8s %-14s %-8.2lf %-12.2lf \n\n"
				, (*ppHead)->book.szBookId
				, (*ppHead)->book.szTitle
				, (*ppHead)->book.szCustomerId
				, (*ppHead)->book.szCheckedOutDt
				, (*ppHead)->book.dLateFeePerDay
                , (*ppHead)->book.dMaxLateFee);//Printing the book info
		}
		else 
        printf("*** Book not found\n");
	}
	else if (strcmp(pszSubCommand, "NEW") == 0)
	{
		iScanfCnt = sscanf(pszRemainingInput, "%9s %6s %10s %lf %lf %[^\n]\n"
			, book.szBookId
			, book.szCustomerId
			, book.szCheckedOutDt
			, &book.dLateFeePerDay
			, &book.dMaxLateFee
			, book.szTitle);//scans for the NEW command data

		if (iScanfCnt < 6)
			exitError("Command Data Messed Up", pszRemainingInput);

		if(searchLL(*ppHead,book.szBookId,&pPrecedes)==NULL)//Checking if the book exists or not
                    insertLL(ppHead, book);//Inserting book into the LL
                else
                    printf("***Book Already Exists\n");//Prints this if the book is not found
	}
	else printf("   *** %s %s\n", ERR_CUSTOMER_SUB_COMMAND, pszSubCommand);
}


/*** include your processTransaction code from program #2 ***/
double processTransaction(Node **ppHead, Customer customer, Transaction transaction)
{
	Node *p;
	Node *pPrecedes;
	p = searchLL(*ppHead, transaction.szBookId, &pPrecedes);//finds the book Id
	int iDateDifference;
	double dLateFee;

	if (p == NULL)//Verifies if the book exists
	{
		printf("\tERROR: Book not found");
		return -1;
	}
	else if (transaction.cTransType == 'R')//Return Transaction
	{
		if (strcmp(p->book.szCustomerId, customer.szCustomerId) != 0)
		{
			printf("\tERROR: Customer does not own book that is being returned");
			return -2;
		}//Not really required, just checking if someone stole a book or something

		iDateDifference = dateDiff(transaction.szTransDt, p->book.szCheckedOutDt);
		dLateFee = p->book.dLateFeePerDay*(iDateDifference - 14);
		//Resetting the book info saying that the book is no longer checked out
		strcpy(p->book.szCustomerId, "NONE");
		strcpy(p->book.szCheckedOutDt, "0000-00-00");
		//Determining the fees that are to be charged on the customer
		if (iDateDifference <= 14)
			return 0;
		else if (dLateFee >= p->book.dMaxLateFee)
			dLateFee = p->book.dMaxLateFee;

		printf("\tLate Fee: %.2lf", dLateFee);
		return dLateFee;
	}
	else if (transaction.cTransType == 'C')//Check Out Transaction
	{
		if (strcmp(p->book.szCustomerId, "NONE") != 0)//check if the book is checked out
			printf("\tERROR: Book already checked out by another customer");
		else
		{
			strcpy(p->book.szCustomerId, customer.szCustomerId);
			strcpy(p->book.szCheckedOutDt, transaction.szTransDt);
			return 0;
		}
		return -1;//returns -1 if something went wrong in the checking out process
	}
	else
		exitError("Invalid Transaction Type", "");//exit if there is no transaction type
}

Node *insertLL(Node **ppHead, Book book)
{
	Node *pNew;
	Node *pPrecedes;
	Node *pFind;
	// see if it already exists
	pFind = searchLL(*ppHead, book.szBookId, &pPrecedes);
	// Does the value already exist
	if (pFind != NULL)
		return pFind;
        pNew=allocateNode(book);
	// Doesn't already exist.  Allocate a node and insert it
	if (pPrecedes == NULL)
	{   // insert at head
		pNew->pNext = *ppHead;
		*ppHead = pNew;
	}
	else
	{   // insert after a node
		pNew->pNext = pPrecedes->pNext;
		pPrecedes->pNext = pNew;
	}
	return pNew;
}

Node *searchLL(Node *pHead, char szMatchBookId[], Node **ppPrecedes)
{
	Node *p;
	*ppPrecedes = NULL;
	for (p = pHead; p != NULL; p = p->pNext)//looks through the linked list for the string
	{
		if (strcmp(szMatchBookId,p->book.szBookId)==0)//tests it
		return p;
		if (strcmp(szMatchBookId,p->book.szBookId)<0)//returns null if it is not there
			return NULL;
		*ppPrecedes = p;
	}
	return NULL;
}
