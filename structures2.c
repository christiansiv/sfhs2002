#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#define CH_CONTINUATION         '\\'


//PLan
//use nextline code by calling it twice to retrieve target/dependencies line and then action line which will also have the appending part sorted out (only thing to look at is that it doesn't get rid of the tab so the line will have a weird gap)
//work out how to expand variables as you read in the lines
//split up dep and targets by colon and store in structure as char arrays (split up dependency later)
//???

//make a list for storing target stuff

typedef struct _l{
	char * target;
	char * dependencies; //store as a string and split up later 
	char * action;
	struct _l *next;
} LISTITEM;

LISTITEM *list=NULL;

void add_item(char * targ, char * deps,char *act) { 
	if(list == NULL) {
		list=malloc(sizeof(LISTITEM));
		if(list == NULL) {
			perror("add_item");
			exit(EXIT_FAILURE);
		}
		list->target=strdup(targ); 
		list->dependencies=strdup(deps); 
		list->action=strdup(act);
		list->next=NULL;
	}
	else {				
		LISTITEM *p=list;

		while(p->next !=NULL) {	//traverse to end of list
			p= p->next;
		}
		p->next = malloc(sizeof(LISTITEM));
		if(p->next == NULL) {
			perror("this did not work");
			exit(EXIT_FAILURE);
		}
		p=p->next;
		p->target=strdup(targ);
		p->dependencies=strdup(deps);
		p->action=strdup(act);
		p->next=NULL;
	}
}

void print_target(LISTITEM *list)
{
    LISTITEM	*p = list;

    while(p != NULL) {
	printf("%s", p->target);
	if(p->next != NULL)
	    printf(" -> ");
	p	= p->next;
    }
    if(list != NULL)
	printf("\n");
}

void print_dependency(LISTITEM *list)
{
    LISTITEM	*p = list;

    while(p != NULL) {
	printf("%s", p->dependencies);
	if(p->next != NULL)
	    printf(" -> ");
	p	= p->next;
    }
    if(list != NULL)
	printf("\n");
}

void print_action(LISTITEM *list)
{
    LISTITEM	*p = list;

    while(p != NULL) {
	printf("%s", p->action);
	if(p->next != NULL)
	    printf(" -> ");
	p	= p->next;
    }
    if(list != NULL)
	printf("\n");
}



bool find_item(LISTITEM *list, char * targwanted) {
	LISTITEM *p=list;

	while(p!=NULL) {
		if(strcmp(p->target, targwanted) ==0) {
			return true;
		}
		p=p->next;
	}
	return false;
}

bool is_target(char *line) //need to test this out
{
	//not really sure how to distinguish these lines as target lines? maybe if they have no equals tab or hash
	//check if they have a ':' 
	
	int length=strlen(line);
	bool target=false;

	for(int i=0; i<length-1; i++) {
		if(line[i] == 58) {
			target=true;
			break;
		}
	}
	return target;
}


//  DEVELOPED IN LECTURE 9  (but here using pointers)
void trimline(char *line)
{
    while(*line != '\0') {      //  loop until we reach the end of line
        if( *line == '\n' || *line == '\r' ) {
            *line = '\0';       // overwrite with null-byte
            break;              // leave the loop early
        }
        ++line;                 // iterate through characters on line
    }
}

//  READ SUCCESSIVE LINES UNTIL END-OF-FILE OR ONE DOES NOT END WITH '\'
char *nextline(FILE *fp)
{
    char        *fullline       = NULL;
    int         fulllength      = 0;

    char        thisline[BUFSIZ];
    int         thislength      = 0;

    while(fgets(thisline, sizeof thisline, fp) != NULL) {
        trimline(thisline);                     // REMOVE TRAILING \n or \r
        thislength      = strlen(thisline);
        fulllength      += thislength;

        printf("%8s()\t%s\n", __func__, thisline);

        if(fullline == NULL) {
            fullline    = strdup(thisline);
        }
        else {
            fullline     = realloc(fullline, fulllength+1);
            strcat(fullline, thisline);
        }
//  SHOULD WE CONTINUE READING, OR IS THE LINE COMPLETE?
        if(fullline[ fulllength-1 ] != CH_CONTINUATION) {
            break;
        }
        fullline[ --fulllength ] = '\0';        // REMOVE TRAILING '\'
    }
    return fullline;
}

//  ----------------------------------------------------------------------

void store_target(FILE *fp) {
	 while(!feof(fp)) {
            char *line = nextline(fp);
	    //line here for handling variable assignments from other file 
	    //where *line is passed in as param
	    if(is_target(line)) {
		char newtarget[50];
		char dependencies[1000];
		int pos=0; //keeps track of line index position
		int length=strlen(line);
		
		for(int i=0; i<length; i++) {
			if(line[i]==':') {
				break;
			}
			pos++;
		}
		for(int j=0; j<pos; j++) {
			newtarget[j]=line[j]; //target stored in char array for targets
		}
		char *target=strdup(newtarget);
		pos++; //moves i to next character after the :
		int index=0;
		for(int i=pos; i<length; i++) {
			dependencies[index]=line[i];
			index++;
		}
		char *dependency=strdup(dependencies);
		
		//also add in checker for next line that checks it has a tab at the start
		char *line2=nextline(fp);
		//line here for handling variable assignment of action line from other
		//file where *act is passed in as param
		
		//add into list
		add_item(target, dependency, line2);

		//free just line? or line2
		free(line);
	//	free(line2);
		
	    }
	    
	 }
	 print_target(list);
	 print_dependency(list);   //just for testing 
	 print_action(list);

}


int main(int argc, char *argv[])
{
    if(argc > 1) {
        FILE *fp        = fopen(argv[1], "r");

        if(fp == NULL) {
            perror(argv[1]);
            return 1;
        }
       /*while(!feof(fp)) {
            char *line = nextline(fp);  // HANDLES CONTINUATION LINES

            if(line) {
                printf("%8s()\t%s\n", __func__, line);
                free(line);
            }
       }*/
	store_target(fp);
        
        fclose(fp);                     // WE OPENED IT, SO WE CLOSE IT
    }
    return 0;
}

//tweaking for my use?
//while loop that checks if the line is a target and if it is calls it again to get the action line
//only thing to consider is how will the loop operate?
//should work doing same thing as main function here even if nextline is called twice because the fp is altered in the nextline function(must be otherwise doing it once wouldnt do anything either
//free memory allocation for both lines at the bottom 
//OK HERE WE GO FELLAS
//
