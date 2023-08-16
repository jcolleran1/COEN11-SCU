#include "list.h"
#include	<stdio.h>
#include	<string.h>
#include        <stdlib.h>

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
