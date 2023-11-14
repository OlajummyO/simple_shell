#include "shell.h"

struct Alias {
    char name[MAX_ALIAS_LEN];
    char value[MAX_ALIAS_LEN];
};

struct Alias aliases[MAX_ALIASES];
int alias_count = 0;

void print_alias(char *name) {
    int i;
    for (i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
    printf("Alias not found: %s\n", name);
}

void list_aliases() {
    int i;
    for (i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void add_alias(char *name, char *value) {
    int i;
    for (i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            strcpy(aliases[i].value, value);
            return;
        }
    }
    if (alias_count < MAX_ALIASES) {
        strcpy(aliases[alias_count].name, name);
        strcpy(aliases[alias_count].value, value);
        alias_count++;
    } else {
        printf("Maximum alias limit reached.\n");
    }
}

void alias_operations(int argc, char *argv[]) {
    int i;
    if (argc == 1) {
        list_aliases();
    } else if (argc == 2) {
        print_alias(argv[1]);
    } else {
        for (i = 1; i < argc; i++) {
            char *name = strtok(argv[i], "=");
            char *value = strtok(NULL, "=");
            if (value == NULL) {
                print_alias(name);
            } else {
                add_alias(name, value);
            }
        }
    }
}

/* Sample Usage
int main(int argc, char *argv[]) {
    alias_operations(argc, argv);
    return 0;
}
*/

