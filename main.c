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
	char **argv = malloc(5 * sizeof(char *));

	argv = strtokarray(command);
	argv[0] = trim(argv[0]);

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
	char cwd[1024];

	printf("($) ");
	while (getline(&line, &size, stdin) != -1)
	{
		count++;
		child = fork();
		if (strcmp(line, "exit\n") == 0)
		{
			exit(2);
		}
		else if (child == 0 && strcmp(line, "pwd\n") == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				printf("%s\n", cwd);
			}
			else
			{
				perror("getcwd() error");
			}
		}
		if (child == 0 && strcmp(line, "pwd\n") != 0)
		{

			execute(line, av, env, count);
			_exit(2);
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
	pid_t child;
	int status;
	int count = 0;
	char cwd[1024];

	while (getline(&line, &size, stdin) != -1)
	{
		count++;
		child = fork();
		if (strcmp(line, "exit\n") == 0)
		{
			exit(2);
		}
		else if (child == 0 && strcmp(line, "pwd\n") == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				printf("%s\n", cwd);
			}
			else
			{
				perror("getcwd() error");
			}
		}
		if (child == 0 && strcmp(line, "pwd\n") != 0)
		{

			execute(line, av, env, count);
			_exit(0);
		}
		else
		{
			wait(&status);
		}
	}
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
