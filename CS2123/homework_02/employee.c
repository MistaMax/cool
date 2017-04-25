/*
 * File: employee.c
 * ----------------
 * This program tests the functions defined for records of type
 * employeeRecordT and employeeT.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header02.h"
#include "bookstypes.h"

#define MAX_NAME_LENGTH 100
#define MAX_TITLE_LENGTH 50
#define MAX_SSN_LENGTH 12
/* Main program */

int main()
{
    payrollT payroll;
    payroll = (GetPayroll());
    ListEmployees(payroll);
    PrintPayroll(payroll);
    return 0;
}

static void ListEmployees(payrollT payroll)
{
    int i;

    for (i = 0; i < payroll->nEmployees; i++) {
        printf("%s (%s)\n", payroll->employees[i]->name, payroll->employees[i]->title);
    }
}

void flushInputBuffer()//flushes the input buffer from scanf, this was causing alot of problems before i made this
{
    char c;
    do
    {
        c=getchar();
    }while(c != '\n' && c != EOF);
}

void inputString(char **s,int length)//efficiently takes the input string with spaces
{
    fgets(*(s),length,stdin);
    if(strlen(*(s))>0 && (*(s))[strlen(*(s))-1]=='\n')
        (*(s))[strlen(*(s))-1]='\0';
}

void PrintPayroll(payrollT payroll)//prints the payroll
{
    int i;
    double adjustedIncome, taxRate;
    taxRate=0.25;
    printf("\n\n%-70s %-8s   %-5s   %-5s\n", "Name", "Gross", "Tax", "Net");//prints the header
    for(i=0;i<payroll->nEmployees;i++)
    {
        adjustedIncome = payroll->employees[i]->salary - payroll->employees[i]->withholding;
        if(adjustedIncome<0)adjustedIncome=0;
        printf("%-70s %-8.2f - %-5.2f = %-5.2f\n", payroll->employees[i]->name, payroll->employees[i]->salary, taxRate*adjustedIncome, payroll->employees[i]->salary - taxRate*adjustedIncome);
    }
    printf("\n");
}

payrollT GetPayroll()//this is the get payroll function, it takes the input from the user to generate an employee payroll
{
    int i, nEmployees;
    payrollT payroll;
    payroll = New(payrollT);
    printf("How many employees: ");
    scanf("%i", &nEmployees);
    printf("\n");
    payroll->employees = NewArray(nEmployees, employeeT);
    payroll->nEmployees = nEmployees;
    for(i=0;i<nEmployees;i++)
    {
        flushInputBuffer();
        payroll->employees[i] = New(employeeT);
        payroll->employees[i]->name = NewArray(MAX_NAME_LENGTH,char);
        payroll->employees[i]->title = NewArray(MAX_TITLE_LENGTH,char);
        payroll->employees[i]->ssnum = NewArray(MAX_SSN_LENGTH,char);
        printf("Employee #%i:\n",i+1);
        printf("Name: ");
        inputString(&payroll->employees[i]->name,MAX_NAME_LENGTH);
        printf("Title: ");
        inputString(&payroll->employees[i]->title,MAX_TITLE_LENGTH);
        printf("SSNum: ");
        inputString(&payroll->employees[i]->ssnum,MAX_SSN_LENGTH);
        printf("Salary: ");
        scanf("%lf", &payroll->employees[i]->salary);
        printf("Withholding exemptions: ");
        scanf("%i", &payroll->employees[i]->withholding);
        printf("\n");
    }
    return (payroll);
}
