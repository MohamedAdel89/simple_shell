#include "headers.h"

/**
 *pperror - prints the error when there is no a command found
 *@line: number of lines executed
 *@name: name of the shell
 *@argv: command that has not been found
 *Return: none
 */

void pperror(int line, char *name, char **argv)
{
	char *ful_err, error[] = ": not found\n";
	int iter = 0, tmp = line, tmpIt = 1;
	ful_err = malloc(1024 * sizeof(char));
	for (iter = 0; iter < 1024; iter++)
		ful_err[iter] = '\0';
	for (iter = 0; name[iter] != '\0'; iter++)
		ful_err[iter] = name[iter];
	ful_err[iter] = ':';
	ful_err[iter + 1] = ' ';
	for (iter += 2; line != 0; iter++)
	{
		for (tmp = line / 10; tmp != 0; tmp /= 10)
			tmpIt *= 10;
		ful_err[iter] = (line / tmpIt) + '0';
		line -= line - (line % tmpIt);
		tmpIt = 1;
	}
	ful_err[iter] = ':';
	ful_err[iter + 1] = ' ';
	tmp = iter + 2;
	for (iter += 2; argv[0][iter - tmp] != '\0'; iter++)
		ful_err[iter] = argv[0][iter - tmp];
	tmp = iter;
	for (; error[iter - tmp] != '\0'; iter++)
		ful_err[iter] = error[iter - tmp];
	ful_err[iter] = '\0';
	write(STDERR_FILENO, ful_err, iter);
	free(ful_err);
}

