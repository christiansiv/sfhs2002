#include "bake.h"

//func to count amount of '$' in a line 
int count(char * line) {
	int length=strlen(line);
	int count=0;

	for(int i=0; i<length; i++){
		if(line[i]=='$') {
			count++;
		}
	}
	return count;
}

//func to expand all variables 
//accepts char * and int as paramters
//returns a char * line with variables expanded
char * expansion(char * line) {
	
	int length=strlen(line);
	int start=0;
	int end=0;

	//find start of var expansion
	for(int i=0; i<length; i++) {
		start++;
		if(line[i]=='$') {
			break;
		}
	}
	//find end of var expansion
	for(int i=0; i<length; i++) {
		end++;
		if(line[i]==')') {
			break;
		}
	}
	//find word inside $(word)
	char var[BUFSIZ];
	int index=0; 
	for(int i=start+2; i<end; i++) {
		var[index]=line[i];
		index++;
	}
	//replace w/value
	char * variable=strdup(var);
	char * value=find_in_linkedlist(variable);

	//get first part of string
	char str1[BUFSIZ];
	int index2=0;
	for(int i=0; i<start; i++) {
		str1[index2]=line[i];
		index2++;
	}
	
	//get string remaining after var
	char str2[BUFSIZ];
	int index3=0;
	for(int i=end+1; i<length; i++) {
		str2[index3]=line[i];
		index3++;
	}
	
	//do i need to strcopy var before putting in strcat??
	//put back together and then return char * to final string
	char *str_med=strcat(str1, value);
	char *str_final=strcat(str_med, str2);

	char * expanded=strdup(str_final);
	return expanded;
}


			


//overall function repeats expansion for however many $'s there are
char * handle_expansions(char * line) {
	int counter=count(line);
	char **expanded=NULL;
	int exp=0;
	expanded=realloc(expanded, (exp+1)*sizeof(expanded[0]));
	expanded[exp]=expansion(line);
	exp++;


	for(int i=0; i<counter-1; i++) {
		expanded=realloc(expanded, (exp+1)*sizeof(expanded[0]));
		expanded[exp]=expansion(expanded[i]);
		exp++;
	}

	return expanded[counter-1];
}

int main(int argc, char * argv[]) {
	return 0;
}
