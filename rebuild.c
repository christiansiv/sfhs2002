
#include "bake.h"

void rebuild(char * action) { //pass in an individual action line 
	//fork and execute a line of text in the shell 
//pid_t child, parent;

int pid; 
int exitstatus=0;
int status;
char * temp = strdup(action);
//char * shell=getenv("SHELL"); //if this doesnt work pass in /bin/bash/
//char actualpath[1000];
//char * path=realpath(file, actualpath);
/*char * buf;
char * cwd;
size_t allocSize=sizeof(char) * 1024;
buf=(char *) malloc(allocSize);
cwd=getcwd(buf, allocSize);
//printf("%s\n", cwd);*/

	char * tok;

	char **action_list = NULL;
	int num = 0;

switch(pid=fork()) {
	case -1:
		printf("fork failed\n");
		exit(EXIT_FAILURE);
		break;
	case 0: //child

	if (temp[0] == '@' || s_flag) {

	} else {
		printf("%s\n",temp);
	}
	tok = strtok(temp, " \t");

	while(tok!=NULL) {
		//printf("%s\n",tok);
		action_list = realloc(action_list, (num+1) * sizeof(action_list[0]));
		action_list[num] = strdup(tok);
		++num;
		tok = strtok(NULL, " \t");
	}
	action_list[num] = "\0";


	execvp(action_list[0],action_list);
	printf("ISSUE WITH ACTION\n");
	exit(exitstatus);
	break;
default: //parent
	while ((pid=wait(&status)) >0) { //waiting
		//printf
	}
	return;

}



}

//int main(int argc, char *argv[]) {
//	char *anything="mycc -o hellow_orld.c";
//	rebuild(anything);
//	return 0;
//}

