/*CITS2002 Project 2018
 * Names: Christian Sivwright, Gemma Irving
 * Student Numbers: 21484775, 21282314
 */

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


struct Node {
	char variable [50];
	char value [50];
	struct Node* prev;
};




//user defined datatype
typedef struct _l{
	char * target;
	char * dependencies; //store as a string and split up later 
	char * action;
	struct _l *next;
} LISTITEM;

//LISTITEM *list=NULL;

//target structure
extern void store_struct(FILE *); //param is not named
extern LISTITEM* store_target(FILE *);
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
extern LISTITEM* find_item(LISTITEM *list, char * targwanted);

//variable expansion file
extern char * handle_expansions(char *);
char * expansion(char *);
int count(char *);

//url mod
char * get_mod1(char *);
extern char * should_rebuild_url(char *);
