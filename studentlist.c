/***************************************************************************
48430 Embedded C - Assignment 2
Name: Yasin Azimi
Student ID: 11733490
Date of submission: 18/05/2016
A brief statement on what you could achieve (less than 50 words):
= My work is of high standards and I believe this program meets 95% of the requirements. It uses suitable struct, pointer and variable names with no declaration of global variables. Hence, it passes all the declared variables and pointers through the use of pointers in each method. Each method performs its own specific task which makes the program low coupling and high cohesive. The program meets all of the inexperienced user requirements and the majority of the hostile user requirements. Therefore, it does not generate any error message during compilation. I am hoping to achieve a High Distinction in the range of 22-25.


A brief statement on what you could NOT achieve (less than 50 words):
= One requirement of the hostile user which I was unable to achieve is when the user inputs a 'space' followed by an integer for their birthday dates. My program should disregard the input and print out an error message, but instead it takes the integer input after the space.



***************************************************************************/

/**************************************************************************
List of header files and preprocessing directives
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_CLASS_SIZE 5		/*Maximum number of students in the class*/
#define MAX_NAME_SIZE 11		/*Maximum length of the string: student name*/
#define DB_FILE_NAME "database"	/*Static file name of the text file where student list is stored*/



/**************************************************************************
Structs
***************************************************************************/
struct date {	/*Declare struct, where 'date' is the name of struct*/
	int day;	/*Declare member of struct; 'day' which is an unsigned integer between 1 and 31*/
	int month;	/*Declare member of struct; 'month' which is an unsigned integer between 1 and 12*/
	int year;	/*Declare member of struct; 'year' which is an unsigned integer between 1800 and 2016*/
};

struct student {				/*Declare struct, where 'student' is the name of struct*/
	char name[MAX_NAME_SIZE];	/*Declare member of struct; 'name[MAX_NAME_SIZE]', which is the name of the student along with the size of the name passed from the preprocessor directive*/
	float gpa;					/*Declare member of struct; 'gpa', which is a float from 0.0 and 4.0*/
	struct date birthday;		/*Declare a nested struct which calls the struct 'date' with the variable 'birthday' passed to it*/
};

typedef struct student studentcount;	/*typedef assigns alternative variable 'studentcount' to the existing struct 'student'*/



/**************************************************************************
Function prototypes
***************************************************************************/
int flush_stdin();												/*Validate integer input*/
int main(void);													/*Main*/
void printmenu(void);											/*Print menu*/
void addstudent(studentcount count[], int* studentsize);		/*Add student*/
void deletestudent(studentcount count[], int* studentsize);		/*Delete last student*/
void showstudentlist(studentcount count[], int* studentsize);	/*Display student list*/
void savestudentlist(studentcount count[], int* studentsize);	/*Save the student list to the database*/
void readstudentlist(studentcount count[], int* studentsize);	/*Read the student list from the database*/



/**************************************************************************
Validate integer input
***************************************************************************/
int flush_stdin() {
	while (getchar() != '\n');	/*It fetches a character from the input stream every time it's called and compares getchar to '\n' if not equal, breaks the loop*/
	return 1;
}



/**************************************************************************
Main
***************************************************************************/
int main(void) {
	studentcount studentlist[MAX_CLASS_SIZE];	/*Initialising array studentlist[MAX_CLASS_SIZE], with structure type student. This is where the list of students are stored*/
	int studentsize = 0;	/*The keyword int declares 'studentsize' to be an integer. This variable name will be used as an integer pointer*/
	char option;	/*The keyword char declares 'option' to be a character*/
	
	do {
		printmenu();	/*Calling the function printmenu*/
		printf("Enter your choice>");	/*Prompts user to select an option from the printmenu*/
		scanf("%c", &option);	/*Receives an input value from the user and stores that value in the 'option' character*/
		switch (option)		/*Switch statement tests a character input against the following list of values*/
		{
			case '1':
					if (studentsize < MAX_CLASS_SIZE) {		/*Checks if the number of students in the class is less than 5*/
						addstudent(studentlist, &studentsize);		/*If they are, than add the student to the list in 'studentsize' stored as an array of struct type 'student'*/
					} else {	/*If the number of students in the class is greater than or equal to 5, print out 'Class is full'*/
						printf("Class is full\n");
					}
					break;	/*Terminates the execution of the switch statement if '1' is selected from the printmenu option*/
					
			case '2':
					if (studentsize > 0) {		/*Checks if the number of students in the class is greater than 0*/
						deletestudent(studentlist, &studentsize);	/*If they are, than delete the most recent student added to the list in 'studentsize' stored as an array of struct type 'student'*/
					} else {	/*If there are no students in the list, print out 'Class is empty'*/
						printf("Class is empty\n");
					}
					break;	/*Terminates the execution of the switch statement if '2' is selected from the printmenu option*/
					
			case '3':
					if (studentsize <= 0) {		/*Checks if there are no students in the list*/
						printf("Class is empty\n");		/*If there is none, prints out 'Class is empty'*/
					} else {	/*If there are students in the list*/
						showstudentlist(studentlist, &studentsize);		/*Display the students in the terminal that are in the list in 'studentsize' stored as an array of struct type 'student'*/
					}
					break;	/*Terminates the execution of the switch statement if '3' is selected from the printmenu option*/

			case '4':
					savestudentlist(studentlist, &studentsize);		/*Makes a backup copy of the current studentlist to the database file that are in the 'studentsize' as an array of struct type 'student'*/
					break;	/*Terminates the execution of the switch statement if '4' is selected from the printmenu option*/
					
			case '5':
					if (studentsize <= 0) {		/*Checks if there are no students in the list 'studentsize' (an instance where no backup copy of student list is made to a database file)*/
						printf("Read error\n");		/*If there are none, print out 'Read error'*/
					} else {	/*If there is an instance of a database and a backup copy of students list exists in that database file*/
						readstudentlist(studentlist, &studentsize);		/*Than read all the students that are in the database file in 'studentsize' stored as an array of struct type 'student'*/
					}
					break;	/*Terminates the execution of the switch statement if '5' is selected from the printmenu option*/
					
			case '6':
					exit(EXIT_SUCCESS);		/*Exits the program*/
					break;	/*Terminates the execution of the switch statement if '6' is selected from the printmenu option*/
					
			default:
					printf("Invalid choice.\n");	/*If any other value is entered outside of the above cases, prints out 'Invalid choice'*/
					break;	/*Terminates the execution of the switch statement if any other value is entered outside of the above cases*/
		}
	}
	while (option != '6' && flush_stdin());		/*The above switch statement is executed if the input value is not 6 and clears the buffer*/
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
Add student
***************************************************************************/
void addstudent(studentcount count[], int* studentsize) {
	studentcount addnewstudent;		/*Declaring another instance of variable 'addnewstudent' to the struct type 'student'*/
	
	printf("Enter name>");	/*Prompts user to enter name*/
	if (scanf(" %10[^\n]", addnewstudent.name) != EOF) {	/*Checks for the receiving input and only receives the first 10 characters. The scanf reads the strings and the format string " %10[^\n]" tells the function to read every character that is not '\n' and therefore, that leaves the '\n' character in the input buffer. It then puts these characters in the variable 'addnewstudent' which is stored as an array of struct type 'student'*/
		flush_stdin();	/*Clear the buffer*/
	}

	printf("Enter birthday: day>");		/*Prompts user to enter birthday: day*/
	scanf("%d", &addnewstudent.birthday.day);
	while (addnewstudent.birthday.day < 1 || addnewstudent.birthday.day > 31) {
		printf("Invalid day. Enter birthday: day>");	
		if (scanf("%d", &addnewstudent.birthday.day) != EOF) {
			flush_stdin();	/*Clear the buffer*/
		}
	}
	
	printf("Enter birthday: month>");	/*Prompts user to enter birthday: month*/
	scanf("%d", &addnewstudent.birthday.month);
	while (addnewstudent.birthday.month < 1 || addnewstudent.birthday.month > 12) {
		printf("Invalid month. Enter birthday: month>");
		if (scanf("%d", &addnewstudent.birthday.month) != EOF) {
			flush_stdin();	/*Clear the buffer*/
		}
	}
	
	printf("Enter birthday: year>");	/*Prompts user to enter birthday: year*/
	scanf("%d", &addnewstudent.birthday.year);
	while (addnewstudent.birthday.year < 1800 || addnewstudent.birthday.year > 2016) {
		printf("Invalid year. Enter birthday: year>");
		if (scanf("%d", &addnewstudent.birthday.year) != EOF) {
			flush_stdin();	/*Clear the buffer*/
		}
	}
	
	printf("Enter GPA>");	/*Prompts user to enter gpa*/
	scanf("%f", &addnewstudent.gpa);	
	while (addnewstudent.gpa < 0.0 || addnewstudent.gpa > 4.0) {
		printf("Invalid GPA. Enter GPA>");
		if (scanf("%f", &addnewstudent.gpa) != EOF) {
			flush_stdin();	/*Clear the buffer*/
		}
	}
	
	count[*studentsize] = addnewstudent;
	*studentsize += 1;
}



/**************************************************************************
Delete last student
***************************************************************************/
void deletestudent(studentcount count[], int* studentsize) {
	if (*studentsize > 0) {		/*Checks if the value inside the 'studentsize' is greater than zero*/
		(*studentsize)--;	/*If it is, than decrement the most recent element in the array*/
	}
}



/**************************************************************************
Display student list
***************************************************************************/
void showstudentlist(studentcount count[], int* studentsize) {
	int element;	/*The keyword int declares 'element' to be an integer*/
	printf("Name       Birthday   GPA\n");	/*Prints out to the terminal to show the headings for student details*/
	printf("---------- ---------- ------\n");	/*Prints out to the terminal to indicate formatted spaces between the headings*/
	for (element = 0; element < *studentsize; element++) {		/*Assigns an integer value of 0 to the variable 'element' with a condition to check whether the 'element' is less than the value stored inside the 'studentsize' pointer. This will then proceed to print out to the terminal the following commands and hence, continues the iterations 'element++'*/
		printf("%-11.10s", count[element].name);	/*Prints out to the terminal the first 10 characters of the student's name with a left indentation of 11 spaces*/
		printf("%02d-%02d-%-5.4d", count[element].birthday.day, count[element].birthday.month, count[element].birthday.year);	/*Prints out to the terminal the formatted birthday dates of the student in the form of '00-00-0000'*/
		printf("%.4f\n", count[element].gpa);	/*Prints out to the terminal the gpa of the student with four 0's padded after the decimal place*/
	}
}



/**************************************************************************
Save the student list to the database
***************************************************************************/
void savestudentlist(studentcount count[], int* studentsize) {
	int record;		/*The keyword int declares 'record' to be an integer*/
	FILE *writefile;	/*Declares the file pointer to 'writefile'*/
	writefile = fopen(DB_FILE_NAME, "w");	/*Opens the file 'DB_FILE_NAME' in read mode*/
	for (record = 0; record < *studentsize; record++) {		/*Assigns an integer value of 0 to the variable 'record' with a condition to check whether the 'record' is less than the value stored inside the 'studentsize' pointer. This will then proceed to read formatted input from a stream that was displayed previously in the terminal and hence, continues the iterations 'element++'*/
		fprintf(writefile, "%11s ", count[record].name);	/*Sends formatted output to a stream where the number of bytes for character name is saved to a file*/
		fprintf(writefile, "%02d-%02d-%d ", count[record].birthday.day, count[record].birthday.month, count[record].birthday.year);		/**/
		fprintf(writefile, "%f\n", count[record].gpa);	/**/
	}
	fclose(writefile);
}



/**************************************************************************
Read the student list from the database
***************************************************************************/
void readstudentlist(studentcount count[], int* studentsize) {
	int r = 0;	/*The keyword int declares 'r' to be an integer and a value of zero is assigned to it*/
	FILE *readfile;
	readfile = fopen(DB_FILE_NAME, "r");
	while (EOF != fscanf(
					readfile,
					"%11s %02d-%02d-%d %f\n",
					count[r].name, &count[r].birthday.day, &count[r].birthday.month, &count[r].birthday.year, &count[r].gpa)) {
						r++; }
	*studentsize = r;
	fclose(readfile);
}








