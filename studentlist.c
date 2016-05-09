/**********************************************************************
48430 Embedded C - Assignment 2
Name: Yasin Azimi
Student ID: 11733490
Date of submission: 09/05/2016
A brief statement on what you could achieve (less than 50 words):
= 

A brief statement on what you could NOT achieve (less than 50 words):
= 

**********************************************************************/

/**********************************************************************
List of header files and preprocessing directives
**********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


#define MAX_CLASS_SIZE 5
#define MAX_NAME_SIZE 11
#define DB_FILE_NAME "database"
#define MIN_DAY 1
#define MAX_DAY 31
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_YEAR 1800
#define MAX_YEAR 2016
#define MIN_GPA 0.0
#define MAX_GPA 4.0



/**********************************************************************

**********************************************************************/

typedef struct {
	int day;
	int month;
	int year;
} date;


typedef struct {
	char name[MAX_NAME_SIZE];
	double gpa;
	date birthday;
} student;



/**********************************************************************
Function prototypes
**********************************************************************/
void printmenu(void);
void addstudent(student* studentinput);
void getbirthday(date* dateinput);

void showstudentlist(student studentlist[]);
void showstudent(student* showstudents);
void showdate(date* showdates);



/**********************************************************************
Main
**********************************************************************/
int main(void){
	int choice;
	int k;
	student studentlist[MAX_CLASS_SIZE+1];
	strcpy(studentlist[0].name, "SENTINEL");
		
	while (1)
	{
		
		printmenu();
		printf("Enter your choice>");
		scanf("%d", &choice);
		
		if (choice == 1)
		{
		
			k = 0;
			while (strcmp(studentlist[k].name, "SENTINEL")) k++;
			
				if (k < MAX_CLASS_SIZE)
				{
					addstudent(&studentlist[k]);
					strcpy(studentlist[k+1].name, "SENTINEL");
				}
				else printf("Class is full\n");
		}
	
		else if (choice == 2)
		{
			
			k = 0;
			while (strcmp(studentlist[k].name, "SENTINEL")) k++;
				if (k == 0) {
					printf("Class is empty\n");
				}
				else {
					strcpy(studentlist[k-1].name, "SENTINEL");
				}
		}
		
		else if (choice == 3)
		{
			showstudent(studentlist);
		}
				
		/*else if (choice == 4) {
				savestudent();
			}
				
		else if (choice == 5) {
				readstudent();
			}*/
	
	
		/*printmenu();*/
	
	}
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
Add student
**********************************************************************/
void addstudent(student* studentinput) {
	
    printf("Enter name>");
	scanf("%s", studentinput->name);
	
	getbirthday(&studentinput->birthday);
	
	printf("Enter GPA>");
	scanf("%lf", &studentinput->gpa);
	while (studentinput->gpa <MIN_GPA || studentinput->gpa >MAX_GPA)
	{
		printf("Invalid GPA. Enter GPA>");
		scanf("%lf", &studentinput->gpa);
	}
}



/**********************************************************************
Get birthday dates 
**********************************************************************/

void getbirthday(date* dateinput) {
	
	printf("Enter birthday: day>");
	scanf("%d", &dateinput->day);
	while (dateinput->day < MIN_DAY || dateinput->day > MAX_DAY)
	{
		printf("Invalid day. Enter birthday: day>"); 
		scanf("%d", &dateinput->day);
	}
	
	printf("Enter birthday: month>");
	scanf("%d", &dateinput->month);
	while (dateinput->month < MIN_MONTH || dateinput->month > MAX_MONTH)
	{
		printf("Invalid month. Enter birthday: month>");
		scanf("%d", &dateinput->month);
	}
	
	printf("Enter birthday: year>");
	scanf("%d", &dateinput->year);
	while (dateinput->year < MIN_YEAR || dateinput->year > MAX_YEAR)
	{
		printf("Invalid year. Enter birthday: year>");
		scanf("%d", &dateinput->year);
	}
}



/**********************************************************************
Display student list
**********************************************************************/
void showstudentlist(student studentlist[]) {
	
	int k = 0;
	if (strcmp((studentlist[k]).name, "SENTINEL") == 0)
	{
		printf("Class is empty\n");
	}
	else
	{
		while (strcmp(studentlist[k].name, "SENTINEL"))
		{
			showstudent(&studentlist[k]);
			++k;
		}
	}
}



/**********************************************************************
Display student
**********************************************************************/
void showstudent(student* showstudents) {
	printf("Name       Birthday   GPA\n");
	printf("---------- ---------- ------\n");
	
	printf("%-10.10s", showstudents->name);
	showdate(&showstudents->birthday);
	
	/*printf(" %lf", &showstudents->gpa);*/
	
	printf("\n");
}



/**********************************************************************
Display birthday
**********************************************************************/
void showdate(date* showdates) {
	printf(" %02d-%02d-%02d", showdates->day, showdates->month, showdates->year);
}



/**********************************************************************
Display gpa
**********************************************************************/



























