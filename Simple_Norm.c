#include "headers.h"
/**
 *built_exit - exit from shell
 *
 *@cadena: array from argv
 *
 *Return: pointer to string
 */

{
	int status;

	if (cadena[1] == NULL)
	{
		free(cadena[0]);
		free(cadena);
		exit(124);
	}
	else
	{
		status = _atoi(cadena[1]);
		free(cadena[0]);
		free(cadena);
		exit(status);
	}
	return (0);
}

/**
 *built_cd - change directory
 *
 *@cadena: array from argv
 *
 *Return: pointer to string
 */

int built_cd(char **cadena)
{
	free(cadena[0]);
	free(cadena);
	exit(123);
}

/**
 *cd_parent - change directory
 *
 *@argv: array from argv
 *@name: name  of shell
 *Return: pointer to string
 */

void cd_parent(char **argv, char *name)
{
	char *home, buf[BUFSIZ], *cp = getcwd(buf, sizeof(buf)), *chr;
	unsigned int i = 0;
	static char old_pwd[BUFSIZ];

	home = get_home();
	if (home == NULL)
		home = cp;
	if (argv[1] != NULL)
		chr = argv[1];
	else
		chr = "";
	if (argv[1] == NULL || chr[0] == '~' || chr[0] == '-')
	{

		if (chr[0] == '-')
		{
			write(STDOUT_FILENO, old_pwd, _strlen(old_pwd));
			write(STDOUT_FILENO, "\n", 1);
			chdir(old_pwd);
		}
		else if (chdir(home) == -1)
		{
			chdir(cp);
			perror(name);
		}
	}
	else if (chdir(argv[1]) == -1)
	{
		chdir(cp);
		perror(name);
	}
	for (i = 0; cp[i] != '\0'; i++)
		old_pwd[i] = cp[i];
	old_pwd[i] = '\0';
}

/**
 *built_history - builtin history
 *
 *@cadena: data info
 *
 *Return: No return
 */
int built_history(char **cadena)
{
	char *home, *tmp[] = {"/bin/cat", NULL, NULL};

	(void)cadena;
	home = get_home();
	tmp[1] = str_concat(home, "/cmd_hist.txt");
	if (execve("/bin/cat", tmp, NULL) == -1)
	{
		perror("");
		free(tmp[1]);
		return (-1);
	}
	free(tmp[1]);
	return (0);
}

/**
 *built_help - builtin help
 *
 *@cadena: data info
 *
 *Return: 0 succces -1 failure
 */
int built_help(char **cadena)
{
	char *home, *tmp[] = {"/bin/cat", NULL, NULL};
	char *list_b[8][2] = {
		{"cd", "/help_cd.txt"            },
		{"env", "/help_env.txt"          },
		{"setenv", "/help_setenv.txt"    },
		{"unsetenv", "/help_unsetenv.txt"},
		{"exit", "/help_exit.txt"        },
		{"alias", "/help_alias.txt"      },
		{"help", "/help_help.txt"        },
		{"history", "/help_history.txt"  }
	};
	int cont, len;

	cont = 0;
	len = strlen(list_b[cont][0]);
	while ((cadena[1] != NULL) &&
	((_strncmp(cadena[1], list_b[cont][0], len)) != 0) && (cont < 8))
	{
		cont++;
		len = strlen(list_b[cont][0]);
	}
	home = get_home();
	if (home == NULL)
		return (-1);
	if (cadena[1] == NULL || cont >= 8)
		tmp[1] = str_concat(home, "/help_empty.txt");
	else
	{
		tmp[1] = str_concat(home, list_b[cont][1]);
	}
	if (execve("/bin/cat", tmp, NULL) == -1)
	{
		perror("");
		free(tmp[1]);
		return (-1);
	}
	free(tmp[1]);
	return (0);
}
