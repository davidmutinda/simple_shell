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
	char *av[4]; /*stores arguments for the execve() function*/
	char *token, *string, *str = NULL;
	int i = 0;
	pid_t child;
	int status, result;

	printf("($) ");
	ch = getline(&str, &len, stdin); /*gets the characters that the user inputs*/
	if (str[0] == '\n')
		shell(argv);

	str[ch - 1] = '\0'; /*changes str[ch - 1] from '\n' and '\0'*/
	result = strcmp(str, "exit");
	if (result == 0) /*if the user keys in "exit" the program is exited*/
		exit(0);

	for (string = str; ; string = NULL, i++)
	{ /*this loop separates the string into words*/
		token = strtok(string, " ");
		av[i] = token;
		if (token == NULL)
			break;
	}
	child = fork(); /*creates child process*/
	if (child == 0) /*return value of fork() in child process is always 0*/
	{ /*child process automatically terminates if execve() is successful*/
		if (execve(av[0], av, NULL) == -1)
		{ /*program enters this block if execve() fails*/
			perror(argv[0]);
			exit(0);/*exits from the child process*/
		}
	}
	wait(&status); /*parent process waits for child process to be executed first*/
	shell(argv); /*program is called again and waits for user input*/
}
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		exit(0);
	}

	shell(argv);

	return (0);
}
