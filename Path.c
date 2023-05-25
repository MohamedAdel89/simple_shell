#include "headers.h"

/**
* main - Entry point
* Return: Always 0
*/

int Path (void)

{
char *cwd;
	cwd = getcwd(NULL, 0);
if (cwd == NULL)
	{
	perror("getcwd() error");
	exit(EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
return (0);
}
