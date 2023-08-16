//	lab 3
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
int minutesList[59];

//functions
void insert();
void list();
void listbytime();
void delete();
int check_duplicate();

// main
int main (void)
{
	int option;


	while (1) {
		printf ("Option 1: Insert Task\n Option 2: List From Older to Newest\n Option 3: Tasks at a given hour\n Option 4: Delete \nOption 0: Quit\nInsert Choice: ");
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
				listbytime();
				break;
			
			case 4:
				delete();
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
	int minutes;
	int i;
	int j;

	if (counter == 10) {
		printf("The list is full\n");
		return;
	}
	printf("Enter task: ");
	__fpurge(stdin);
	scanf("%[^'\n']", &task);
	if(check_duplicate(task) == 1) {
		return;
	}
	printf("Enter hour of day in military time: ");
	scanf("%d", &hour);
	printf("Enter what minute: ");
	scanf("%d", &minutes);
	if (hour < 0 || hour > 23) {
		printf("Hour %d does not exist\n", hour);
		return;
	}
	if (minutes < 0 || minutes > 59) {
		printf("Minute %d does not exist", minutes);
		return;
	} 

	for (i = 0; i < counter; i++) {
		if(hour > hoursList[i]) {
			continue;
		} else if(hour == hoursList[i]) {
			if(minutes > minutesList[i]) {
				continue;
			} else {
				break;
			}
		} else {
			break;
		}
	}
	
	for (j = counter-1; j >= i; j--) {
	        strcpy(tasksList[j+1], tasksList[j]);
		minutesList[j+1] = minutesList[j];
		hoursList[j+1] = hoursList[j];
	}
	strcpy(tasksList[i], task);
	minutesList[i] = minutes;
	hoursList[i] = hour;
	counter++;

}	

int check_duplicate(char task[20]) {
	int i;
	for(i = 0; i<counter; i++) {
		if(strcmp(tasksList[i], task) == 0) {
			printf("This task already exists\n");
			return 1;
		} else {
			return 0;
		}
	}
}

void list() {
	int i = 0;
	if(counter == 0) {
		printf("There are no tasks\n\n");
		return;
	}
	for (i = 0; i < counter; i++) {
		printf("Task: %s    Time: %d: %02d\n", tasksList[i], hoursList[i], minutesList[i]);
	}
}

void listbytime() {
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

void delete() {
	char deleteTask[20];
	int i;
	int j;
	
	if (counter == 0) {
		printf("There are no tasks");
	} else {
		printf("What task would you like to delete: ");
		scanf("%s", &deleteTask);
		for (i = 0; i < counter; i++) {
			if((strcmp(deleteTask, tasksList[i])) == 0) {
	                        printf("Task: %s has been deleted.\n",tasksList[i]);

				for(i; i < counter; i++) {
					strcpy(tasksList[i], tasksList[i+1]);
					hoursList[i] = hoursList[i+1];
					minutesList[i] = minutesList[i+1];
				}
				counter--;
				return;
			}
		}
	}
}





















