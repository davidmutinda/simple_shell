#include "main.h"
/**
 * print_env - prints current environment
 * @environ: pointer to environment variables
 * Return: void
 */
void print_env(char **environ)
{
	int count = 0;

	while (environ[count])
	{
		printf("%s\n", environ[count]);
		count++;
	}
}
