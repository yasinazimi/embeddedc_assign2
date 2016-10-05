/***************************************************************************
48430 Embedded C - Assignment 2
Name: Yasin Azimi
Student ID: 11733490
Date of submission: 22/05/2016
***************************************************************************/


/**************************************************************************
List of header files and preprocessing directives
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_CLASS_SIZE 5
#define MAX_NAME_SIZE 11
#define DB_FILE_NAME "database"
#define ASCII_CHAR_PERIOD 46
#define ASCII_CHAR_ZERO 48
#define ASCII_CHAR_NINE 57


/**************************************************************************
Structs
***************************************************************************/
struct date {	/*struct date is declared, where 'date' is the name of struct*/
	int day;
	int month;
	int year;
};

struct student {				/*struct student is declared, where 'student' is the name of struct*/
	char name[MAX_NAME_SIZE];
	struct date birthday;
	float gpa;
};

typedef struct student studentcount;	/*typedef assigns alternative variable 'studentcount' to the existing struct 'student'*/


/**************************************************************************
Function prototypes
***************************************************************************/
int flush_stdin();
void printmenu(void);
int checkvalue(char string[]);
void addstudent(studentcount count[], int* studentsize);
void deletestudent(studentcount count[], int* studentsize);
void showstudentlist(studentcount count[], int* studentsize);
void savestudentlist(studentcount count[], int* studentsize);
void readstudentlist(studentcount count[], int* studentsize);


/**************************************************************************
Main
***************************************************************************/
int main(void) {
	studentcount studentlist[MAX_CLASS_SIZE];	/*Initialising array studentlist[MAX_CLASS_SIZE], with structure type student. This is where the list of students are stored*/
	int studentsize = 0;	/*The keyword int declares 'studentsize' to be an integer. This variable name will be used as an integer pointer*/
	char option;	/*The keyword char declares 'option' to be a character*/
	
	do {
		printmenu();	/*Calling the function printmenu*/
		printf("Enter your choice>");	/*Prompt user to select an option from the menu*/
		scanf("%c", &option);	/*Receives an input value from the user and stores that value in the 'option' character*/
		switch (option)
		{
			case '1':
					if (studentsize < MAX_CLASS_SIZE) {		/*Checks if the number of students in the class is less than 5. If they are, than add the student to the list in 'studentsize' stored as an array of struct type 'student'*/
						addstudent(studentlist, &studentsize);
					}
					else {	/*If the number of students in the class is greater than or equal to 5, prints out error message*/
						printf("Class is full\n"); }
					break;
					
			case '2':
					if (studentsize > 0) {		/*Checks if the number of students in the class is greater than 0. If they are, than delete the most recent student added to the list in 'studentsize' stored as an array of struct type 'student'*/
						deletestudent(studentlist, &studentsize);
					}
					else {	/*If there are no students in the list, prints out error message*/
						printf("Class is empty\n"); }
					break;
					
			case '3':
					if (studentsize <= 0) {		/*Checks if there are no students in the list. If there is none, prints out error message*/
						printf("Class is empty\n");
					}
					else {	/*If there are students in the list, display the students in the terminal that are in the list in 'studentsize' stored as an array of struct type 'student'*/
						showstudentlist(studentlist, &studentsize); }
					break;

			case '4':
					savestudentlist(studentlist, &studentsize);		/*Makes a backup copy of the current studentlist to the database file*/
					break;
					
			case '5':
					if (studentsize <= 0) {		/*Checks if there are no students in the list 'studentsize' (an instance where no backup copy of student list is made to a database file). If there are none prints out error message*/
						printf("Read error\n");
					}
					else {	/*If there is an instance of a database and a backup copy of students list exists in that database file, than read all the students that are in the database file in 'studentsize' stored as an array of struct type 'student'*/
						readstudentlist(studentlist, &studentsize); }
					break;
					
			case '6':
					exit(EXIT_SUCCESS);		/*Exits the program*/
					break;
					
			default:
					printf("Invalid choice.\n");	/*Prints out error message if any other value is entered outside of the above cases*/
					break;
		}
	} while (option != '6' && flush_stdin());		/*The above switch statement is executed if the input value is not 6 and clears the buffer*/
    return 1; 
}


/**************************************************************************
Menu
***************************************************************************/
void printmenu(void){
    printf("\n\n"
                   "1. add student\n"
                   "2. delete last student\n"
                   "3. display student list\n"
                   "4. save the student list to the database\n"
                   "5. read the student list from the database\n"
                   "6. exit the program\n");
}


/**************************************************************************
Validate integer input
***************************************************************************/
int flush_stdin() {
	while (getchar() != '\n');	/*Clears the input stream*/
	return 1;
}


/**************************************************************************
Validate input characters with ASCII
***************************************************************************/
int checkvalue(char string[]) {
    int value;		/*Initialised as an index for this function*/
    for (value = 0; string[value] != '\0'; value++) {	/*Loops until a null character is received from an input stream. It then checks the value is within the ASCII range declared below*/
        if (((int)string[value] < ASCII_CHAR_ZERO || (int)string[value] > ASCII_CHAR_NINE) && (int)string[value] != ASCII_CHAR_PERIOD){
            return 0;
        }
    }
    return 1;
}


/**************************************************************************
Add student
***************************************************************************/
void addstudent(studentcount count[], int* studentsize) {
	studentcount addnewstudent;		/*Declaring another instance of variable 'addnewstudent' to the struct type 'student'*/
	int validateinput;		/*Validates the return value from the input stream*/
	char tempvalue[10];		/*Temporary return value for scanf*/
	printf("Enter name>");
	scanf(" %[^\n]", addnewstudent.name);	/*Intakes the first 10 characters from the input stream and stores this for the student name*/
	flush_stdin(); 	/*Clear the buffer*/
	
	do {
		if (validateinput == 0)
		printf("Invalid day. ");	/*Print error message*/
		printf("Enter birthday: day>");
		scanf("%2[^\n]", tempvalue);	/*Only intake the first 2 integer values*/
		validateinput = checkvalue(tempvalue);	/*Check for a correct input from the input stream*/
		if (atoi(tempvalue) < 1 || atoi(tempvalue) > 31)	/*Check for correct input within the range*/
		validateinput = 0;
		else addnewstudent.birthday.day = atoi(tempvalue);	/*If the input entered is valid, assign it to the input stream*/
		flush_stdin();	/*Clears the input stream*/
	} while (validateinput != 1);	/*Continue the iteration until a valid input is received*/
	
	do {
		if (validateinput == 0)
		printf("Invalid month. ");	/*Print error message*/
		printf("Enter birthday: month>");
		scanf("%2[^\n]", tempvalue);	/*Only intake the first 2 integer values*/
		validateinput = checkvalue(tempvalue);	/*Check for a correct input from the input stream*/
		if (atoi(tempvalue) < 1 || atoi(tempvalue) > 12)	/*Check for correct input within the range*/
		validateinput = 0; 
		else addnewstudent.birthday.month = atoi(tempvalue);	/*If the input entered is valid, assign it to the input stream*/
		flush_stdin();	/*Clears the input stream*/
	} while (validateinput != 1);	/*Continue the iteration until a valid input is received*/
	
	do {
		if (validateinput == 0)
		printf("Invalid year. ");	/*Print error message*/
		printf("Enter birthday: year>");
		scanf("%4[^\n]", tempvalue);	/*Only intake the first 4 integer values*/
		validateinput = checkvalue(tempvalue);	/*Check for a correct input from the input stream*/
		if (atoi(tempvalue) < 1800 || atoi(tempvalue) > 2016)	/*Check for correct input within the range*/
		validateinput = 0;
		else addnewstudent.birthday.year = atoi(tempvalue);	/*If the input entered is valid, assign it to the input stream*/
		flush_stdin();	/*Clears the input stream*/
	} while (validateinput != 1);	/*Continue the iteration until a valid input is received*/
	
	do {
		if (validateinput == 0)
		printf("Invalid GPA. ");	/*Print error message*/
		printf("Enter GPA>");
		scanf("%6[^\n]", tempvalue);	/*Only intake the first 6 integer values*/
		validateinput = checkvalue(tempvalue);	/*Check for a correct input from the input stream*/
		if (atof(tempvalue) < 0.0 || atof(tempvalue) > 4.0)	/*Check for correct input within the range*/
		validateinput = 0;
		else addnewstudent.gpa = atof(tempvalue);	/*If the input entered is valid, assign it to the input stream*/
	} while (validateinput != 1);	/*Continue the iteration until a valid input is received*/
	
	count[*studentsize] = addnewstudent;	/*The data stored inside 'addnewstudent' is passed to the array of structs through pointer*/
	*studentsize += 1;	/*Increment the value stored inside the 'studentsize'*/
}


/**************************************************************************
Delete last student
***************************************************************************/
void deletestudent(studentcount count[], int* studentsize) {
	if (*studentsize > 0) {		/*Checks if the value inside the 'studentsize' pointer is greater than zero*/
		(*studentsize)--;	/*If it is, than decrements the most recent element added in the array*/
	}
}


/**************************************************************************
Display student list
***************************************************************************/
void showstudentlist(studentcount count[], int* studentsize) {
	int element;	/*The keyword int declares 'element' to be an integer*/
	printf("Name       Birthday   GPA\n");
	printf("---------- ---------- ------\n");
	for (element = 0; element < *studentsize; element++) {		/*Assigns an integer value of 0 to the variable 'element' with a condition to check whether the 'element' is less than the value stored inside the 'studentsize' pointer. This will then proceed to print out to the terminal the following commands and hence, continues the iterations 'element++'. The following lines are executed and prints out each student to the terminal in the format specified*/
		printf("%-11.10s", count[element].name);
		printf("%02d-%02d-%-5.4d", count[element].birthday.day, count[element].birthday.month, count[element].birthday.year);
		printf("%.4f\n", count[element].gpa);
	}
}


/**************************************************************************
Save the student list to the database
***************************************************************************/
void savestudentlist(studentcount count[], int* studentsize) {
	int record;		/*The keyword int declares 'record' to be an integer*/
	FILE *writefile;	/*Declares the file pointer to 'writefile'*/
	writefile = fopen(DB_FILE_NAME, "w");	/*Creates an empty file for writing and if a file with the same name already exists, its content is flushed and the file is considered as a new empty file*/
	for (record = 0; record < *studentsize; record++) {		/*Assigns an integer value of 0 to the variable 'record' with a condition to check whether the 'record' is less than the value stored inside the 'studentsize' pointer. This will then proceed to read formatted input from a stream that is displayed previously in the terminal and hence, continues the iterations 'record++'. The following lines are executed and prints out each student to the file with the specified format as displaying on the terminal*/
		fprintf(writefile, "%11s ", count[record].name);
		fprintf(writefile, "%02d-%02d-%d ", count[record].birthday.day, count[record].birthday.month, count[record].birthday.year);
		fprintf(writefile, "%f\n", count[record].gpa);
	}
	fclose(writefile);	/*Closes the opening file stream 'writefile'.*/
}


/**************************************************************************
Read the student list from the database
***************************************************************************/
void readstudentlist(studentcount count[], int* studentsize) {
	int r = 0;	/*The keyword int declares 'r' to be an integer and a value of zero is assigned to it*/
	FILE *readfile;		/*Declares the file pointer to 'readfile'*/
	readfile = fopen(DB_FILE_NAME, "r");	/*Opens the file 'DB_FILE_NAME' in read mode*/
	while (EOF != fscanf(	/*Repeatedly executes the following statements as long as end-of-file is not equal to the formatted input being read from the database file. The following lines are executed and it loops over each row of the database and aligns the current element in the list to the values from the database*/
					readfile,
					"%11s %02d-%02d-%d %f\n",
					count[r].name, &count[r].birthday.day, &count[r].birthday.month, &count[r].birthday.year, &count[r].gpa)) {
						r++; }
	*studentsize = r;	/*Number of rows in the database file is set according to the size of the studentlist*/
	fclose(readfile);	/*Closes the opening file stream 'readfile'*/
}