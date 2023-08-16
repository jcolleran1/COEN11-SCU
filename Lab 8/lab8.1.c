//	lab 8
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

//define
#define SCHEDULE struct info

typedef struct info {
	int hoursList;
	char tasksList[20];
	int minutesList;
	int priority;
	INFO2 info;
	SCHEDULE *next;
} INFO;

SCHEDULE *heads[3];


//functions
void insert();
void list();
void listbytime();
void delete();
int check_duplicate(char task[]);
void save_to_file();
void delete_all_nodes();
void read_file(char *name);
void userInfo();

// main
int main (int argc, char *argv[]) {
	int option;

        if (argc == 1) {
                printf ("The name of the file is missing!\n");
                return 1;
        }
        read_file (argv[1]);


	while (1) {
		printf ("Option 1: Insert Task\n Option 2: List From Older to Newest\n Option 3: Tasks at a given hour\n Option 4: Delete \nOption 0: Quit and saves a text file\nInsert Choice: ");
		scanf ("%d", &option);
		
		switch (option) {
			case 1:
				userInfo();
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
				save_to_file(argv[1]);
				delete_all_nodes();
				printf("exit");
				return 0;	
				
	
			default:
				printf ("Incorrect button \n");
		}

	}	
}

void userInfo() {
	SCHEDULE p;
	printf("What is the priority of your task? (1, 2, 3)");
        scanf("%d", &p.priority);
        printf("Enter task: ");
        __fpurge(stdin);
        scanf("%[^'\n']", p.tasksList);
       
        if(check_duplicate(p.tasksList) == 1) {
             return;
        }
        printf("Enter hour of day in military time: ");
        scanf("%d", &p.hoursList);
        printf("Enter what minute: ");
        scanf("%d", &p.minutesList);
        if (p.hoursList < 0 || p.hoursList > 23) {
                printf("Hour %d does not exist\n", p.hoursList);
                return;
        }
        if (p.minutesList < 0 || p.minutesList > 59) {
                printf("Minute %d does not exist", p.minutesList);
                return;
        }


        if (p.hoursList < 12) {
                printf("\nWhat is your budget? ");
                scanf("%f", &p.info.budget);
        } else if (p.hoursList >= 12 && p.hoursList <= 20) {
                printf("\nWhere is your task? ");
                scanf("%s", &p.info.location);
        } else if (p.hoursList > 20) {
                printf("\nWhat is your end time hour: ");
                scanf("%d", &p.info.time[0]);
                printf("\nWhat is your end time minute: ");
                scanf("%d", &p.info.time[1]);

        }
	insert(p);	
}

void insert(SCHEDULE node) {
	SCHEDULE *z, *q, *p;
	p = (SCHEDULE *) malloc (sizeof(SCHEDULE));
	
	*p = node;
	z = q = heads[p->priority-1];
	if (p == NULL) {
		printf("Your memory is full.");
	}
	while (z != NULL) {
		if (z -> hoursList > p -> hoursList) {
			break;
		} else if (z -> hoursList == p -> hoursList) {
			if (z -> minutesList > p -> minutesList) {
				break;
			}
		}
		q = z;
		z = z -> next; 

	}
	if (z == heads[p->priority-1]) {
		p -> next = heads[p->priority-1];
		heads[p->priority-1] = p;
	} else {
		p -> next = z;
		q -> next = p;
	}
	return;

}


int check_duplicate(char task[20]) {
	int i;
	for (i=0; i < 3; i++) {
		SCHEDULE *p = heads[i];
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
}

void list() {
	SCHEDULE *p;
	int i = 0;
	for (i = 0; i < 3; i++) {
	        p = heads[i];
	        if(p == NULL) {
        	        printf("There are no tasks in priority %d\n",i+1);
        	}
		while (p != NULL) {
			printf("Priority: %d Task: %s    Time: %d: %02d\n", i+1, p->tasksList, p->hoursList, p->minutesList);
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
	return;
}

void delete() {
	int i;
        SCHEDULE *z;
        SCHEDULE *q;
        INFO p;
        int temp;
        printf("Which task would you like to delete: ");
        scanf("%s", p.tasksList);

	for (i = 0; i < 3; i++) {
		z = heads[i];
		q = heads[i];
	       	while (z != NULL){
                	if (strcmp(z -> tasksList, p.tasksList) == 0) {
		             	printf("Task: %s has been deleted.\n", p.tasksList);
				temp = i;
				i = 3;
				break;
			}
                        q = z;
			z = z -> next;				
        	}
	}
        if (z == NULL) {
	        printf("There are no tasks");
                return;
	}
	if (z == heads[temp]) {
		heads[temp] = heads[temp] -> next;
		free(z);
	} else {
		q -> next = z-> next;
		free(z);			
	}
}



void listbytime() {
	INFO *p;
        int time;
        int hours;
        int time2;
	int i;
        printf("What time would you like to search for: \n");
        printf("Hour: ");
        scanf("%d", &time);
        printf("\nMinute: ");
        scanf("%d", &time2);
	for(i = 0;i < 3; i++) {
		p = heads[i];
 		while (p != NULL){
        	        if (p-> hoursList == time && p-> minutesList == time2) {
                	        printf("\nAt time %d:%d you have a task of %s in prioirty %d\n", time, time2, p->tasksList, i+1);
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
        	        printf("\nThere are no tasks at time %d:%d in priority %d\n", time,time2,i);
                	return;

        	}	
	}
}

void save_to_file(char *name) {
	FILE *outfp;
	int i;
	SCHEDULE *p;
	outfp = fopen(name, "w");
	if ((outfp = fopen (name, "w")) == NULL) {
		printf ("cannot open the file data.txt\n");
	}
	for(i = 0; i < 3; i++) {
		p = heads[i];
     		while (p != NULL) {
			fprintf(outfp, "%s %d %d:%.02d ", p->tasksList, p->priority, p->hoursList, p->minutesList);
	                if (p -> hoursList < 12) {
        	                fprintf(outfp,"%.2f\n", p->info.budget);
                	} else if (p -> hoursList >= 12 && p -> hoursList <= 20) {
                        	fprintf(outfp, "%s\n", p->info.location);
	                } else if (p -> hoursList > 20) {
        	                fprintf(outfp, "%d:%d\n", p->info.time[0], p->info.time[1]);
                	}
                	p = p -> next;

        	}
	}
	fclose(outfp);
	return;
}

void read_file(char *name) {
	FILE *fp;
	char colon;
	SCHEDULE temp;
	fp = fopen(name, "r");
	int i;
	if (fp == NULL) {
		printf("Errror: Unable to open file\n");
		return;
	}	
	while (fscanf(fp, "%s", temp.tasksList) == 1 ) {
		fscanf(fp, "%d", &temp.priority);
		fscanf(fp, "%d", &temp.hoursList);
		fscanf(fp, "%c", &colon);
		fscanf(fp, "%d", &temp.minutesList);
		if(temp.hoursList < 12) {
        	        fscanf(fp, "%f", &temp.info.budget);	
		} else if (temp.hoursList >= 12 && temp.hoursList <= 20) {
	                fscanf(fp, "%s", temp.info.location);
		} else {
			fscanf(fp, "%d", &temp.info.time[0]);
               		fscanf(fp, "%c", &colon);
       	        	fscanf(fp, "%d", &temp.info.time[1]);
			}
		insert(temp);
	}
	fclose(fp);
	return;
}




void delete_all_nodes() {
	int i;
	for (i = 0; i <3; i++) {
		SCHEDULE *p = heads[i];
        	SCHEDULE *temp = heads[i];
		while (p != NULL) {
			temp = p;
			free(p);
			p = p-> next;
		}
	}	
}
