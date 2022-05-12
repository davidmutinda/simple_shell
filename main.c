#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
/**
 * shell - checks and executes commands entered
 * @argv: argument vector
 * Return: void
 */
void shell(char *argv[])
{
	size_t len, ch;
	char *av[4];
	char *token, *string, *str = NULL;
	int i = 0;
	pid_t child;
	int status, result;

	printf("($) ");
	ch = getline(&str, &len, stdin);
	if (str[0] == '\n')
		shell(argv);

	str[ch - 1] = '\0';
	result = strcmp(str, "exit");
	if (result == 0)
		exit(0);

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
			perror(argv[0]);
			exit(0);
		}
	}
	wait(&status);
	shell(argv);
}
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	if (argc < 1)
		exit(0);

	shell(argv);

	return (0);
}
