/**********************************************************************
48430 Embedded C - Assignment 2
Name: Yasin Azimi
Student ID: 11733490
Date of submission: 16/05/2016
A brief statement on what you could achieve (less than 50 words):
= 

A brief statement on what you could NOT achieve (less than 50 words):
= 

**********************************************************************/

/**********************************************************************
List of header files and preprocessing directives
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CLASS_SIZE 5
#define MAX_NAME_SIZE 11
#define DB_FILE_NAME "database"



/**********************************************************************

**********************************************************************/

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



/**********************************************************************
Function prototypes
**********************************************************************/
void printmenu(void);
void addstudent(studentcount count[], int* studentsize);
void showstudentlist(studentcount count[], int* studentsize);
void savestudentlist(studentcount count[], int* studentsize);
void readstudentlist(studentcount count[], int* studentsize);
void flush_stdin(void);



/**********************************************************************
Validating integer values
**********************************************************************/
char checkRange(char max, char min, char num) {
    if (num <= max && num >= min) {
        return 1;
    }
    else {
        return 0;
    }
}



/**********************************************************************
Validating integer values
**********************************************************************/
void flush_stdin(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}



/**********************************************************************
Main
**********************************************************************/
int main(void){
	studentcount studentlist[MAX_CLASS_SIZE-1];
	char SENTINEL = NULL;
	int studentsize = 0;
	char option;

	while (option != '6') {
		printmenu();
		printf("Enter your choice>");
		scanf(" %c", &option);
		switch (option)
		{
			case '1':
					if (SENTINEL == 0) {
						if (studentsize >= 0 && studentsize <= 4) {
							addstudent(studentlist, &studentsize);
						}
					}
					else if (SENTINEL != 1) {
						if (studentsize > 4) {
							printf("Class is full\n");
						}
					}
					break;
					
			case '2':
					if (studentsize > 0) {
						studentsize--;
					}
					else if (studentsize <= 0) {
						printf("Class is empty\n");
					}
					break;
					
			case '3':
					showstudentlist(studentlist, &studentsize);
					break;

			case '4':
					savestudentlist(studentlist, &studentsize);
					break;
					
			case '5':
					readstudentlist(studentlist, &studentsize);
					break;
					
			case '6':
					exit(EXIT_SUCCESS);
					
			default:
					printf("Invalid choice.\n");
					break;
		}
    }
	
    return 1;
}



/**********************************************************************
Choices menu
**********************************************************************/
void printmenu(void){
    printf("\n\n"
                   "1. add student\n"
                   "2. delete last student\n"
                   "3. display student list\n"
                   "4. save the student list to the database\n"
                   "5. read the student list from the database\n"
                   "6. exit the program\n");
}



/**********************************************************************
Add new student
**********************************************************************/
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



/**********************************************************************
Display the students in a list

// printf("Class is empty\n");
**********************************************************************/
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



/**********************************************************************
Save studentlist to database

// overwrite if database file already exists
**********************************************************************/
void savestudentlist(studentcount count[], int* studentsize) {
	int record;
	FILE *writefile;
	writefile = fopen("database", "w");
	for (record = 0; record < *studentsize; record++) {
		fprintf(writefile, "%s\t", count[record].name);
		fprintf(writefile, "%d\t%d\t%d\t", count[record].birthday.day, count[record].birthday.month, count[record].birthday.year);
		fprintf(writefile, "%.6f\n", count[record].gpa);
	}
	fclose(writefile);
}



/**********************************************************************
Read studentlist from database
**********************************************************************/
void readstudentlist(studentcount count[], int* studentsize) {
	int r;
	FILE *readfile;
	
	readfile = fopen("database", "r");
	if (readfile == NULL) {
		printf("Read error\n");
	}
	else if (readfile) {
		while ((r = getc(readfile)) != EOF)
			putchar(r);
		fclose(readfile);
	}	
}










