#include "bake.h"

int main(int argc, char* argv[]) {
	//pass in file as argv 
	//store in struct using store struct func - does it need to return the list maybe?
	//then pass that struct into build 
	
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
	LISTITEM * list=store_target(fp);

	build(list);


        
        fclose(fp);                     // WE OPENED IT, SO WE CLOSE IT
    }
    return 0;

}

