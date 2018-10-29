#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdbool.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<string.h>


//user defined datatype
typedef struct _l{
	char * target;
	char * dependencies; //store as a string and split up later 
	char * action;
	struct _l *next;
} LISTITEM;

LISTITEM *list=NULL;

//target structure
extern void store_struct(FILE *); //param is not named
bool is_target(char *);
void trimline(char *);
char* nextline(FILE *);


//variable storage
extern char * find_in_linkedlist(char * line);
void handle_assignment(char *, int);
//void handle_dependency(char *, int);
void handle_line(char *);
void push_to_linkedlist(char*,char*);

//rebuild
extern void rebuild(char *);


//build

//variable expansion file
extern char * handle_expansions(char *);
char * expansion(char *);
int count(char *);

//url mod
char * get_mod1(char *);
extern char * should_rebuild_url(char *);
