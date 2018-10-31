#include "bake.h"


int main(int argc, char* argv[]) {
	//pass in file as argv 
	//store in struct using store struct func - does it need to return the list maybe?
	//then pass that struct into build 
//    char* cwd = NULL;
//    getcwd(cwd, sizeof(cwd));
//    if(cwd == NULL ) {
//        printf("Error getting cwd");
//    }
    char* filename = NULL;
    i_flag = false;
    n_flag = false;
    p_flag = false;
    s_flag = false;
        int i = 0;
        while ((i = getopt(argc, argv, "C:f:inps")) != -1) {
            if (i == 'C') {
                int res = chdir(optarg);
                if (res == false) {
                    printf("CHANGE DIR FAILED\n");
                    exit(EXIT_FAILURE);
                }
            } else if (i == 'f') {
                filename = optarg;
            } else if (i == 'i') {
                i_flag = true;
            } else if (i == 'n') {
                n_flag = true;
            } else if (i == 'p') {
                p_flag = true;
            } else if (i == 's') {
                s_flag = true;
            } else {
                printf("Error in arguments %c",i);
                abort();
            }

        }
        FILE *fp;
        if (filename == NULL) {
             fp = fopen("Bakefile", "r");
            if (fp == NULL) {

                fp = fopen("bakefile","r");
                if (fp == NULL) {
                    perror("Can't find bakefile\n");
                }
            }
        }
        else {
            fp = fopen(filename,"r");
        }


	LISTITEM * list=store_target(fp);
	LISTITEM* p = list;
    if(p_flag) {
        while(p!=NULL) {
            printf("TARGET: %s\n DEPENDENCY %s\n ACTION %s\n",p->target,p->dependencies,p->action);
            p=p->next;
        }
    }
	build(list);


        
        fclose(fp);                     // WE OPENED IT, SO WE CLOSE IT

    return 0;

}

