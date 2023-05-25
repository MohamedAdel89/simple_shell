#include "headers.h"

/**
 *valid_command - validates if the command is a built in or has a binary file
 *@argv: array of strings input
 *@name: name of the shell
 *@line: number of line executed
 *Return: none
 */

void valid_command(char **argv, char *name, int line)
{
	bicmds_t builtinCmds[] = {
		{"cd", built_cd},
		{"env", _env},
		{"setenv", prueba},
		{"unsetenv", prueba},
		{"exit", built_exit},
		{"alias", prueba},
		{"help", built_help},
		{"history", built_history},
		{NULL, NULL}
	};
	int iter = 0;
	char *ful_path;

	while (builtinCmds[iter].name != NULL)
	{
		if (_strncmp(builtinCmds[iter].name, argv[0], 0) == 0)
		{
			if (builtinCmds[iter].f(argv) == -1)
				exit(EXIT_FAILURE);
		}
		iter++;
	}
	ful_path = _which(*argv);
	if (ful_path != NULL)
	{
		if (execve(ful_path, argv, environ) == -1)
			perror(name);
		exit(EXIT_FAILURE);
	}
	else
	{
		pperror(line, name, argv);
		free(argv[0]);
		free(argv);
		exit(127);
	}
}

/**
 *_which - find the path for a command
 *@cmd: command to find
 *Return: the ful path concatenated with the command
 */

char *_which(char *cmd)
{

	struct stat st;
	char *path, *cat, *Bcmd = str_concat("/", cmd), *tmpEnviron, sw = '0';

	if (*cmd == '/' || *cmd == '.')
		return (cmd);
	tmpEnviron = get_path();
	path = _strtok(tmpEnviron, "=");
	path = _strtok(NULL, "");
	if (path == NULL || tmpEnviron == NULL)
		return (NULL);
	else if (*path == ':')
		check_cd(&path, &Bcmd, &cat, &sw);
	else
		path = _strtok(path, ":");
	while (path != NULL)
	{
		path = _strtok(NULL, "");
		if (path == NULL)
			break;
		if (*path == ':')
			check_cd(&path, &Bcmd, &cat, &sw);
		else
		{
			path = _strtok(path, ":");
			cat = str_concat(path, Bcmd);
			if (stat(cat, &st) == 0)
				break;
			free(cat);
		}
	}
	free(tmpEnviron);
	if (path != NULL || sw == '1')
		cat != (Bcmd + 1) ? free(Bcmd) : (void)1;
	else
	{
		cat = path;
		free(Bcmd);
	}
	return (cat);
}

/**
 *check_cd - checks for current path
 *@path: current path
 *@Bcmd: slash command
 *@cat: concatenation
 *@sw: switch for which
 *Return: none
 */

void check_cd(char **path, char **Bcmd, char **cat, char *sw)
{
	struct stat st;

	*cat = *Bcmd + 1;
	if (stat(*cat, &st) == 0)
	{
		*path = NULL;
		*sw = '1';
	}
	else
		*path = _strtok(*path, ":");

}

/**
 *_strdup - copy a string
 *@str: string to be copyied
 *Return: pointer to a newly allocated space in memory
 */

char *_strdup(char *str)
{
	int size = 1;
	char *cpystr;

	if (str == NULL)
	{
		return (NULL);
	}

	while (*(str + size - 1) != '\0')
		size++;

	cpystr = malloc(size * sizeof(char));

	if (cpystr == NULL)
	{
		free(cpystr);
		return (NULL);
	}
	size--;
	for (; size >= 0; size--)
		*(cpystr + size) = *(str + size);
	return (cpystr);
}

/**
 *get_path - function that get path variable in k
 *Return: char pointing to a copy to path
 */

char *get_path(void)
{
	unsigned int i = 0;
	char *tmpEnviron;

	while (environ[i] != NULL && _strncmp(environ[i], "PATH", 4) != 0)
		(i)++;
	if (environ[i] == NULL)
		return (NULL);
	tmpEnviron = _strdup(environ[i]);
	return (tmpEnviron);
}
