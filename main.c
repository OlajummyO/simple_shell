#include "shell.h"

int main(int ac, char **argv)

{

      	char *prompt = "(hsh) $ ";
  
	char *lineptr = NULL, *lineptr_copy = NULL;
  
	char *token;
 
       	size_t n = 0; 
 
       	ssize_t nchars_read;
 
       	const char *delim = " \n";

      	int num_tokens = 0;
  
	int i = 0;


 	 /* declaring void variables */
 	 (void)ac; 

   	/* create an infinite loop */
    	while (1){
    	
	printf("%s", prompt);
    	
	nchars_read = getline(&lineptr, &n, stdin);
    

  	/* check if the getline function failed or reached EOF or user use CTRL + D */ 
        
	if (nchars_read == -1){
            printf("Exiting shell....\n");
            return (-1);
        }

	
	/*allocate space for a copy of the lineptr */
	lineptr_copy = malloc(sizeof(char) * nchars_read);
	if (lineptr_copy== NULL){
		perror("tsh: memrory allocation error");
		return (-1);
	}


	/* copy lineptr to lineptr_copy*/
	strcpy(lineptr_copy, lineptr);


	/* split the string (lineptr) into an array of words*/
	/*  calculate the total number of tokens */
	token = strtok(lineptr, delim);

	while (token != NULL){
		
		num_tokens++;
		
		token = strtok(NULL, delim);
	}

	num_tokens++;

	
	/* Allocate space to hold the arry of strings */
	argv = malloc(sizeof(char *) * num_tokens);



	/* store each token in the argv array */
	token = strtok(lineptr_copy, delim);


	for (i = 0; token != NULL; i++){
		
		argv[i] = malloc(sizeof(char) * strlen(token));
		
		strcpy(argv[i], token);

		token = strtok(NULL, delim);
	}

	
	argv[i] = NULL;
	
	/*execute the command*/
	
	execmd(argv);

	}

      	/* free up allocated memory */
     	free(lineptr);    
	free(lineptr);


	return (0);

}
