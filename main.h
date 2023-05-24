#ifndef MAIN_H
#define MAIN_H

char **strtokarray(char *str, char *delim);
void _which(char *str);
void shell_nonint(char *av, char **env);
void shell_interactive(char *av, char **env);
void execute(char *command, char *av, char **env, int count);
#endif
