#include "headers.h"

/**
 * get_home - gets the HOME environmental variable
 * Return: string containing the HOME value
 */
char *get_home(void)
{
	int a = 0, cont;
	char *home;

	while (environ[a] != NULL && _strncmp(environ[a], "HOME", 4) != 0)
	{
		a++;
	}

	if (environ[a] == NULL)
		return (NULL);

	for (cont = 0; environ[a][cont] != '='; cont++)
		;

	home = environ[a] + cont + 1;
	return (home);
}

/**
 * delete_delim - counts until the next delimiter
 * @delim_2: delimiter strings like \n, ;, &&, ||
 * Return: the number of characters written
 */
int delete_delim(char *delim_2)
{
	int fd_log, leido, escrito, cont;
	char tmp_buffer[BUFFERSIZE], *first_delim, *my_path;
	long int diferencia;

	for (cont = 0; cont == BUFFERSIZE - 1; cont++)
		tmp_buffer[cont] = 4;

	my_path = get_home();
	my_path = str_concat(my_path, "/cmd_log.txt");
	fd_log = open(my_path, O_RDONLY);
	leido = read(fd_log, tmp_buffer, BUFFERSIZE);
	close(fd_log);

	if (leido == -1 || leido == 0)
		return (-1);

	first_delim = look_first_delim(tmp_buffer, delim_2) + 1;
	diferencia = first_delim - tmp_buffer;
	fd_log = open(my_path, O_WRONLY | O_TRUNC);

	if (fd_log == -1)
		return (-1);

	escrito = write(fd_log, first_delim, (long int)leido - diferencia);

	if (escrito == -1)
		return (-1);

	close(fd_log);
	free(my_path);
	return (escrito);
}

/**
 * _strcopy - copies memory
 * @str: the origin string
 * @ptr: the destination string
 * Return: the number of characters copied
 */
int _strcopy(char *str, char *ptr)
{
	unsigned int cont = 0;

	while (str[cont] > 0 && str[cont] != '\n' && str[cont] != '\0' && str[cont] != ';')
	{
		ptr[cont] = str[cont];
		cont++;
	}

	if (str[cont] == '\0')
	{
		free(ptr);
		exit(0);
	}

	return (cont);
}

/**
 * _realloc - reallocates memory
 * @ptr: the address of the old memory
 * @new_size: the new size
 * Return: pointer to the newly allocated memory
 */
void *_realloc(void *ptr, unsigned int new_size)
{
	char *a;
	unsigned int cont = 0;
	char *aux = ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	a = malloc(new_size * sizeof(char));

	if (a == NULL)
		return (NULL);

	while (aux[cont] != '\0')
	{
		a[cont] = aux[cont];
		cont++;
	}

	free(ptr);
	return (a);
}

/**
 * _getline - Replacement for getline function
 * @lineptr: pointer to buffer
 * @n: quantity of bytes to read
 * @stream: kind of stream to get info
 * Return: number of characters read or -1 in case of error
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t size;
	char key_buff[BUFFERSIZE];
	char *delim_2 = ";\n", *my_path;
	int leido = 0, del_delim = 0, cont, fd_log;

	size = *n;
	stream = stream;
	leido = read(STDIN_FILENO, key_buff, BUFFERSIZE);

	for (cont = leido; cont < BUFFERSIZE - 1; cont++)
		key_buff[cont] = '\0';

	if (leido != 0)
		init_file(key_buff, leido);

	my_path = get_home();
	my_path = str_concat(my_path, "/cmd_log.txt");
	fd_log = open(my_path, O_RDONLY);
	free(my_path);
	leido = read(fd_log, key_buff, BUFFERSIZE);

	if (leido == -1)
		return (-1);

	close(fd_log);

	for (cont = leido; cont < BUFFERSIZE - 1; cont++)
		key_buff[cont] = '\0';

	if (*lineptr == NULL)
	{
		*lineptr = malloc(sizeof(char) * BUFFERSIZE);

		if (*lineptr == NULL)
			return (-1);
	}
	else if (leido > size)
	{
		*lineptr = _realloc(*lineptr, leido + 120);

		if (*lineptr == NULL)
			return (-1);
	}

	leido = _strcopy(key_buff, *lineptr);
	(*lineptr)[leido] = '\0';
	del_delim = delete_delim(delim_2);

	if (del_delim == -1)
		return (-1);

	return (leido);
}
