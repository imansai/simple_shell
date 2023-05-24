#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void execute(char *command, char **env)
{
	char **argv = malloc(2 * sizeof(char *));
	argv[0] = command;
	argv[1] = NULL;
	if (execve(argv[0], argv, env) == -1)
	{
		perror("Error:");
	}
}
/**
 * shell_interactive - starts shell
 *
 * Return: void;
 */
void shell_interactive(char **env)
{
	char *line = NULL;
	size_t size = 0;

	printf("($) ");
	getline(&line, &size, stdin);
	execute("/bin/ls", env);
	free(line);
}

char **strtokarray(char *str)
{
	char **arr = malloc(sizeof(char *));
	char *token;
	int i = 0;

	if (str == NULL)
		return (NULL);
	token = strtok(str, ":");
	while (token != NULL)
	{
		arr = realloc(arr, (i + 1) * sizeof(char *));
		arr[i] = malloc((strlen(token) + 1) * sizeof(char));
		token = strtok(NULL, ":");
		arr[i++] = token;
	}
	return (arr);
}

void _which(char *str)
{
	char *path = getenv("PATH");
	int i = 0;

	char **arr = strtokarray(path);
	while (arr[i] != NULL)
	{
		if (strcmp(arr[i++], str) == 0)
		{
			printf("found %s\n", str);
			return;
		}
	}
	printf("couldnt find %s\n", str);
}

int main(int ac, char **av, char **env)
{

	shell_interactive(env);
	return (0);
}