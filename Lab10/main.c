//      lab 10
//      //      winter 2023
//      //      name: Joshua Colleran
#include  "list.h"

pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER;


int main (int argc, char *argv[]) {
	int option;

        if (argc == 1) {
                printf ("The name of the file is missing!\n");
                return 1;
        }
        read_file (argv[1]);
	pthread_mutex_init(&mutex,NULL);
	pthread_t thread;
	pthread_create(&thread, NULL, autosave, argv[2]);

	while (1) {
		printf ("Option 1: Insert Task\n Option 2: List From Older to Newest\n Option 3: Tasks at a given hour\n Option 4: Delete \n Option 5: List backwards \n Option 6: Show Autosaved list\n Option 0: Quit and saves a text file\nInsert Choice: ");
		scanf ("%d", &option);
		
		switch (option) {
			case 1:
				pthread_mutex_lock(&mutex);
				userInfo();
				pthread_mutex_unlock(&mutex);
				break;

			case 2:
				list();
				break;

			case 3:
				listbytime();
				break;
			
			case 4:
				pthread_mutex_lock(&mutex);
				delete();
				pthread_mutex_unlock(&mutex);
				break;
			case 5:
				pthread_mutex_lock(&mutex);
				lB2();
				pthread_mutex_unlock(&mutex);
				break;
			case 6:
				
                                pthread_mutex_lock(&mutex);
                                binary(argv[2]);
                                pthread_mutex_unlock(&mutex);
				break;

			case 0:
				pthread_mutex_lock(&mutex);
				pthread_cancel(thread);
				pthread_mutex_unlock(&mutex);
				save_to_file(argv[1]);
				delete2();
				return 0;	
				
	
			default:
				printf ("Incorrect button \n");
		}

	}	
}

