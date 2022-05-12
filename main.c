#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
/**
 * shell - checks and executes commands entered
 *
 * Return: void
 */
void shell(char *av[])
{
	size_t len, ch;
	char *av[4];
	char *token, *string, *str = NULL;
	int i = 0;
	pid_t child;
	int status, result;

	printf("#cisfun$ ");
	ch = getline(&str, &len, stdin);

	str[ch - 1] = '\0';
	result = strcmp(str, "exit");
	if (result == 0)
	{
		printf("$ exiting the shell\n");
		exit(0);
	}
	for (string = str; ; string = NULL, i++)
	{
		token = strtok(string, " ");
		av[i] = token;
		if (token == NULL)
			break;
	}
	child = fork();
	if (child == 0)
	{
		if (execve(av[0], av, NULL) == -1)
		{
			perror("%s", av[0]);
			exit(0);
		}
	}
	wait(&status);
	shell();
}
/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(int ac, char *av[])
{
	if (ac < 1)
		exit(0);

	shell(av);

	return (0);
}
