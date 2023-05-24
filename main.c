#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * execute - executes command passed as parameter
 * @command: command passed to execute
 * @env: environment from main
 * Return: void;
 */

void execute(char *command, char **env)
{
	int i = 0;
	char **argv = malloc(2 * sizeof(char *));
	int len = strlen(command);

	argv[0] = command;
	argv[0][len - 1] = '\0';
	argv[1] = NULL;
	if (execve(argv[0], argv, env) == -1)
	{
		printf("($) ");
		perror("Error:");
	}
}
/**
 * shell_interactive - starts shell
 * @env: environment from main
 * Return: void;
 */

void shell_interactive(char **env)
{
	char *line = NULL;
	size_t size = 0;
	pid_t child;
	int status;

	printf("($) ");
	while (line != "exit\n")
	{
		child = fork();
		if (child == 0)
		{
			while (getline(&line, &size, stdin) != -1)
			{
				execute(line, env);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
}

/**
 * shell_nonint - executes command in non interactive mode
 * @env: array of chars containing env
 * Return: void;
 */

void shell_nonint(char **env)
{
	char *line = NULL;
	size_t size = 0;
	int status;

	getline(&line, &size, stdin);
	execute(line, env);
	free(line);
}

/**
 * main - starts shell
 * @ac: arg count
 * @av: arg array
 * @env: environment
 * Return: void;
 */

int main(int ac, char **av, char **env)
{
	if (isatty(0))
		shell_interactive(env);
	else
		shell_nonint(env);
	return (0);
}
