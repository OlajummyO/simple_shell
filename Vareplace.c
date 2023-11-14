#include "shell.h"

char *variables[2] = {NULL, NULL}; /* Placeholder for $? and $$*/

char* get_variable_value(char* var) {
    if (strcmp(var, "$?") == 0) {
        return variables[0]; /* Return the exit status*/
    } else if (strcmp(var, "$$") == 0) {
        pid_t pid = getpid();
        sprintf(variables[1], "%d", pid); /* Store PID in variables[1]*/
        return variables[1];
    }
    return NULL;
}

void replace_variables(char *command) {
    char new_command[MAX_COMMAND_LEN];
    char *token = strtok(command, " ");
    while (token != NULL) {
        if (token[0] == '$') {
            char *var_value = get_variable_value(token);
            if (var_value != NULL) {
                strcat(new_command, var_value);
            } else {
                strcat(new_command, token);
            }
        } else {
            strcat(new_command, token);
        }
        strcat(new_command, " ");
        token = strtok(NULL, " ");
    }
    printf("Updated command: %s\n", new_command);
}

void execute_shell_command() {
    char command[MAX_COMMAND_LEN];
    int status = 5; /* Example exit status of last command */
    char exit_status[5]; /* Max digits for $? (usually 3)*/
    strcpy(command, "echo $? $$");
    sprintf(exit_status, "%d", status);
    variables[0] = exit_status;
    variables[1] = (char *)malloc(sizeof(char) * 10); /* Memory for $$*/

    replace_variables(command);

    free(variables[1]); /* Free allocated memory for $$*/
}

/* This function can be called elsewhere in your program
int main() {
    execute_shell_command();
    return 0;
}*/

