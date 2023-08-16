
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
void listBackwards(SCHEDULE *p);
void lB2();
void delete2();
