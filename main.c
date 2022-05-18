#include "main.h"

/**
 * child_process - creates a child process to execute user input
 * @av: pointer to strings
 * @argv: argument vector
 * Return: void
 */
void child_process(char **av, char **argv)
{
	pid_t child;

	child = fork(); /*creates child process*/
	if (child == 0) /*return value of fork() in child process is always 0*/
	{ /*child process automatically terminates if execve() is successful*/
		if (execve(av[0], av, NULL) == -1)
		{ /*program enters this block if execve() fails*/
			perror(argv[0]);
			exit(EXIT_FAILURE);/*exits from the child process*/
		}
	}
}

/**
 * shell - checks and executes commands entered
 * @argv: argument vector
 * Return: void
 */
void shell(char *argv[])
{
	size_t len, ch;
	char *av[4]; /*stores arguments for the execve() function*/
	char *token, *string, *str = NULL, bin[5] = "/bin/";
	int i = 0, status, result;

	write(1, "($) ", 4);
	ch = getline(&str, &len, stdin); /*gets the characters that the user inputs*/
	if (*str == '\n' || *str == EOF)
		shell(argv);
	str[ch - 1] = '\0'; /*changes str[ch - 1] from '\n' and '\0'*/
	result = _strcmp(str, "exit");
	if (result == 0) /*if the user keys in "exit" the program is exited*/
		exit(EXIT_SUCCESS);
	for (string = str; ; string = NULL, i++)
	{ /*this loop separates the string into words*/
		token = strtok(string, " ");
		av[i] = token;
		if (token == NULL)
			break;
	}
	if (!_strcmp(av[0], "env"))
	{
		print_env(environ);
		shell(argv);
	}
	else if (av[0][0] != '/')
	{
		av[0] = strcat(bin, av[0]);
	}

	if (av[1] != NULL)
	{
		if (av[1][0] == '$')/*checks for environment variables*/
			av[1] = _getenv(av[1]);/*copies value of environment variable to av[1]*/
	}
	child_process(av, argv); /*creates child process*/
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
	if (argc < 1)
	{
		perror("Wrong usage");
		exit(EXIT_FAILURE);
	}

	shell(argv);

	return (0);
}
