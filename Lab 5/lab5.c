//	lab 5
//	winter 2023
//	name: Joshua Colleran
//


//  includes
#include	<stdio.h>
#include	<string.h>

// defines


// global variables
int counter = 0;

typedef union {
        float budget;
        char location[20];
        int time[2];
} INFO2;

typedef struct info {
	int hoursList;
	char tasksList[20];
	int minutesList;
	INFO2 info;
} INFO;



INFO array[10];
INFO *p;

//functions
void insert();
void list();
void listbytime();
void delete();
int check_duplicate();
void deleteByHour();

// main
int main (void)
{
	int option;


	while (1) {
		printf ("Option 1: Insert Task\n Option 2: List From Older to Newest\n Option 3: Tasks at a given hour\n Option 4: Delete \n Option 5: Delete by hour\nOption 0: Quit\nInsert Choice: ");
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
			case 5:
				deleteByHour();
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
	scanf("%[^'\n']", task);
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
		printf("%d", i);
		if(hour > array[i].hoursList) {
			continue;
		} else if(hour == array[i].hoursList) {
			if(minutes > array[i].minutesList) {
				continue;
			} else {
				break;
			}
		} else {
			break;
		}
	}
	
	for (j = counter-1; j >= i; j--) {
	        array[j+1] = array[j];
	}

        strcpy(array[i].tasksList, task);
        array[i].minutesList = minutes;
        array[i].hoursList = hour;


        if (hour < 12) {
                printf("\nWhat is your budget? ");
                scanf("%f", &array[i].info.budget);
        } else if (hour >= 12 && hour <= 20) {
                printf("\nWhere is your task? ");
                scanf("%s", array[i].info.location);
        } else if (hour > 20) {
                printf("\nWhat is your end time hour: ");
                scanf("%d", &array[i].info.time[0]);
		printf("\nWhat is your end time minute: ");
                scanf("%d", &array[i].info.time[1]);

        }
	counter++;	
}	

int check_duplicate(char task[20]) {
	int i;
	for(i = 0; i<counter; i++) {
		if(strcmp(array[i].tasksList, task) == 0) {
			printf("This task already exists\n");
			return 1;
		} else {
			return 0;
		}
	}
}

void list() {
	INFO *p = array;
	int i = 0;
	if(counter == 0) {
		printf("There are no tasks\n\n");
		return;
	}
	for (i = 0; i < counter; i++, p++) {
		printf("Task: %s    Time: %d: %02d\n", p->tasksList, p->hoursList, p->minutesList);
		if (p -> hoursList < 12) {
                	printf("\nYour Restriction is a budget of %.2f dollars\n", p->info.budget);
        	} else if (p -> hoursList >= 12 && p -> hoursList <= 20) {
                	printf("\nYour Restriction is it must be at location: %s\n", p->info.location);
        	} else if (p -> hoursList > 20) {
                	printf("\nYour Restriction is it must end by:  %d:%02d\n", p->info.time[0],p->info.time[1]);
        	}

			
	}
}

void listbytime() {
	INFO *p = array;
	int time;
	int hours;
	int i;
	int time2;
	printf("What time would you like to search for: \n");
	printf("Hour: ");
	scanf("%d", &time);
        printf("\nMinute: ");
        scanf("%d", &time2);

	for(i = 0; i < counter; i++, p++) {
		if (p-> hoursList == time && p-> minutesList == time2) {
			printf("\nAt time %d:%d you have a task of %s\n", time, time2, p->tasksList);
			hours++;
        		if (time < 12) {
        	        	printf("\nYour Restriction is a budget of %.2f dollars\n", p->info.budget);
		        } else if (time >= 12 && time <= 20) {
        		        printf("\nYour Restriction is it must be at location: %s\n", p->info.location);
	        	} else if (time > 20) {
                		printf("\nYour Restriction is it must end by:  %d:%02d\n", p->info.time[0],p->info.time[1]);
        		}
		}
	}
	if(hours == 0) {
		printf("\nThere are no tasks at time %d:%d\n", time,time2);
		return;

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
			if((strcmp(deleteTask, array[i].tasksList)) == 0) {
	                        printf("Task: %s has been deleted.\n",array[i].tasksList);

				for(i; i < counter; i++) {
					array[i] = array[i+1];
				}
				counter--;
				return;
			}
		}
	}
}

void deleteByHour() {
        INFO *p = array;
        int time;
        int hours;
        int i,j;
        printf("Which hour would you like to delete: ");
        scanf("%d", &time);
        for(i = 0; i < counter && p-> hoursList <= time; i++, p++) {
                if (p-> hoursList == time) {
			printf("Task: %s has been deleted.\n",p -> tasksList);
                        for(j=i; j < counter; j++) {
				array[j] = array[j+1];
                        }
                        counter--;
			i--;
                        hours++;
			p--;
                }
        }
        if(hours == 0) {
                printf("\nThere are no tasks at time %d\n", time);

	}
}







