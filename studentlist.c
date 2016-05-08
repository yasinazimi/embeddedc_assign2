/**********************************************************************
48430 Embedded C - Assignment 2
Name: Yasin Azimi
Student ID: 11733490
Date of submission: 00/05/2016
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



/**********************************************************************
Sturcts
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



/**********************************************************************
Main
**********************************************************************/
int main(void){
	int choice;
	int m;	
	student studentlist[MAX_CLASS_SIZE+1];
	strcpy(studentlist[0].name, "SENTINEL");
		
	while (1) {
		
		printmenu();
		printf("Enter your choice>");
		scanf("%d", &choice);
		
		if (choice == 1) {
		
			m = 0;
			while (strcmp(studentlist[m].name, "SENTINEL")) m++;
			
				if (m < MAX_CLASS_SIZE)
				{
					addstudent(&studentlist[m]);
					strcpy(studentlist[m+1].name, "SENTINEL");
				}
				else printf("Class is full\n");
		}
	
		else if (choice == 2) {
			
				m = 0;
				while (strcmp(studentlist[m].name, "SENTINEL")) m++;
					if (m == 0) {
						printf("Class is empty\n");
					}
					else {
						strcpy(studentlist[m-1].name, "SENTINEL");
					}
			}
		
		/*else if (choice == 3) {
				showstudent(studentlist);
			}
				
		else if (choice == 4) {
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
}



/**********************************************************************
Get birthday dates 
**********************************************************************/

void getbirthday(date* dateinput) {
	
	printf("Enter birthday: day>");
	scanf("%d", &dateinput->day);
	while(1 > dateinput->day || dateinput->day > 31 )
	{
		printf("Invalid day. Enter birthday: day>"); 
		scanf("%d", &dateinput->day);
	}       
	
	
	printf("Enter birthday: month>");
	scanf("%d", &dateinput->month);
	while( 1 > dateinput->month || dateinput->month > 12)
	{
		printf("Invalid month. Enter birthday: month>");
		scanf("%d", &dateinput->month);
	}
	
	
	printf("Enter birthday: year>");
	scanf("%d", &dateinput->year);
	while(2016 < (dateinput->year) || 1800 > (dateinput->year))
	{
		printf("Invalid year. Enter birthday: year>");
		scanf("%d", &dateinput->year);
	}
		
}



































