#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

char * get_mod1(char * line) {
int length=strlen(line);
//printf("%d\n", length);
char str[]="Last-Modified:";
int length0=strlen(str);
bool match=true;
int traverse=0;
int pos1=0;
int pos2=0;

while(length != traverse) {
//	printf("%s\n", "here"); gets here
	
	if(line[traverse]=='L') {
	//	printf("%s\n", "here");

		pos1=traverse;
		int index=0;
		for(int i=pos1; i<length0; i++) {
			if(line[i] != str[index]) {
				match=false;
			}
			printf("%s\n", "here2");

			index++;
		}
	//	printf("%s\n", "here");
		
	if(match==true) {
		break;
	}
	}
	traverse++;
	}
//printf("%d\n", pos1);
char str2[]="GMT";
int length2=strlen(str2);
int traverse2=pos1;

bool match2=true;
while(length!=traverse2) {
	if(line[traverse2]=='G') {
		pos2=traverse2;
		int index=0;
		for(int j=pos2; j<length2; j++) {
			if(line[j] != str2[index]) {
				match2=false;
			}
			index++;
		}
		
	if(match2==true) {
		break;
	//	printf("%s\n", "here3");

	}
	
	}
	traverse2++;


}
//printf("%d\n", pos2);
char date[BUFSIZ];
int index2=0;

for(int i=pos1+length0+1; i<pos2+3; i++) {
	date[index2]=line[i];
	index2++;
}
printf("%s\n", date);
char * mod_date=strdup(date);
return mod_date;
}

char * should_rebuild_url(char* url) {

    char    readbuffer[255];

    pid_t child_pid;
    //int child_status;
    char *argv[4];
    int fd[2];
    pipe(fd);
    argv[0] = "curl";
    argv[1] = "-I";
    argv[2] = "https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm";
    argv[3] = NULL;
    child_pid = fork();
    if (child_pid == 0) {
        //Child Process

        dup2(fd[1],STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);
        execvp(argv[0], argv);

        printf("Unknown command\n");
        exit(0);
    } else if (child_pid == -1) {
        printf("Failed to fork\n");
        exit(1);
    }
    else {
        close(fd[1]);
        int nbytes = 0;
        char *totalStr = malloc(1);
        while(0 !=(nbytes=read(fd[0], readbuffer,sizeof(readbuffer)))) {
            //printf("%s\n",readbuffer);
            //char * temp = (char *) malloc(sizeof(totalStr));
            //strcpy(temp,totalStr);
            totalStr = (char *) realloc(totalStr, sizeof(readbuffer)+sizeof(totalStr));
            strcat(totalStr,readbuffer);
        }
        wait(NULL);
       	printf("%s\n",totalStr);
       //TODO: TOTAL STR CONTAINS THE ANSWER
	char * string=get_mod1(totalStr);
	printf("%s\n",string);

	return string;

    }
    }

int main(int argc, char *argv[]) {
	char url[]="http://teaching.csse.uwa.edu.au/units/CITS2002/project/dependency-5m";
	char * urll=malloc(strlen(url)+1);
	urll=strdup(url);

	char * check=should_rebuild_url(urll);
	printf("%s\n", check);
	return 0;
}


