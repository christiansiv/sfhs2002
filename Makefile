mycc = cc -std=c99 -Wall -Werror -pedantic

bakefile : bake.o variables.o rebuild.o variable_expansion.o target_struct.o build.o url_mod_date.o
	$(mycc) -o bakefile bake.c variables.c variable_expansion.c target_struct.c build.c url_mod_date.c rebuild.c

bake.o : bake.c variables.o variable_expansion.o target_struct.o rebuild.o build.o url_mod_date.o
	$(mycc) -c bake.c variables.c variable_expansion.c target_struct.c build.c url_mod_date.c

variables.o : variables.c bake.h
	$(mycc) -c variables.c

rebuild.o : rebuild.c bake.h
	$(mycc) -c rebuild.c

variable_expansion.o : variable_expansion.c variables.o bake.h
	$(mycc) -c variable_expansion.c variables.c

target_struct.o : target_struct.c variables.o variable_expansion.o bake.h
	$(mycc) -c target_struct.c variables.c variable_expansion.c

build.o : build.c variable_expansion.o variables.o target_struct.o rebuild.o url_mod_date.o bake.h
	$(mycc) -c build.c variable_expansion.c variables.c target_struct.c rebuild.c url_mod_date.c

url_mod_date.o : url_mod_date.c
	$(mycc) -c url_mod_date.c