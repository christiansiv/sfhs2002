#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

FILE * rebuild(char * url) { //pass in an individual action line 
	//fork and execute a line of text in the shell 
//pid_t child, parent;
int pid; 
int exitstatus=0;
int status;
char * shell=getenv("SHELL"); //if this doesnt work pass in /bin/bash/

FILE *fp;
fp=fopen("url_header.txt", "w+"); //creates a file for storing curl header output in
char * string1="curl --head "; 
char * pipe=" <url_header.txt";
char * med_str=NULL;
	med_str=realloc(med_str,strlen(url)+strlen(string1)+1);
	med_str=strcat(string1, url);
char * finalstr=NULL;
	finalstr=realloc(finalstr,strlen(med_str)+strlen(pipe)+1);
	finalstr=strcat(med_str,pipe); //creates a string to pass into command line for exectution

switch(pid=fork()) {
	case -1:
		printf("fork failed");
		exit(EXIT_FAILURE);
		break;
	case 0: //child
	//	printf("%s %s\n", action, cwd);
	execl(shell,finalstr, (char *) NULL);
	//sleep?
	exit(exitstatus);
	break;
default: //parent
	while ((pid=wait(&status)) >0) { //waiting
		//printf
	}
	exit(exitstatus);
	break;

}
return fp; //returns file with url header details
fclose(fp);

}

//func to extract last modified date as a string from curl header details file
char * get_mod(FILE *fp) {
char str[]="Last-Modified: ";
int length0=strlen(str);
char date[BUFSIZ];
char thisline[BUFSIZ];
	while(fgets(thisline, sizeof thisline, fp) != NULL) {
		int length=strlen(thisline);

		for(int i=0; i<length0;i++) {
			if(thisline[i]!=str[i]){
				continue;
			}
		}
		int index=0;
		for(int i=length0+1; i<length; i++) {
			date[index]=thisline[i];
			index++;
		}
	}
	char * last_modified=malloc(strlen(date)+1);
	last_modified=strdup(date);
	return last_modified;
}

/*char * get_mod1(char * line) {
int length=strlen(line);
char str[]="Last-Modified:";
int length0=strlen(str);
bool match=false;
int i=0;

while(line[i]!= NULL) {
	if(line[i]=='L') {
		int index=0;
		for(i; i<length0; i++) {
			if(line[i] != str[index]) {
				continue;
			}
			index++;
		}
		match=true;
		}
	if(match==true) {
		break;
	}
}

char str2[]="GMT";
int length2=strlen(str2);
int j=0;
bool match2=false;
while(line[j]!= NULL) {
	if(line[j]=='G') {
		int index=0;
		for(j; j<length2; j++) {
			if(line[j] != str2[index]) {
				continue;
			}
			index++;
		}
		match2=true;
		}
	if(match2==true) {
		break;
	}
}


char date[BUFSIZ];
int index2=0;

for(i=i+1; i<j-2; i++) {
	date[index2]=line[i];
	index2++;
}
char * mod_date=strdup(date);
return mod_date;
}*/






int main(int argc, char *argv[]) {
	char url[]="http://teaching.csse.uwa.edu.au/units/CITS2002/project/dependency-5m";
	char * urll=malloc(strlen(url)+1);
	urll=strdup(url);
	FILE *fp=rebuild(urll);
	char * mod_date=get_mod(fp);

	printf("%s\n", mod_date);
	
			return 0;

}

