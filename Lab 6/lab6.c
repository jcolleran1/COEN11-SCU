//	lab 6
//	winter 2023
//	name: Joshua Colleran
//


//  includes
#include	<stdio.h>
#include	<string.h>
#include        <stdlib.h>



// global variables
typedef union {
        float budget;
        char location[20];
        int time[2];
} INFO2;

#define SCHEDULE struct info

typedef struct info {
	int hoursList;
	char tasksList[20];
	int minutesList;
	INFO2 info;
	SCHEDULE *next;
} INFO;

SCHEDULE *head = NULL;
SCHEDULE *tail = NULL;


//functions
void insert();
void list();
void listbytime();
void delete();
int check_duplicate();

// main
int main (void) {
	int option;


	while (1) {
		printf ("Option 1: Insert Task\n Option 2: List\n Option 3: Tasks at a given hour\n Option 4: Delete \nOption 0: Quit\nInsert Choice: ");
		scanf ("%d", &option);
		
		switch (option) {
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
	SCHEDULE *p, *q;
	q = head;

	p = (SCHEDULE *) malloc (sizeof(SCHEDULE));
	printf("Enter task: ");
	__fpurge(stdin);
	scanf("%[^'\n']", p -> tasksList);


	if (p == NULL) {
		printf("Memory is full\n");
		return;
	}
	if(check_duplicate(p -> tasksList) == 1) {
             return;
        }
        printf("Enter hour of day in military time: ");
	scanf("%d", &p -> hoursList);
        printf("Enter what minute: ");
      	scanf("%d", &p -> minutesList);
        if (p -> hoursList < 0 || p -> hoursList > 23) {
               	printf("Hour %d does not exist\n", p -> hoursList);
               	return;
        }
        if (p -> minutesList < 0 || p -> minutesList > 59) {
               	printf("Minute %d does not exist", p -> minutesList);
               	return;
        }


	if (p -> hoursList < 12) {
                printf("\nWhat is your budget? ");
               	scanf("%f", &p -> info.budget);
	} else if (p -> hoursList >= 12 && p -> hoursList <= 20) {
                printf("\nWhere is your task? ");
               	scanf("%s", &p -> info.location);
	} else if (p -> hoursList > 20) {
                printf("\nWhat is your end time hour: ");
               	scanf("%d", &p -> info.time[0]);
	        printf("\nWhat is your end time minute: ");
                scanf("%d", &p -> info.time[1]);

        }

        if(head == NULL && tail == NULL) {
                head = p;
                tail = p;
        } else {
                tail->next = p;
                tail = tail->next;
        }
	
		
}


int check_duplicate(char task[20]) {
	INFO *p;
	p = head;
	while (p != NULL) {
		if(strcmp(p -> tasksList, task) == 0) {
			printf("This task already exists\n");
			return 1;
		} else {
			return 0;
		}
		p = p -> next;
	}
}

void list() {
	INFO *p;
	p = head;
	if(p == NULL) {
		printf("There are no tasks\n\n");
		return;
	}
	while (p != NULL) {
		printf("Task: %s    Time: %d: %02d\n", p->tasksList, p->hoursList, p->minutesList);
		if (p -> hoursList < 12) {
                	printf("\nYour Restriction is a budget of %.2f dollars\n", p->info.budget);
        	} else if (p -> hoursList >= 12 && p -> hoursList <= 20) {
                	printf("\nYour Restriction is it must be at location: %s\n", p->info.location);
        	} else if (p -> hoursList > 20) {
                	printf("\nYour Restriction is it must end by:  %d:%02d\n", p->info.time[0],p->info.time[1]);
        	}
		p = p -> next;
			
	}
}

void delete() {
	INFO *p;
	p = head;
	if (head == NULL) {
		printf("There are no tasks");
		return;
	} else {
		head = head -> next;
		if (head == NULL) {
			tail = NULL;
		}
		printf("Your task %s has been deleted\n", p -> tasksList);
		free(p);
	}
}



void listbytime() {
	INFO *p;
	p = head;
        int time;
        int hours;
        int time2;
        printf("What time would you like to search for: \n");
        printf("Hour: ");
        scanf("%d", &time);
        printf("\nMinute: ");
        scanf("%d", &time2);

        while (p != NULL){
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
		p = p -> next;
        }
        if(hours == 0) {
                printf("\nThere are no tasks at time %d:%d\n", time,time2);
                return;

        }
}

