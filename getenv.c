#include "main.h"
/**
 * _getenv - prints current environment
 * @token: string
 * Return: pointer
 */
char *_getenv(char *token)
{
	int count = 0, i;
	char *string;
	char new = '\n';

	string = malloc(sizeof(char) * 10);
	token += 1;
	while (environ[count])
	{
		i = 0;
		while (environ[count][i] != '=')
		{
			string[i] = environ[count][i];
			i++;
		}
		string[i] = '\0';
		if (!_strcmp(string, token))
		{
			free(string);
			return (environ[count]);
		}
		count++;
	}
	write (1, &new, 1);
	return (NULL);
}
