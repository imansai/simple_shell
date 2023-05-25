#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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
	char **argv;

	argv = strtokarray(command, " \n\r\t");
	argv[0] = strtok(argv[0], " \n\r\t");

	if (strcmp(argv[0], "(null)") != 0)
	{
		if (strcmp(argv[0], "env") == 0)
		{
			if (execve("/bin/env", argv, env) == -1)
			{
				printf("%s: %d: %s: not found\n", av, count, argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (execve(argv[0], argv, env) == -1)
			{
				printf("%s: %d: %s: not found\n", av, count, argv[0]);
				exit(EXIT_FAILURE);
			}
		}
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
	int count = 0;
	char cwd[1024];
	int checkpwd, checkexit, checknexit, status;

	printf("($) ");
	while (getline(&line, &size, stdin) != -1)
	{

		checkexit = strcmp(line, "exit\n");
		checknexit = strncmp(line, "exit ", 5);
		checkpwd = strcmp(line, "pwd\n");
		count++;
		child = fork();
		if (checkexit == 0 || checknexit == 0)
			break;
		if (child == 0 && strcmp(line, "pwd\n") == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				printf("%s\n", cwd);
			else
				perror("getcwd() error");
		}

		if (child == 0 && checkpwd != 0 && checkexit != 0)
		{
			execute(line, av, env, count);
			break;
		}
		else
		{
			wait(&status);
			printf("($) ");
		}
	}
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
	char cwd[1024];
	int checkpwd, checkexit, checknexit, status;

	while (getline(&line, &size, stdin) != -1)
	{
		checknexit = strncmp(line, "exit ", 5);
		checkexit = strcmp(line, "exit\n");
		checkpwd = strcmp(line, "pwd\n");
		count++;
		child = fork();
		if (checkexit == 0 || checknexit == 0)
			break;
		if (child == 0 && strcmp(line, "pwd\n") == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				printf("%s\n", cwd);
			else
				perror("getcwd() error");
		}

		if (child == 0 && checkpwd != 0 && checkexit != 0)
		{
			execute(line, av, env, count);
			break;
		}
		else
			wait(&status);
	}
	free(line);
	exit(0);
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