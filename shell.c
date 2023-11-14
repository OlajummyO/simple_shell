#include "shell.h"

char **parse_command(char *command, int *num_tokens) {
    const char *delim = " \n";
    char *token;
    char **command_argv;
    int i;
    int count = 0;

    /* Count the number of tokens */
    token = strtok(command, delim);
    while (token != NULL) {
        count++;
        token = strtok(NULL, delim);
    }

    /* Allocate space for the array of strings */
    command_argv = malloc(sizeof(char *) * (count + 1));
    if (command_argv == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    /* Copy tokens into the array */
    token = strtok(command, delim);
    for (i = 0; i < count; i++) {
        command_argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(command_argv[i], token);
       	if (command_argv[i] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
       
        token = strtok(NULL, delim);
    }

    /* Null-terminate the array */
    command_argv[count] = NULL;

    /* Update the value of num_tokens */
    *num_tokens = count;

    return command_argv;
}

void free_argv(char **argv) {
   int i;
   if (argv == NULL) {
        return;
    }

    for (i = 0; argv[i] != NULL; i++) {
        free(argv[i]);
    }
    free(argv);
}



int main(void) {
    char *prompt = "(hsh) $ ";
    char *lineptr = NULL;
    char *lineptr_copy = NULL;
    char *token;
    int num_tokens = 0;
    char **command_argv = parse_command(lineptr_copy, &num_tokens); /* Store each token in the command_argv array using parse_command */
   
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int i = 0;
  

    /* Create a loop with a clear exit condition */
    while (1) {
        printf("%s", prompt);

        nchars_read = getline(&lineptr, &n, stdin);

        /* Check if the getline function failed or reached EOF or the user used CTRL + D */
        if (nchars_read == -1) {
            printf("Exiting shell....\n");
            break;  /* Exit the loop on failure*/
        }

        /* Allocate space for a copy of the lineptr */
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL) {
            perror("tsh: memory allocation error");
            break;  /* Exit the loop on failure*/
        }

        /* Copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);

        /* Split the string (lineptr) into an array of words */
        /* Calculate the total number of tokens */
        token = strtok(lineptr, delim);
        while (token != NULL) {
            num_tokens++;
            token = strtok(NULL, delim);
        }

        /* Execute the command */
        execmd(command_argv);

        /* Free up allocated memory */
        free(lineptr_copy);

        /* Reset num_tokens for the next iteration */
        num_tokens = 0;

        /* Free up allocated memory for command_argv */
        for (i = 0; i < num_tokens; i++) {
            free(command_argv[i]);
        }
        free(command_argv);
    }

    /* Free up allocated memory */
    free(lineptr);

    return 0;
}

