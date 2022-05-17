#include "main.h"

/**
 * get_env - gets value of environment variable
 * @av: pointer to strings
 * Return: void
 */
void get_env(char **av)
{
	char *new;
	int i = 1, j = 0;

	new = malloc(sizeof(char) * strlen(av[1]));
	while (av[1][i] != '\0')
	{/*copies content from av[1][i] to new starting from av[1][1]*/
		new[j] = av[1][i];
		i++;
		j++;
	}
	av[1] = getenv(new);/*copies value of environment variable to av[1]*/
	free(new);
}

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
			exit(0);/*exits from the child process*/
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
	char *token, *string, *str = NULL;
	int i = 0, status, result;

	printf("($) ");
	ch = getline(&str, &len, stdin); /*gets the characters that the user inputs*/
	if (*str == '\n' || *str == EOF)
	{
		shell(argv);
	}

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
	if (av[1] != NULL)
	{
		if (av[1][0] == '$')
		{
			get_env(av);
			if (av[1] == NULL)
			{
				perror("Variable not found");
				shell(argv);
			}
		}
	}
	child_process(av, argv);
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
		exit(0);
	}

	shell(argv);

	return (0);
}
