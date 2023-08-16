#include	<stdio.h>
#include	<string.h>
#include    <stdlib.h>
#include  "list.h"

int main (int argc, char *argv[]) {
	int option;

        if (argc == 1) {
                printf ("The name of the file is missing!\n");
                return 1;
        }
        read_file (argv[1]);


	while (1) {
		printf ("Option 1: Insert Task\n Option 2: List From Older to Newest\n Option 3: Tasks at a given hour\n Option 4: Delete \n Option 5: List backwards \n Option 0: Quit and saves a text file\nInsert Choice: ");
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
			case 5:
				lB2();
			case 0:
				save_to_file(argv[1]);
				delete2();
				printf("exit");
				return 0;	
				
	
			default:
				printf ("Incorrect button \n");
		}

	}	
}

