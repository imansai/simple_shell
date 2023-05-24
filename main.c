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
 * @av: first arg from argv
 * @env: environment from main
 * @count: command count
 * Return: void;
 */

void execute(char *command, char *av, char **env, int count)
{
	char **argv = malloc(2 * sizeof(char *));
	int len = strlen(command);

	argv[0] = command;
	argv[0][len - 1] = '\0';
	argv[1] = NULL;
	if (execve(argv[0], argv, env) == -1)
	{
		printf("%s: %d: %s: not found\n", av, count, argv[0]);
	}
}
/**
 * shell_interactive - starts shell
 * @av: first arg from argv
 * @env: environment from main
 * Return: void;
 */

void shell_interactive(char *av, char **env)
{
	char *line = "";
	size_t size = 0;
	pid_t child;
	int status;
	int count = 0;

	printf("($) ");
	while (getline(&line, &size, stdin) != -1)
	{
		count++;
		child = fork();
		if (strcmp(line, "exit\n") == 0)
		{
			break;
		}
		if (child == 0)
		{

			execute(line, av, env, count);
			_exit(0);
		}
		else
		{
			wait(&status);
		}
		printf("($) ");
	}
	free(line);
}

/**
 * shell_nonint - executes command in non interactive mode
 * @av: first arg from argv
 * @env: array of chars containing env
 * Return: void;
 */

void shell_nonint(char *av, char **env)
{
	char *line = NULL;
	size_t size = 0;

	getline(&line, &size, stdin);
	execute(line, av, env, 0);
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
	int i = 0;

	while (i != ac)
		(void)av[i++];
	if (isatty(0))
		shell_interactive(av[0], env);
	else
		shell_nonint(av[0], env);
	return (0);
}
