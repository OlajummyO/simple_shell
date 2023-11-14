#include "shell.h"

void execute_commands(char *commands) {
    const char *delimiter = ";";
    char *tokens = strtok(commands, delimiter);

    while (tokens != NULL) {
        /* Token is a command; execute it*/
	int num_token = 0;
        char **argv = parse_command(tokens, &num_token);


        if (argv != NULL) {
            execmd(argv);
            free_argv(argv);
        }

        tokens = strtok(NULL, delimiter);
    }
}
