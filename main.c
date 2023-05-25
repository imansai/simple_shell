#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "main.h"

/**
 * execute - executes command passed as parameter
 * @command: command passed to execute
 * @av: first arg from argv
 * @env: environment from main
 * @count: command count
 * Return: void;
 */

int execute(char *command, char *av, char **env, int count)
{
	char **argv;
	char cwd[1024];

	argv = strtokarray(command, " \n\r\t");
	argv[0] = strtok(argv[0], " \n\r\t");

	if (strcmp(argv[0], "(null)") != 0)
	{
		if (strcmp(argv[0], "env") == 0)
			execve("/bin/env", argv, env);
		else if (strcmp(argv[0], "pwd") == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				printf("%s\n", cwd);
			else
				perror("getcwd() error");
		}
		else if (strcmp(argv[0], "exit") == 0)
			return (1);

		else
		{
			if (execve(argv[0], argv, env) != 1)
				printf("%s: %d: %s: not found\n", av, count, argv[0]);
			return (0);
		}
	}
	return (0);
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
	int count = 0;
	int status;

	printf("($) ");
	while (getline(&line, &size, stdin) != -1)
	{

		clearerr(stdin);
		count++;
		child = fork();
		if (child == 0)
		{
			if (execute(line, av, env, count) == 1)
				exit(1);
			exit(0);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
				exit(0);
			else
				printf("($) ");
		}
	}
	free(line);
	putchar('\n');
	line = "";
	exit(0);
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
	int count = 0;
	ssize_t result;
	int status;

	while ((result = getline(&line, &size, stdin)) != -1)
	{

		count++;

		child = fork();
		if (child == 0)
		{
			if (execute(line, av, env, count) == 1)
				exit(1);
			free(line);
			exit(0);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
				exit(0);
		}
	}
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
	(void)ac;
	if (isatty(0))
		shell_interactive(av[0], env);
	else
		shell_nonint(av[0], env);
	return (0);
}
