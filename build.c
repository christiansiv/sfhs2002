//File to check if targets need building and if they do execute them
//iterate through list:
//FOREACH target
//->retrieve dependencies line from list and break into pointer vector of dependencies
//FOR EACH DEPENDENCY
////->if number of dependencies =0 rebuild
//->if there are dependencies first: ->classify them 
//----->(1) dependency that identifies existing files on disk
//----->(2) dependency that is another target 
//----->(3)dependency is a url (if a dependency looks like an simple URL (it commences with the pattern file://, http://, or https://))
//->get the modification date of target and compare against each of its dependencies
//-> if any dep mod date is more recent REBUILD or if any dep doesnt exist REBUILD otherwise cont.

//how to start?
//->have a function that passes in the linked list
//->have a loop that rotates through each node of the linked list??
//

//code for breaking up dependencies (tested)
		char *med;  
		med=strtok(str, " "); //set whatever string u want
		//loop that puts each individual dependency into pointer vector
		while(med!=NULL) {
		//	printf("%s\n", med); //prints out the the current word its pointing too
		//	do something with curr word here or just put into a pointer vector
			med=strtok(NULL, " "); //sets the pointer to the next word
			}



