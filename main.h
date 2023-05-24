#ifndef MAIN_H
#define MAIN_H

char **strtokarray(char *str);
void _which(char *str);
void shell_nonint(char **env);
void shell_interactive(char **env);
void execute(char *command, char **env);
#endif
