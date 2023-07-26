#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_COMMAND_LENGTH 100
#define BUFFER_LEN 1024

extern char **environ;

char *concat_all(char *s1, char *s2);
char *find_path(char *av);
char **split_line(char *line, int bufsize);
int check_builtin(char *argvv);
void print_env(void);
void builtins(char **argvv, int i);
void exec_command(char **argvv);
void __exit(char **argvv);
void change_dir(char **argvv);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
int _strlen(char *s);
char *read_line();
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenv(char *env);

// void prompt();  note: this function is not used
// void execute(char *command); **

#endif // MAIN_H