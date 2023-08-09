#include "list.h"

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

void *autosave(void *arg) {
        char *filename = (char*)arg;
        int i;
        SCHEDULE *p;
        FILE *fp;
        while (1) {
                pthread_mutex_lock(&mutex);
                fp =fopen(filename, "wb");
                for (i = 0; i<3; i++) {
                        p = heads[i];
                        while (p != NULL) {
                                fwrite(p, sizeof(SCHEDULE), 1, fp);
                                p = p -> next;
                        }
                }
                fclose(fp);
                pthread_mutex_unlock(&mutex);
                sleep(5);
        }
}

void binary(char *arg) {
        char *filename = (char*)arg;
        SCHEDULE p;
        FILE *fp;
	fp = fopen(filename, "rb");
        while (0 < fread(&p,sizeof (SCHEDULE), 1,fp)) {
	        printf("%s %d %d:%.02d ", p.tasksList, p.priority, p.hoursList, p.minutesList);
                if (p.hoursList < 12) {
                	printf("%.2f\n", p.info.budget);
                } else if (p.hoursList >= 12 && p.hoursList <= 20) {
                        printf("%s\n", p.info.location);
                } else if (p.hoursList > 20) {
                        printf("%d:%d\n", p.info.time[0], p.info.time[1]);
                }
	}
	fclose(fp);
	return;
}




