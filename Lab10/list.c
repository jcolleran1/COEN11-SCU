#include "list.h"
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



void listBackwards(SCHEDULE *p) {
	if(p == NULL) {
        	printf("There are no tasks here\n");
		return;
	} else {
		listBackwards(p->next);
	        printf("Priority: %d Task: %s    Time: %d: %02d\n", p->priority, p->tasksList, p->hoursList, p->minutesList);
                pthread_mutex_lock(&mutex);                if (p -> hoursList < 12) {
        	        printf("\nYour Restriction is a budget of %.2f dollars\n", p->info.budget);
                } else if (p -> hoursList >= 12 && p -> hoursList <= 20) {
        		printf("\nYour Restriction is it must be at location: %s\n", p->info.location);
                } else  {
                	printf("\nYour Restriction is it must end by:  %d:%02d\n", p->info.time[0],p->info.time[1]);
                }
        }

}

void lB2 () {
	int i;
	for (i = 0; i < 3; i++) {
		listBackwards(heads[i]);
	}
}




void delete2(){
	int i;
	for (i=0; i < 3; i++) {
		delete_all_nodes(heads[i]);	
	}
}

void delete_all_nodes(SCHEDULE *p) {
	if (p == NULL) {
		return;	
	} else {
		delete_all_nodes(p -> next); 
		free(p);
	}	
}


