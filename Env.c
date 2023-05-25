#include "headers.h"

/**
 * create_env - creates the environment in a file named env.txt
 * @env: environmental variable
 * Return: void
 */
void create_env(char **env)
{
	int fileDesc, envIter = 0, len = 0;
	char *home;

	home = str_concat(get_home(), "/env.txt");
	fileDesc = open(home, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	free(home);

	if (fileDesc == -1)
		return;

	while (env[envIter] != NULL)
	{
		len = _strlen(env[envIter]);
		write(fileDesc, env[envIter], len);
		write(fileDesc, "\n", 1);
		envIter++;
	}

	close(fileDesc);
}

/**
 * _env - prints all the environmental variables
 * @argv: array of strings
 * Return: int status
 */
int _env(char *argv[])
{
	char *home = str_concat(get_home(), "/env.txt");
	char *cat[] = {"/bin/cat", NULL, NULL};

	cat[1] = home;
	(void)argv;

	if (execve(cat[0], cat, NULL) == -1)
		exit(-1);

	return (0);
}
