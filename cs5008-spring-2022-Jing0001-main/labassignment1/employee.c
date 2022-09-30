/*C Program to read and print the employee details using structure and dynamic memory allocation*/
#include <stdio.h>
#include <stdlib.h>
/*structure to hold the details of an employee*/
typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;
/* Read the employee details using scanf*/
void readData(int n, employee_t* s)
{
    for (int count = 0; count < n;count++) {
        printf("\n");
        printf("Enter the employeeID, Name, designation and Department of Employee %d:\n", count + 1);
        scanf("%d", &s[count].empId);
        scanf("%20s", s[count].Name);
        scanf("%30s", s[count].Designation);
        scanf("%20s", s[count].Dept);
    }
    printf("\n");
}
/* Function to print the employee details*/
void display(int n, employee_t* s)
{
    for (int count = 0; count < n; count++) {
        printf("The details of Employee %d:\n", count + 1);
        printf("empId: %d\n", s[count].empId);
        printf("Name: %s\n", s[count].Name);
        printf("designation: %s\n", s[count].Designation);
        printf("Dept: %s\n", s[count].Dept);
        printf("\n");
    }
}

/*----------Main Program--------*/
int main()

{
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);
    employee_t* s = (employee_t*)malloc(n*sizeof(employee_t));
    readData(n, s);
    display(n, s);
    free(s);
    return 0;
}
