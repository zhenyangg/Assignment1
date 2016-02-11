#define INELIGIBLE 0
#define READY 1
#define RUNNING 2
#define FINISHED 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


#define MAX_LENGTH	128
#define MAX_CHILDREN	5

struct Node {
    int id; // corresponds to line number in graph text file
    char prog[MAX_LENGTH]; // prog + arguments
    char input[MAX_LENGTH]; // filename
    char output[MAX_LENGTH]; // filename
    int children[MAX_CHILDREN]; // children ids
    int num_children; // how many children this node has
    int status; // ineligible/ready/running/finished
    pid_t pid; // Process
}; // max 10 processes


// main: open textproc.txt
// separate and store each of the commands somewhere
// use : as delimiter to split the commands
void main() {
	FILE *infile;
	infile = fopen("testproc.txt", "r");

	char str[30];
	int count = 1;
	
	char *ptr;
   	char line [ 128 ]; /* or other suitable maximum line size */
	struct Node nodesArray[10];
	char *token;
	while ( fgets ( line, sizeof line, infile ) != NULL ) /* read a line */
	{
		// parse childIDs to get int array and no. of children

		// ptr[count-1] = (struct Node *) malloc(sizeof(struct Node));
	    	fputs ( line, stdout ); /* write the line */
	    	token = strtok(line, ":");
		strcpy(nodesArray[count-1].prog, token);
		//printf("%s\n", nodesArray[count-1].prog);
	    	
	    	token = strtok(NULL, ":");
		if (strcmp(token, "none") == 0){
			nodesArray[count-1].children[0] = -1;
			//printf("BLAHZ %d\n", nodesArray[count-1].children[0]);
		}
		else {
			int j=0, len, num;
			while (sscanf(token, "%d%n", &num, &len) == 1) {
				nodesArray[count-1].children[j] = num;
				token += len;
				//printf("j = %d, num = %d\n", j, num);
				j++;
			}
			//printf("BLAHZ %d\n", nodesArray[count-1].children[0]);
		}
		
	    	
	    	token = strtok(NULL, ":");
		strcpy(nodesArray[count-1].input, token);
		//printf("%s\n", nodesArray[count-1].input);
	    	
	    	token = strtok(NULL, "\n");
	    	strcpy(nodesArray[count-1].output, token);
		//printf("%s\n", nodesArray[count-1].output);
	    
	    	nodesArray[count-1].id = count;

		count++;
	    	
	};

	printf("No. of commands: %d\n", count-1);
	
	int i;
	for (i=0; i<count-1; i++) {
		printf("%s\n", nodesArray[i].prog);
		if (nodesArray[i].children[0] == -1 ) {
			printf("stu %i\n", nodesArray[i].children[0]);
		}
		else {
			int k;
			for (k=0; k<MAX_CHILDREN; k++) {
				if (nodesArray[i].children[k] != 0 ) {
					printf("%i\n", nodesArray[i].children[k]);
				}
			}
		}
		printf("%s\n", nodesArray[i].input);
		printf("%s\n\n", nodesArray[i].output);
	}
	
	fclose ( infile );
	

	for(int i=0; i<sizeof(nodesArray)/sizeof(nodesArray[0]); i++){
		if(i==0){
			nodesArray[i]->status = READY;
		}
		else{
			nodesArray[i]->status = INELIGIBLE;
		}
	}
	
	/*
	// starting processes
	pid = fork();
	
	if (pid >= 0){ //forking successful
	
	    if (pid == 0) { // child process
	        printf("Child process\n");
	    }
	    
	    else { // parent process
	        printf("Parent process\n");
	    }
	    
	}
	else { printf("Forking failed~\n");
    */
	
	
};



// create a process // parallel processing
// follow the requirements

// output to sink.txt
