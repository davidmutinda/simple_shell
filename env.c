#include "main.h"
/**
 * print_env - prints current environment
 * @environ: pointer to environment variables
 * Return: void
 */
void print_env(char **environ)
{
	int count = 0, i;
	char new = '\n';

	while (environ[count])
	{
		i = 0;
		while (environ[count][i] != '\0')
		{
			write(1, &environ[count][i], 1);
			i++;
		}
		write(1, &new, 1);
		count++;
	}
}
