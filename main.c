#include <memory.h>
#include <stdlib.h>
#include "command_parser.h"
#include "commands.h"
#include "environment.h"
#include "file_processing.h"
#include "variables.h"
#include "stdio.h"

typedef enum {
    false = 0, true = 1
} bool;

void start(bool read_from_file);

void shell_loop(bool input_from_file);

char **split(char *enteredLine);

int main(int argc, char *argv[]) {
    setup_environment();
    // any other early configuration should be here

    if (argc > 1) {
        start(true);
    } else {
        start(false);
    }

    return 0;
}

void start(bool read_from_file) {
    cd(""); // let shell starts from home

    if (read_from_file) {
        // file processing functions should be called from here

        shell_loop(true);
    } else {
        shell_loop(false);
    }
}

void shell_loop(bool input_from_file) {
    bool from_file = input_from_file;
    char buffer[256];
    char *enteredLine = buffer;

    while (true) {
        if (from_file) {
            //read next instruction from file

            // if end of file {from_file = false; continue;}
        } else {
            printf("enter\n");
            scanf("%[^\n]", enteredLine);
            char **res = split(enteredLine);
            for (int i = 0; i < (5 + 1); ++i)
                printf("res[%d] = %s\n", i, res[i]);
            break;
        }

        //parse your command here

        //execute your command here

        /*
            you don't need to write all logic here, a better practice is to call functions,
            each one contains a coherent set of logical instructions
        */
    }
}


char **split(char *str) {
    char **res = NULL;
    // pointer to a pointer to a char
    // since pointer to a char is equivalent to a string
    // therefore it is a pointer to string!
    char *p = strtok(str, " ");
    int n_spaces = 0, i;


/* split string and append tokens to 'res' */

    while (p) {
        res = realloc(res, sizeof(char *) * ++n_spaces);

        if (res == NULL)
            exit(-1); /* memory allocation failed */

        res[n_spaces - 1] = p;

        p = strtok(NULL, " ");
    }

/* realloc one extra element for the last NULL */

    res = realloc(res, sizeof(char *) * (n_spaces + 1));
    res[n_spaces] = 0;

    return res;
}