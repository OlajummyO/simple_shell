#include "shell.h"

int main(void) {
    char *prompt = "(simple_shell) $ ";
    char *lineptr = NULL;
    char *token;
    char *delim = " ";
    char **argv = malloc(sizeof(char *) * (num_tokens + 1));
    int num_tokens = 0;
    size_t n = 0;
    ssize_t nchars_read;


    while (1) {
        printf("%s", prompt);

        nchars_read = getline(&lineptr, &n, stdin);

        /* Check for end of file (Ctrl+D) or error in getline */
        if (nchars_read == -1 || feof(stdin)) {
            printf("Exiting shell....\n");
            free(lineptr);
            break;
        }

        /* Remove the newline character at the end of the input */
        if (lineptr[nchars_read - 1] == '\n') {
            lineptr[nchars_read - 1] = '\0';
        }

        /* Tokenize the input */
        token = strtok(lineptr, delim);

 
       while (token != NULL) {
            argv = realloc(argv, sizeof(char *) * (num_tokens + 1));
            argv[num_tokens] = strdup(token);

            if (argv[num_tokens] == NULL) {
                perror("Error: memory allocation failed");
                exit(EXIT_FAILURE);
            }

            num_tokens++;
            token = strtok(NULL, delim);
        }

        argv[num_tokens] = NULL;

        /* Execute the command */
        if (num_tokens > 0) {
            if (strcmp(argv[0], "setenv") == 0) {
                int success;
                if (num_tokens == 3) {
                    success = setenv(argv[1], argv[2], 1);
                    if (success != 0) {
                        fprintf(stderr, "Failed to set environment variable %s\n", argv[1]);
                    }
                } else {
                    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                }
            } else if (strcmp(argv[0], "unsetenv") == 0) {
                int success;
                if (num_tokens == 2) {
                    success = unsetenv(argv[1]);
                    if (success != 0) {
                        fprintf(stderr, "Failed to unset environment variable %s\n", argv[1]);
                    }
                } else {
                    fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                }
            } else {
                char *command = get_path(argv[0]);

                if (command != NULL) {
                    execvp(command, argv);
                } else {
                    fprintf(stderr, "Command not found: %s\n", argv[0]);
                }
            }
        }

        /* Free allocated memory for argv */
        for (int i = 0; i < num_tokens; i++) {
            free(argv[i]);
        }
        free(argv);
    }

    /* Free allocated memory for lineptr */
    free(lineptr);

    return 0;
}

