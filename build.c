/*CITS2002 Project 2018
 * Names: Christian Sivwright, Gemma Irving
 * Student Numbers: 21484775, 21282314
 */

#include <ctype.h>
#include "bake.h"

bool check_build_status(LISTITEM *item, LISTITEM *list);
void action_building(char *action);
int file_mod(char *filename);
bool is_url(char *line);


//code for checking the modifcation date of target and dependencies
//
void build(LISTITEM *item) {
    check_build_status(item,item);
}


bool check_build_status(LISTITEM *item, LISTITEM *list) {
    //char*target=list->target;
    char *dependency = item->dependencies;
    char **dep_words = NULL;
    int dep = 0;

    char *med;
    char *temp = strdup(dependency);
    med = strtok(temp, " ");
    //loop that puts each individual dependency into pointer vector
    while (med != NULL) {
        dep_words = realloc(dep_words, (dep + 1) * sizeof(dep_words[0]));
        dep_words[dep] = malloc(sizeof(med));
        int length = strlen(med);
        int index = 0;
        for(int i =0 ; i < length; i++) {
            if (isspace(med[i])) {
                continue;
            }
            else {
                dep_words[dep][index] = med[i];
                index++;
            }
        }
        dep_words[dep][index] = '\0';
        ++dep;

        med = strtok(NULL, " "); //sets the pointer to the next word
    }

    bool rebuild = false;

    for (int i = 0; i < dep; i++) {
	int time = 0;
	if(is_url(dep_words[i])) {
	const char* time_details=should_rebuild_url(dep_words[i]);//returns a string with the date
	struct tm tm;	
	strptime(time_details, "%a:%d:%b:%Y:%H:%M%S", &tm);
	time_t t =mktime(&tm);
	time=(int) t;
	} else {
		
	time=file_mod(dep_words[i]);
        if (time != 0) { // FILE EXISTS
            if (time > file_mod(item->target)) { //dependency is newer so must rebuild;
                rebuild = true;
            } else { //target is newer;
                continue;//so do what?
            }
        } else { // file doesn't exist
            LISTITEM *found = find_item(list, dep_words[i]);
            if (found == NULL) {

                printf("Can't build doesn't exist\n");
                exit(0);
                //We can't build it because it doesn't exist anywhere
            } else {
                // we need to go build it
                check_build_status(found, list);

            }

        }

	}
    }
	free(dep_words);
    action_building(item->action);
    return true;
}


//fork and wait while it completes and then return the 
	//rebuild target passed in 
	//pass action lines to shell 
	//need find_item function from other file
char * remove_tab(char * line) {
	int length=strlen(line);
	
	char new[length];
	int index=0;
	for(int i=0; i<length; i++) {
	if(line[i]=='\t') {
	continue;
	}
	new[index]=line[i];
	index++;
	}
	new[index] = '\0';
	printf("%s\n", new);
	return strdup(new);
}

void action_building(char *action) {
//code for breaking up action lines based upon the "|"
//int length=strlen(action);
char ** actions=NULL;
int act=0;

char *med;
char *temp = strdup(action);
med=strtok(temp, "|");

while(med!=NULL) {
	actions=realloc(actions, (act+1) *sizeof(actions[0]));
	actions[act]=strdup(med);
	++act;

	med=strtok(NULL, "|");
}


for(int i=0; i<act; i++) {
	char * rebuild_me=remove_tab(actions[i]);
	rebuild(rebuild_me);
}
free(actions);

}

//void(char [] action);



//code for returning file modification time as an integer (where the larger the int the more recent the mod time as its counted from epoch 1970 time) from lec 17ish (tested but only with full pathnames?)
char *progname;

int file_mod(char *filename) { //just need to pass in unspecified target/dependency

	struct stat stat_buffer;

	if(stat(filename, &stat_buffer) != 0) { //can we stat the files attributes

		return 0;	
	}
	else if( S_ISREG( stat_buffer.st_mode) ) {
		printf("file was modified on %i\n", (int)stat_buffer.st_mtime);
		printf("which was %s", ctime(&stat_buffer.st_mtime));
	//	int time=(int)stat_buffer.st_mtime;
		return  (int)stat_buffer.st_mtime;

	}
	return 0;
}

int url_modification(char *url); // function to get the modification date of the url
//function for determinining if a dependency is a url

bool is_url(char *line) { //untested
	//int length=strlen(line);

	char hs[]="https://";
	int length1=strlen(hs);

	char f[]="file://";
	int length2=strlen(f);

	char h[]="http://";
	int length3=strlen(h);


	bool first=true; 
	bool second=true;
	bool third=true;

	for(int i=0; i<length1; i++){
		if(line[i]!=hs[i]) {
			first=false;
			break;
		}
	}

		for(int i=0; i<length2; i++){
		if(line[i]!=f[i]) {
			second=false;
			break;
		}
	}
	
		for(int i=0; i<length3; i++){
		if(line[i]!=h[i]) {
			third=false;
			break;
		}
	}
	
	return first || second || third;
}



		


