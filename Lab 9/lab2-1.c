//	lab 2
//	winter 2023
//	name: Joshua Colleran
//


//  includes
#include	<stdio.h>
#include	<string.h>

// defines


// global variables
int hoursList[23];
char tasksList[10][20];
int counter = 0;

//functions
void insert();
void list();
void list_hour();

// main
int main (void)
{
	int option;


	while (1)
	{
		printf ("Option 1: Insert Task\n Option 2: List From Older to Newest\n Option 3: Tasks at a given hour\n Option 0: Quit\nInsert Choice: ");
		scanf ("%d", &option);
		
		switch (option)
		{
			case 1:
				insert();
				break;

			case 2:
				list();
				break;

			case 3:
				list_hour();
				break;
			
			case 0:
				return 0;	

	
			default:
				printf ("Incorrect button \n");
		}

	}	

}

void insert() {
	char task[20];
	int hour;
	if (counter == 10) {
		printf("The list is full\n");
		return;
	}
	printf("Enter task: ");
	__fpurge(stdin);
	scanf("%[^'\n']", &task);
	printf("Enter hour of day in military time: ");
	scanf("%d", &hour);
	if (hour < 0 || hour > 23) {
		printf("Hour %d does not exists\n", hour);
		return;
	}
	strcpy(tasksList[counter], task);
	hoursList[counter] = hour;
	counter++;
}	


void list() {
	int i = 0;
	if(counter == 0) {
		printf("There are no tasks\n\n");
		return;
	}
	for (i = 0; i < counter; i++) {
		printf("Task: %s    Time: %d\n", tasksList[i], hoursList[i]);
	}
}

void list_hour() {
	int time;
	int hours;
	int i;
	printf("What time would you like to search for: ");
	scanf("%d", &time);
	for(i = 0; i < counter; i++) {
		if (hoursList[i] == time) {
			printf("\nAt time %d you have a task of %s\n", time, tasksList[i]);
			hours++;
		}
	}
	if(hours == 0) {
		printf("\nThere are no tasks at time %d\n", time);

	}
}






















