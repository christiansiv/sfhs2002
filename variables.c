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
    if (curr == NULL) {
        curr = (struct Node*) malloc(sizeof(struct Node));
        curr->prev = NULL;
    }

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
     char* cwd = NULL;
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

    char *variable = malloc(sizeof(char * ));
    char *value = malloc(sizeof(char *));

    int index = 0;

    for (int j = 0; j<i;j++){
        current = line[j];

        if(isspace(current)) {
            if (isspace(line[j + 1]) || (j + 1 == index)) {
                continue;
            }
        }
        else {
            variable = realloc(variable, index+1 * sizeof(*variable));
            variable[index] = line[j];
            index++;
        }
    }
    variable = realloc(variable, index * sizeof(*variable));
    variable[index] = '\0';
    int length = strlen(line);
    index = 0;
    for(int j = i+1;j<length; j++) {
        current = line[j];
        if ((isspace(current) && isspace(line[j+1])) || (isspace(current) && index == 0)) {// remove whitespace
            continue;
        }
        value = realloc(value, index+1 * sizeof(*value));
        value[index] = line[j];
        index++;
    }
    value = realloc(value, index * sizeof(*value));
    value[index] = '\0';
    push_to_linkedlist(variable, value);
    free(variable);
    free(value);


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

