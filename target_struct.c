/*CITS2002 Project 2018
 * Names: Christian Sivwright, Gemma Irving
 * Student Numbers: 21484775, 21282314
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "bake.h"


#define CH_CONTINUATION         '\\'

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
;	printf("\n");
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



LISTITEM *find_item(LISTITEM *list, char * targwanted) {
	LISTITEM *p=list;

	while(p!=NULL) {
		if(strcmp(p->target, targwanted) ==0) {
			return p;
		}
		p=p->next;
	}
	return NULL;
}

bool is_target(char *line) //need to test this out
{
	//not really sure how to distinguish these lines as target lines? maybe if they have no equals tab or hash
	//check if they have a ':' 
	
	int length=strlen(line);
	bool target=false;

	for(int i=0; i<length; i++) {
		if(line[i] == ':') {
			target=true;
			break;
		}
	}
	return target;
}

/*char * remove_tab(char * line) {
	int length=strlen(line);
	int count=0;
	
	for(int i=0; i<length; i++) {
		if(line[i]=='	') {
			break;
		}
		count++;
	}
	if(count!=length) {
	for(int i=count; i<length; i++) {
		line[i]=line[i+1];
		}
	}
	return line;
}*/
		


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
        fullline[ --(fulllength) ] = '\0'; // REMOVE TRAILING '\'
    }
   // remove_tab(fullline);
    return fullline;

	
    	
}

//  ----------------------------------------------------------------------

bool is_action(char * line) {
	if(line[0]=='	') {
		return true;
	}
	return false;
}

LISTITEM* store_target(FILE *fp) {
	 while(!feof(fp)) {
		char *line = nextline(fp);
		    //handle_line(line);
	   //handle_expansions(line);
	    //line here for handling variable assignments from other file 
	    //where *line is passed in as param
	    if(is_target(line)) {
		char newtarget[BUFSIZ];
		char dependencies[BUFSIZ];
		int pos=0; //keeps track of line index position
		int length=strlen(line);
		char *dependency=NULL;
		char *target=NULL;
				
		for(int i=0; i<length; i++) {
			if(line[i]==':') {
				break;
			}
			pos++;
		}
		for(int j=0; j<pos; j++) {
			newtarget[j]=line[j]; //target stored in char array for targets
		}
		newtarget[pos]='\0';
		target=realloc(target, strlen(newtarget)+1);
		target=strdup(newtarget);
				pos++; //moves i to next character after the :
		int index=0;
		for(int i=pos; i<length; i++) {
			dependencies[index]=line[i];
			index++;
		}
		dependencies[index]='\0';
		dependency=realloc(dependency, strlen(dependencies)+1);
		dependency=strdup(dependencies);
				//also add in checker for next line that checks it has a tab at the start
		char *actionLine=NULL;

		if(!feof(fp)) {
		char *line2=nextline(fp);
				int fullength=0;
		
		while(is_action(line2)) {
			char *line=strdup(line2);
			//add "|" into line to show where action lines differ
			char a[]="|";
			line=realloc(line, strlen(line)+1);
			line=strcat(line, a);
			fullength+=strlen(line);
			actionLine=realloc(actionLine, fullength+1);
			actionLine=strcat(actionLine, line);
			if(feof(fp)){
				break;
			} else {
			line2=nextline(fp);
			}
		}
		actionLine[--fullength]='\0';
		char *actionLines=strdup(actionLine);
		//line here for handling variable assignment of action line from other
		//file where *act is passed in as param

		
		//add into list
		add_item(target, dependency, actionLines);
		} else {
		char * actionLines=strdup(actionLine);
		add_item(target, dependency, actionLines);
		}


 		//free just line? or line2
		free(line);
	//	free(line2);
	//    free(dependency);
	//    free(target);
	   // free(actionLine);

		
	    }
	   
	    
	 }
	 print_target(list);
	 print_dependency(list);   //just for testing 
	 print_action(list);
	 return list;
 }

//int main(int argc, char *argv[])
//{
//    if(argc > 1) {
//        FILE *fp        = fopen(argv[1], "r");
//
//        if(fp == NULL) {
//            perror(argv[1]);
//            return 1;
//        }
//       /*while(!feof(fp)) {
//            char *line = nextline(fp);  // HANDLES CONTINUATION LINES
//
//            if(line) {
//                printf("%8s()\t%s\n", __func__, line);
//                free(line);
//            }
//       }*/
//	store_target(fp);
//
//        fclose(fp);                     // WE OPENED IT, SO WE CLOSE IT
//    }
//    return 0;
//}


