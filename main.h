#ifndef MAIN_H
#define MAIN_H

char **strtokarray(char *str, char *delim);
void _which(char *str);
void shell_interactive(char *av, char **env);
int execute(char *command, char *av, char **env, int count);
#endif
