/*
 * Type: string
 * ------------
 * The type string is identical to the type char *, which is
 * traditionally used in C programs.  The main point of defining a
 * new type is to improve program readability.   At the abstraction
 * levels at which the type string is used, it is usually not
 * important to take the string apart into its component characters.
 * Declaring it as a string emphasizes this atomicity.
 */

typedef char *string;



/*
 * Constants
 * ---------
 * MaxEmployees -- Maximum number of employees
 */

#define MaxEmployees 100

/*
 * Type: employeeRecordT
 * ---------------------
 * This structure defines a type for an employee record.
 */

typedef struct {
    string name;
    string title;
    string ssnum;
    double salary;
    int withholding;
} employeeRecordT;

/*
 * Type: employeeT
 * ---------------
 * This type definition introduces an employeeT as a
 * pointer to the same record type as before.
 */

typedef struct {
    string name;
    string title;
    string ssnum;
    double salary;
    int withholding;
} *employeeT;

/*
 * Type: payrollT
 * --------------
 * This type represents an entire collection of employees.  The
 * type definition uses a dynamic array of employeeT values to
 * ensure that there is no maximum bound imposed by the type.
 * The cost of this design is that the programmer must explicitly
 * allocate the storage for the array using NewArray.
 */

typedef struct {
    int nEmployees;
    employeeT *employees;
} *payrollT;

/*
 * Global variables
 * ----------------
 * staff       -- Array of employees
 * nEmployees  -- Number of employees
 * manager     -- Used to produce a figure for the code
 */

static employeeRecordT staff[MaxEmployees];
static int nEmployees;

static employeeRecordT manager = {
    "Ebenezer Scrooge", "Partner", "271-82-8183", 250.00, 1
};

/* Private function declarations */

void flushInputBuffer();
void inputString(char **s, int length);
void PrintPayroll(payrollT payroll);
payrollT GetPayroll();
static void InitEmployeeTable(void);
static payrollT CreatePayroll(employeeRecordT staff[], int nEmployees);
static void ListEmployees(payrollT payroll);
static double AverageSalary(payrollT payroll);
