#include "headers.h"
#include <string.h>

/**
 * is_in_delim - checks if a character is in the delimiter string
 * @a: character to check
 * @delim: delimiter string
 * Return: 1 if char a is in delim, 0 otherwise
 */
int is_in_delim(char a, const char *delim)
{
	int flag = 0, cont;

	for (cont = 0; delim[cont] != '\0'; cont++)
	{
		if (delim[cont] == a)
			flag = 1;
	}

	return flag;
}

/**
 * look_first_char - finds the first character that is different from the delimiter
 * @str: string to search
 * @delim: delimiter string
 * Return: pointer to the first character different from delim
 */
char *look_first_char(char *str, const char *delim)
{
	char a, *ptr;
	int cont = 0, flag_is = 1;

	while (flag_is == 1)
	{
		a = str[cont];
		if (a == '\0')
			return NULL;
		flag_is = is_in_delim(a, delim);
		cont++;
	}

	ptr = str;
	cont--;

	while (cont > 0)
	{
		ptr++;
		cont--;
	}

	return ptr;
}

/**
 * look_first_delim - finds the first delimiter character
 * @str: string to search
 * @delim: delimiter string
 * Return: pointer to the first delimiter character
 */
char *look_first_delim(char *str, const char *delim)
{
	char a, *ptr;
	int cont = 0, flag_is = 0;

	while (flag_is == 0)
	{
		a = str[cont];
		flag_is = is_in_delim(a, delim);
		cont++;
	}

	ptr = str;
	cont--;

	while (cont > 0)
	{
		ptr++;
		cont--;
	}

	return ptr;
}

/**
 * look_last_delim - finds the last delimiter character before a non-delimiter character
 * @str: string with characters different from delim
 * @delim: delimiter string
 * Return: pointer to the last delimiter character
 */
char *look_last_delim(char *str, const char *delim)
{
	char a, *ptr;
	int cont = 0, flag_is = 0;

	while (flag_is == 0)
	{
		a = str[cont];
		flag_is = is_in_delim(a, delim);
		cont++;
		if (a == '\0')
			break;
	}

	ptr = str;
	cont = cont - 1;

	while (cont > 0)
	{
		ptr++;
		cont--;
	}

	return ptr;
}

/**
 * _strtok - replaces strtok function
 * @str: string to tokenize
 * @delim: delimiter string
 * Return: pointer to the next token
 */
char *_strtok(char *str, const char *delim)
{
	char *aux2, *aux1;
	static char *ptr;

	if (str != NULL)
	{
		aux1 = look_first_char(str, delim);
		if (aux1 == NULL)
			return NULL;

		aux2 = look_last_delim(aux1, delim);
		if (aux2[0] == '\0')
			ptr = aux2;
		else
			ptr = aux2 + 1;

		aux2[0] = '\0';

		if (aux2 <= aux1 || aux1 == NULL || aux1[0] == '#')
			return NULL;

		return aux1;
	}

	aux1 = look_first_char(ptr, delim);
	if (aux1 == NULL)
		return NULL;

	aux2 = look_last_delim(aux1, delim);
	if (aux2[0] == '\0')
		ptr = aux2;
	else
		ptr = aux2 + 1;

	aux2[0] = '\0';

	if (aux2 <= aux1 || aux1 == NULL || aux1[0] == '#')
		return NULL;

	return aux1;
}
