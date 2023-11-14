#include "shell.h"

void some_builtin_function(void) {
    char *prompt = "(simple_shell) $ ";
    char *lineptr = NULL;
    char *token;
    char *delim = " ";
    int num_tokens = 0;
    char **argv = malloc(sizeof(char *) * (num_tokens + 1));
    size_t n = 0;
    ssize_t nchars_read;
    int i;

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
            if (strcmp(argv[0], "cd") == 0) {
                /* Handle the cd command*/
                if (num_tokens == 1) {
                    
		/* No argument provided, interpret as cd $HOME */
                  char *home = getenv("HOME");
                  if (home != NULL) {
                        chdir(home);
                        setenv("PWD", home, 1);
                    } else {
                        fprintf(stderr, "HOME environment variable not set.\n");
                    }
                } else if (strcmp(argv[1], "-") == 0) {
                    /* Handle cd -*/
                    char *old_pwd = getenv("OLDPWD");
                    if (old_pwd != NULL) {
                        chdir(old_pwd);
                        setenv("PWD", old_pwd, 1);
                    } else {
                        fprintf(stderr, "OLDPWD not set.\n");
                    }
                } else {
                    /* Handle cd with an argument*/
                    if (chdir(argv[1]) == 0) {
                        char *cwd = getcwd(NULL, 0);
                        setenv("PWD", cwd, 1);
                        free(cwd);
                    } else {
                        perror("cd");
                    }
                }
            } else if (strcmp(argv[0], "setenv") == 0) {
                /* Handle the setenv command*/
                /* ...*/
            } else if (strcmp(argv[0], "unsetenv") == 0) {
                /* Handle the unsetenv command*/
                /* ...*/
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
        for (i = 0; i < num_tokens; i++) {
            free(argv[i]);
        }
        free(argv);
    }

    /* Free allocated memory for lineptr */
    free(lineptr);

 
}
