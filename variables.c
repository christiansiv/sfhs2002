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
#include <math.h>
#include "bake.h"

#if defined(__linux__)
extern  char    *strdup(const char *str);
#endif

#define CH_CONTINUATION         '\\'
struct Node *curr = NULL;

// Make function to add elements to my linked list
void push_to_linkedlist(char* variable, char* value) {
    // Add to linked list
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->prev = curr;
    new_node->variable = strdup(variable);
    new_node->value =strdup(value);
    curr = new_node;

}

// Make function to search the list and return the value for the variable
char* find_in_linkedlist(char* value) {
    //CHECK IF VALUE IS ANY SPECIAL CASE. I.E PID PPID RAND
    int special = 0;

 if (strcmp(value, "PID")) {
     special = getpid();
     char *specialStr = malloc(sizeof(char) * (int) log10(special));
     return specialStr;
} else if (strcmp(value,"PPID")) {

     special = getppid();
     char *specialStr = malloc(sizeof(char) * (int) log10(special));
     return specialStr;

} else if (strcmp(value, "PWD")) {
     char* cwd;
     if (getcwd(cwd, sizeof(cwd)) != NULL) {
         printf("Current working dir: %s\n", cwd);
         return cwd;
     } else {
         perror("getcwd() error");
         return "";
     }


} else if ( strcmp(value,"RAND")) {

     special = rand();
     char *specialStr = malloc(sizeof(char) * (int) log10(special));
     return specialStr;
 }

 else {


    struct Node *temp = curr;
    while( temp-> prev != NULL) {
        if( strcmp(value, temp->value)){
            return temp->value;
        }
        temp = temp->prev;
    }
}

    //NOW CHECK ENV VARIABLES
    char * s = getenv(value);
    if ( s!=NULL) {
        return s;
    }
    //OTHERWISE RETURN EMPTY STRING
    return "";


}

void handle_assignment(char* line, int i) {
    char current;
    char *variable = malloc(sizeof(line));
    char *value = malloc(sizeof(line));

    int index = 0;

    for (int j = 0; j<i;j++){
        current = line[j];

        if(isspace(current)) {
            if (isspace(line[j + 1]) || (j + 1 == index)) {
                continue;
            }
        }
        else {


            variable[index] = line[j];
            index++;
        }
    }
    int length = strlen(line);
    index = 0;
    for(int j = i+1;j<length; j++) {
        current = line[j];
        if ((isspace(current) && isspace(line[j+1])) || (isspace(current) && index == 0)) {// remove whitespace
            continue;
        }

        value[index] = line[j];
        index++;
    }

    push_to_linkedlist(variable, value);
    //free(variable);
    //free(value);


}

//void handle_dependency(char* line,int i) 
    //Check if things have been built, if they haven't been built read down

void handle_line(char* line) {
    printf("%s",line);
    int length = strlen(line);

    if (line[0] == '\n') {
        return;

    } else if (line[0] == '#') {

        return;
    } else if (line[0] == '\t') {
        return;
    } else {

        for (int i = 0; i < length; i++) {

            if (line[i] == '=') { //and theres no tab at the start as action lines also have equals
                handle_assignment(line, i);
                break;
            } 

        }
    }
}

//read in each line and work out what form of line it is
//e.g. (a) comment line (b) variable assignment (c) action line (d) target line
//void line_form(FILE *fp) {
//
//    char        *fullline       = NULL;
//    int         fulllength      = 0;
//
//    char        line[BUFSIZ];
//    int         thislength      = 0;
//    //Read each line of the file
//    while (fgets(line, sizeof line, fp) != NULL) {
//        trimline(line);
//        thislength      = strlen(line);
//
//
//        int length = strlen(line);
//
//        if (line[0]=='\n'){
//            continue;
//
//        } else if (line[0] == '#') {
//
//            continue;
//
//        } else if (line[length - 2] == '\\') {
//
//            // if line ends in a \ we want to get the contents of the next string and add it to the current string
//            //char* temp = sizeof(line);
//            //strcpy(line,temp);
//            if (fgets(line,sizeof line, fp) != NULL) {
//
//            }
//            else {
//                printf("Error on line %d",lineNumber);
//            }
//
//
//        } else if (line[0] == 9) {
//            // This is an action line
//            printf("Action line!\n");
//
//        } else {
//
//            for (int i = 0; i < length; i++) {
//
//                if (line[i] == '='){
//                    handle_assignment(line,i);
//                    break;
//                } else if( line[i] == ':') {
//                    handle_dependency(line,i);
//                }
//
//
//
//            }
//
//        }
//
//    lineNumber++;
//    }
//}


////  DEVELOPED IN LECTURE 9  (but here using pointers) //  Written by Chris.McDonald@uwa.edu.au, September 2018
//void trimline(char *line)
//{
//    while(*line != '\0') {      //  loop until we reach the end of line
//        if( *line == '\n' || *line == '\r' ) {
//            *line = '\0';       // overwrite with null-byte
//            break;              // leave the loop early
//        }
//        ++line;                 // iterate through characters on line
//    }
//}

//  READ SUCCESSIVE LINES UNTIL END-OF-FILE OR ONE DOES NOT END WITH '\' //  Written by Chris.McDonald@uwa.edu.au, September 2018
//char *nextline(FILE *fp)
//{
//    char        *fullline       = NULL;
//    int         fulllength      = 0;
//
//    char        thisline[BUFSIZ];
//    int         thislength      = 0;
//
//    while(fgets(thisline, sizeof thisline, fp) != NULL) {
//        trimline(thisline);                     // REMOVE TRAILING \n or \r
//        thislength      = strlen(thisline);
//        fulllength      += thislength;
//
//        //printf("%8s()\t%s\n", __func__, thisline);
//
//        if(fullline == NULL) {
//            fullline    = strdup(thisline);
//        }
//        else {
//            fullline     = realloc(fullline, fulllength+1);
//            strcat(fullline, thisline);
//        }
////  SHOULD WE CONTINUE READING, OR IS THE LINE COMPLETE?
//        if(fullline[ fulllength-1 ] != CH_CONTINUATION) {
//            break;
//        }
//        fullline[ --fulllength ] = '\0';        // REMOVE TRAILING '\'
//    }
//    return fullline;
//}

//  ----------------------------------------------------------------------

//int main(int argc, char *argv[])
//{
//    curr = (struct Node*) malloc(sizeof(struct Node));
//    curr->prev = NULL;
//    if(argc > 1) {
//        FILE *fp        = fopen(argv[1], "r");
//
//        if(fp == NULL) {
//            perror(argv[1]);
//            return 1;
//        }
//        while(!feof(fp)) {
//            char *line = nextline(fp);  // HANDLES CONTINUATION LINES
//
//            if(line) {
//                //printf("%8s()\t%s\n", __func__, line);
//                handle_line(line);
//                free(line);
//            }
//        }
//        fclose(fp);                     // WE OPENED IT, SO WE CLOSE IT
//    }
//    return 0;
//}
