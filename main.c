#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include "command_parser.h"
#include "commands.h"
#include "environment.h"
#include "file_processing.h"
#include "variables.h"
#include "stdio.h"
#include <string.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotAssignable"
typedef enum {
    false = 0, true = 1
} bool;
int n_spaces = 0;

void start(bool read_from_file);

void shell_loop(bool input_from_file);

//char **split(char *enteredLine);

//char *concat(const char *s1, const char *s2);

//char **filter(char **split);

//bool is_change_directory(char str[]);

int main(int argc, char *argv[]) {
    setup_environment();
    // any other early configuration should be here
//    argc = 2;
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
    char *entered_line = buffer;
    char bin_string[512] = "/bin/";
    char filename[256];
//    pid_t pid;
    while (true) {
        if (from_file) {


//            scanf("%[^\n]", filename);
//            FILE *file = fopen(filename, "r");
//            if (file != NULL) {
//
//                char line_from_file[128];
//                while (fgets(line_from_file, sizeof line_from_file, file) != NULL) {
//                    char **array_of_splitted = filter(split(line_from_file));
////                    array_of_splitted[0] = concat(bin_string, array_of_splitted[0]);
//                    for (int i = 0; i < (n_spaces + 1); ++i)
//                        printf("\tres[%d] = %s\n", i, array_of_splitted[i]);
////                    execv(array_of_splitted[0], array_of_splitted);
//
//                }
//                fclose(file);
//            } else {
//                perror(filename);
//            }
//            break;


        } else {
            printf("shell>> ");
            gets(entered_line);
        }

        // split
        char **array_of_splitted = NULL;
        char *p = strtok(entered_line, " ");
        int i;
        while (p) {
            array_of_splitted = realloc(array_of_splitted, sizeof(char *) * ++n_spaces);
            if (array_of_splitted == NULL)
                exit(-1);
            array_of_splitted[n_spaces - 1] = p;
            p = strtok(NULL, " ");
        }
        array_of_splitted = realloc(array_of_splitted, sizeof(char *) * (n_spaces + 1));
        array_of_splitted[n_spaces] = 0;
        // end split

        if (strcmp(array_of_splitted[0], "cd") == 0) {
            printf("%s\n", array_of_splitted[1]);
            printf("chdir = %d\n", chdir(array_of_splitted[1]));
        } else {
            pid_t pid;
            pid = fork();
            if (pid == 0) {
                strcat(bin_string, array_of_splitted[0]);
                printf("%s", bin_string);
                array_of_splitted[0] = bin_string;
                execv(bin_string, array_of_splitted);
                printf("\n");
                exit(0);
            } else {
                wait(0);
                printf("parent\n");
            }
        }

        //execute your command here

        /*
            you don't need to write all logic here, a better practice is to call functions,
            each one contains a coherent set of logical instructions
        */
    }
}

//bool is_change_directory(char str[]) {
//    if (strcmp(str, "cd") == 0)
//        return true;
//    return false;
//}

char **filter(char **split) {
    char **array_of_splitted;
    int initial = 0;
    for (int i = 0; i < n_spaces; i++) {
        if (split[i] == NULL) {
            continue;
        }
        array_of_splitted[initial++] = split[i];
    }
    array_of_splitted[initial++] = NULL;
    printf("%d", initial);
    array_of_splitted = realloc(array_of_splitted, sizeof(char *) * initial);
    return array_of_splitted;
}

//char **split(char *str) {
////    printf("%d", strlen(str));
////    for (int i = 0; i < strlen(str); i++)
////        printf("\n%c\n", str[i]);
//    char **res = NULL;
//    char *p = strtok(str, " ");
//    int i;
//    while (p) {
//        res = realloc(res, sizeof(char *) * ++n_spaces);
//        if (res == NULL)
//            exit(-1);
//        res[n_spaces - 1] = p;
//        p = strtok(NULL, " ");
//    }
//    res = realloc(res, sizeof(char *) * (n_spaces + 1));
//    res[n_spaces] = 0;
//    return res;
//}


//char *concat(const char *s1, const char *s2) {
//    char *result = malloc(strlen(s1) + strlen(s2) + 1);//+1 for the null-terminator
//    //in real code you would check for errors in malloc here
//    strcpy(result, s1);
//    strcat(result, s2);
//    return result;
//}

#pragma clang diagnostic pop