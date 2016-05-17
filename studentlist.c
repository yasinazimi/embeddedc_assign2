/***************************************************************************
48430 Embedded C - Assignment 2
Name: Yasin Azimi
Student ID: 11733490
Date of submission: 17/05/2016
A brief statement on what you could achieve (less than 50 words):
= 

A brief statement on what you could NOT achieve (less than 50 words):
= 

***************************************************************************/

/**************************************************************************
List of header files and preprocessing directives
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLASS_SIZE 5
#define MAX_NAME_SIZE 11
#define DB_FILE_NAME "database"



/**************************************************************************
Structs
***************************************************************************/
struct date {
	int day;
	int month;
	int year;
};

struct student {
	char name[MAX_NAME_SIZE];
	float gpa;
	struct date birthday;
};

typedef struct student studentcount;



/**************************************************************************
Function prototypes
***************************************************************************/
int flush_stdin();
void printmenu(void);
void addstudent(studentcount count[], int* studentsize);
void deletestudent(studentcount count[], int* studentsize);
void showstudentlist(studentcount count[], int* studentsize);
void savestudentlist(studentcount count[], int* studentsize);
void readstudentlist(studentcount count[], int* studentsize);



/**************************************************************************
Validating integer values
***************************************************************************/
int flush_stdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	return 1;
}



/**************************************************************************
Main
***************************************************************************/
int main(void) {
	studentcount studentlist[MAX_CLASS_SIZE];
	int SENTINEL = 0;
	int studentsize = 0;
	char option;

	do {
		printmenu();
		printf("Enter your choice>");
		scanf(" %c", &option);
		switch (option)
		{
			case '1':
					if (studentsize < MAX_CLASS_SIZE) {
						addstudent(studentlist, &studentsize);
					} else {
						printf("Class is full\n");
					}
					break;
					
			case '2':
					if (studentsize > 0) {
						deletestudent(studentlist, &studentsize);
					} else {
						printf("Class is empty\n");
					}
					break;
					
			case '3':
					if (studentsize <= 0) {
						printf("Class is empty\n");
					} else {
						showstudentlist(studentlist, &studentsize);
					}
					break;

			case '4':
					savestudentlist(studentlist, &studentsize);
					break;
					
			case '5':
					if (SENTINEL != 1) {
						printf("Read error\n");
					} else {
						readstudentlist(studentlist, &studentsize);
					}
					break;
					
			case '6':
					exit(EXIT_SUCCESS);
					break;
					
			default:
					printf("Invalid choice.\n");
					break;
		}
    }
	while (option != '6' && flush_stdin());
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
	studentcount addnewstudent;
	printf("Enter name>");
	if (scanf(" %10[^\n]", addnewstudent.name) != EOF) {
		flush_stdin();
	}
	
	printf("Enter birthday: day>");
	scanf("%d", &addnewstudent.birthday.day);
	while (addnewstudent.birthday.day < 1 || addnewstudent.birthday.day > 31) {
		printf("Invalid day. Enter birthday: day>");	
		if (scanf("%d", &addnewstudent.birthday.day) != EOF) {
			flush_stdin();
		}
	}
	
	printf("Enter birthday: month>");
	scanf("%d", &addnewstudent.birthday.month);
	while (addnewstudent.birthday.month < 1 || addnewstudent.birthday.month > 12) {
		printf("Invalid month. Enter birthday: month>");
		if (scanf("%d", &addnewstudent.birthday.month) != EOF) {
			flush_stdin();
		}
	}
	
	printf("Enter birthday: year>");
	scanf("%d", &addnewstudent.birthday.year);
	while (addnewstudent.birthday.year < 1800 || addnewstudent.birthday.year > 2016) {
		printf("Invalid year. Enter birthday: year>");
		if (scanf("%d", &addnewstudent.birthday.year) != EOF) {
			flush_stdin();
		}
	}
	
	printf("Enter GPA>");
	scanf("%f", &addnewstudent.gpa);
	while (addnewstudent.gpa < 0.0 || addnewstudent.gpa > 4.0) {
		printf("Invalid GPA. Enter GPA>");
		if (scanf("%f", &addnewstudent.gpa) != EOF) {
			flush_stdin();
		}
	}
	
	count[*studentsize] = addnewstudent;
	*studentsize += 1;
}



/**************************************************************************
Delete last student
***************************************************************************/
void deletestudent(studentcount count[], int* studentsize) {
	if (*studentsize > 0) {
		(*studentsize)--;
	}
}



/**************************************************************************
Display student list
***************************************************************************/
void showstudentlist(studentcount count[], int* studentsize) {
	int element;
	printf("Name       Birthday   GPA\n");
	printf("---------- ---------- ------\n");
	for (element = 0; element < *studentsize; element++) {
		printf("%-11.10s", count[element].name);
		printf("%02d-%02d-%-5.4d", count[element].birthday.day, count[element].birthday.month, count[element].birthday.year);
		printf("%.4f\n", count[element].gpa);
	}
}



/**************************************************************************
Save the student list to the database
***************************************************************************/
void savestudentlist(studentcount count[], int* studentsize) {
	int record;
	FILE *writefile;
	writefile = fopen(DB_FILE_NAME, "w");
	for (record = 0; record < *studentsize; record++) {
		fprintf(writefile, "%11s ", count[record].name);
		fprintf(writefile, "%02d-%02d-%d ", count[record].birthday.day, count[record].birthday.month, count[record].birthday.year);
		fprintf(writefile, "%f\n", count[record].gpa);
	}
	fclose(writefile);
}



/**************************************************************************
Read the student list from the database
***************************************************************************/
void readstudentlist(studentcount count[], int* studentsize) {
	int r = 0;
	FILE *readfile;
	readfile = fopen(DB_FILE_NAME, "r");
	while (r < MAX_CLASS_SIZE) {
		if (fscanf(readfile, "%11s ", count[r].name)) {
			r++; }
		if (fscanf(readfile, "%02d-%02d-%d ", &count[r].birthday.day, &count[r].birthday.month, &count[r].birthday.year)) {
			r++; }
		if (fscanf(readfile, "%f\n", &count[r].gpa)) {
			r++; }
	}
	*studentsize = r;
	fclose(readfile);
}










