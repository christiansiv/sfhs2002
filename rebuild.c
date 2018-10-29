#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>

void rebuild(char * action) { //pass in an individual action line 
	//fork and execute a line of text in the shell 
//pid_t child, parent;

int pid; 
int exitstatus=0;
int status;
char * shell=getenv("SHELL"); //if this doesnt work pass in /bin/bash/
//char actualpath[1000];
//char * path=realpath(file, actualpath);
/*char * buf;
char * cwd;
size_t allocSize=sizeof(char) * 1024;
buf=(char *) malloc(allocSize);
cwd=getcwd(buf, allocSize);
//printf("%s\n", cwd);*/


switch(pid=fork()) {
	case -1:
		printf("fork failed");
		exit(EXIT_FAILURE);
		break;
	case 0: //child

	execl(shell,action, (char *) NULL);

	exit(exitstatus);
	break;
default: //parent
	while ((pid=wait(&status)) >0) { //waiting
		//printf
	}
	exit(exitstatus);
	break;

}



}

//int main(int argc, char *argv[]) {
//	char *anything="mycc -o hellow_orld.c";
//	rebuild(anything);
//	return 0;
//}

