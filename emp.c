#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_name_size 100

struct employee
{
    char name[100];
    int id;
    struct date_of_birth
    {
        int day;
        int month;
        int year;
    } dob;
    float salary;
};
long eSize;
FILE *emp;
// EMPLOYEE.BIN
// temprory************
FILE *TEMP;
// TEMP.BIN
void exitEmployee(FILE *);
void addEmployee(FILE *);
void updateEmployee(FILE *);
void deleteEmployee(FILE *);
void listEmployee(FILE *);
void searchEmployee(FILE *);
char getArgument();
void hold_clear_Screen();
char searchoption();
int searchByName(FILE *);
int searchById(FILE *);
void printEmploy(FILE *);
int main()
{
    struct employee e;
    eSize = sizeof(e);
    emp = fopen("employee.bin", "rb+");
    if (emp == NULL)
    {
        emp = fopen("employee.bin", "wb+");
        if (emp == NULL)
        {
            printf("file opening error!\n");
            return 0;
        }
    }
    while (1)
    {
        // system("cls");
        char choice = getArgument();
        switch (choice - '0')
        {
        case 0:
            exitEmployee(emp);
            break;
        case 1:
            addEmployee(emp);
            break;
        case 2:
            updateEmployee(emp);
            break;
        case 3:
            deleteEmployee(emp);
            break;
        case 4:
            searchEmployee(emp);
            break;
        case 5:
            listEmployee(emp);
            break;
        default:
            printf("not a valid option\n");
        }
    }
}
char getArgument()
{
    printf("\n\n");
    printf("\tChoose 0 for save and exit\n");
    printf("\tChoose 1 for Add an employee:\n");
    printf("\tChoose 2 for update an employee:\n");
    printf("\tChoose 3 for delete an employee:\n");
    printf("\tChoose 4 for search an employee:\n");
    printf("\tChoose 5 for list all employee:\n");
    printf("\n \t choose what you want to do between o to 5.\n");
    char choice;
    scanf(" %c", &choice);
    getchar(); // Add a space before %c to consume any leftover newline
    if (choice >= '0' && choice <= '5')
    {
        return choice;
    }
    system("cls");
    printf("\n\n\tEnter a valid option!\n");
    hold_clear_Screen();
    return getArgument(); // Return the recursive call
}

void hold_clear_Screen()
{
    printf("\n\nPress any key to continue\n");
    getchar();
    system("cls");
    // getchar();
}
void exitEmployee(FILE *emp)
{
    system("cls");
    printf("Are you confirm to exit \t (yes or No)\n");
    char confirm;
    scanf("%c", &confirm);
    getchar();
    if (confirm == 'y' || confirm == 'Y')
    {
        fclose(emp);
        system("cls");
        exit(1);
    }
    return;
}

void addEmployee(FILE *emp)
{
    system("cls");
    struct employee e;
    eSize = sizeof(e);
    printf("Enter employee name:\n");
    fgets(e.name, max_name_size, stdin);
    e.name[strcspn(e.name, "\n")] = '\0'; // Remove newline from fgets
    printf("Enter id:\n");
    scanf("%d", &e.id);
    printf("Enter date of birth (dd-mm-yyyy):\n");
    scanf("%d%*c%d%*c%d", &e.dob.day, &e.dob.month, &e.dob.year);
    printf("Enter salary of employee:\n");
    scanf("%f", &e.salary); // Use %f instead of %.2f for input

    fseek(emp, 0, SEEK_END); // Seek to the end of the file
    fwrite(&e, eSize, 1, emp);
    fflush(emp);
    system("cls");
    printf("Record added successfully.\n");
    hold_clear_Screen();
}
void updateEmployee(FILE *emp)
{
    system("cls");
    char choice;
    struct employee e;
    eSize = sizeof(e);
    printf("\t\t\t********UPDATE SECTION*******");

    printf("\n\tYou search by Name and employ id\n");
    choice = searchoption();
    switch (choice - '0')
    {
    case 0:
        return;
    case 1:
        if (searchByName(emp) == 0)
            return;
        break;
    case 2:

        if (searchById(emp) == 0)
            return;
        break;
    default:
        printf("\tYou choose wrong option.\n");
        hold_clear_Screen();
        return;
    }

    printf("Enter employee name:\n");
    fgets(e.name, max_name_size, stdin);
    e.name[strcspn(e.name, "\n")] = '\0'; // Remove newline from fgets
    printf("Enter id:\n");
    scanf("%d", &e.id);
    printf("Enter date of birth (dd-mm-yyyy):\n");
    scanf("%d%*c%d%*c%d", &e.dob.day, &e.dob.month, &e.dob.year);
    printf("Enter salary of employee:\n");
    scanf("%f", &e.salary); // Use %f instead of %.2f for input

    fseek(emp, -eSize, SEEK_CUR); // Seek to the end of the file
    fwrite(&e, eSize, 1, emp);
    fflush(emp);
    system("cls");
    printf("Record update successfully.\n");
    getchar();
    hold_clear_Screen();
    return;
}
void deleteEmployee(FILE *emp)
{
    printf("Task not complete for work\n");
    system("cls");
    char choice;
    struct employee e;
    eSize = sizeof(e);
    printf("\t\t\t********DELETE SECTION*******");
    printf("\n\tYou search by Name and employ id\n");
    choice = searchoption();
    switch (choice - '0')
    {
    case 0:
        return;
    case 1:
        if (searchByName(emp) == 0)
            return;
        break;
    case 2:

        if (searchById(emp) == 0)
            return;
        break;
    default:
        printf("\tYou choose wrong option.\n");
        hold_clear_Screen();
        return;
    }
    fseek(emp,-eSize,SEEK_CUR);
    fread(&e , eSize , 1 , emp);
    struct employee temp=e;
    TEMP=fopen("temprory.bin","wb+");
    if(TEMP==NULL){
        printf("Error opening file");
        return;
    }
    rewind(emp);
    while(fread(&e,eSize,1,emp) !=NULL)
    {
        if(strcmp(e.name,temp.name)==0)
        {
            printf("Record deleted\n");
            continue;
        }
        fwrite(&e, eSize, 1, TEMP);
    }
    fclose(emp);
    fclose(TEMP);
    remove("employee.bin");
    rename("temprory.bin","employee.bin");

    emp = fopen("employee.bin","rb+");
    if(emp=NULL){
        printf("Error reporting employee file.\n");
        return;
    }
    printf("Record Delete successfully.\n");
    hold_clear_Screen();
}
void listEmployee(FILE *emp)
{
    system("cls");
    struct employee e;
    eSize = sizeof(e);
    rewind(emp);
    printf("\n\n\t\t*******************EMPLOYEE RECORDS***********************\n");
    while (fread(&e, eSize, 1, emp) == 1)
    {
        printf("\tName :%s\tID :\t%d\tDOB\t%d-%d-%d\t salary :\t%.2f\n", e.name, e.id, e.dob.day, e.dob.month, e.dob.year, e.salary);
    }
    printf("\n\t\t**********************END RECORDS**************************\n");
    hold_clear_Screen();
    return;
}
void searchEmployee(FILE *emp)
{
    // system("cls");
    struct employee e;
    eSize = sizeof(e);
    char choice;
    // printf("\t\t\t*******SEARCH SECTION*******\n");
    system("cls");
    printf("\n\tYou search by Name and employ id\n");
    choice = searchoption();
    switch (choice - '0')
    {
    case 0:
        return;
    case 1:
        searchByName(emp);
        return;
    case 2:
        printf("this part not ready....");
        searchById(emp);
        return;
    default:
        printf("\tYou choose wrong option.\n");
        hold_clear_Screen();
        return;
    }
}

char searchoption()
{
    printf("\n\n");
    printf("\tChoose 0 for main manu\n");
    printf("\tChoose 1 for search by name:\n");
    printf("\tChoose 2 for search by I'd:\n");
    char choice;
    scanf(" %c", &choice);
    getchar(); 
    if (choice >= '0' && choice <= '2')
    {
        return choice;
    }
    system("cls");
    printf("\n\n\tEnter a valid option!\n");
    hold_clear_Screen();
    return searchoption();
}
int searchByName(FILE *emp)
{
    system("cls");
    struct employee e;
    eSize = sizeof(e);
    rewind(emp);
    char nameSearch[max_name_size];
    printf("\n\tEnter Employee name:\n");
    if (fgets(nameSearch, max_name_size, stdin) == NULL)
    {
        perror("Error reading input"); // Handle potential errors
        hold_clear_Screen();
        return 0;
    }
    nameSearch[strcspn(nameSearch, "\n")] = '\0';

    while (fread(&e, eSize, 1, emp) == 1)
    {
        if (strcmp(nameSearch, e.name) == 0)
        {
            printf("\n\n\t\t*******************EMPLOYEE RECORDS***********************\n");
            printf("\tName :%s\tID :\t%d\tDOB\t%d-%d-%d\t salary :\t%.2f\n", e.name, e.id, e.dob.day, e.dob.month, e.dob.year, e.salary);
            printf("\n\t\t**********************END RECORDS**************************\n");
            hold_clear_Screen();
            return 1;
        }
    }
    printf("Record not found!");
    hold_clear_Screen();
    return 0;
}
int searchById(FILE *emp)
{
    struct employee e;
    eSize = sizeof(e);
    rewind(emp);
    system("cls");
    int searchId;
    printf("\n\tEnter Employee ID:\n");
    if (scanf("%d", &searchId) != 1)
    { // Read Employee ID
        printf("Invalid input. Please enter a valid integer ID.\n");
        while (getchar() != '\n');
        hold_clear_Screen();
        return 0;
    }
    while (getchar() != '\n');

    while (fread(&e, eSize, 1, emp) == 1)
    { // Read each employee record
        if (searchId == e.id)
        { // Match found
            system("cls");
            printf("\n\n\t\t*******************EMPLOYEE RECORDS***********************\n");
            printf("\tName: %s\tID: %d\tDOB: %d-%d-%d\tSalary: %.2f\n",
                   e.name, e.id, e.dob.day, e.dob.month, e.dob.year, e.salary);
            printf("\n\t\t**********************END RECORDS**************************\n");
            hold_clear_Screen();
            return 1;
        }
    }
    printf("\nRecord not found!\n");
    hold_clear_Screen();
    return 0;
}
