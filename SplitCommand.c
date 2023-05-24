#include "headers.h"
#include <string.h>

/**
 *is_in_delim - replace _strtok function
 *@a: pointer to string
 *@delim: pointer to string delim
 *Return: flag = 1 si char a is in delim
 */

int is_in_delim(char a, const char *delim)
{
	int flag = 0, cont;

	for (cont = 0; delim[cont] != '\0'; cont++)
	{
		if (delim[cont] == a)
			flag = 1;
	}

	return (flag);
}

/**
 *look_first_char - found first char differ delim
 *@str: pointer to string
 *@delim: pointer to string delim
 *Return: pointer to first char different to delim
 */

char *look_first_char(char *str, const char *delim)
{
	char a, *ptr;
	int cont = 0, flag_is = 1;

	while (flag_is == 1)
	{
		a = str[cont];
		if (a == '\0')
			return (NULL);
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
	return (ptr);
}

/**
 *look_first_delim - replace _strtok function
 *@str: pointer to string
 *@delim: pointer to string delim
 *Return: pointer to first char different to delim
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
	return (ptr);
}

/**
 *look_last_delim - look last char bfoor replace _strtok function
 *@str: pointer to string with char different to dilem
 *@delim: pointer to string delim
 *Return: pointer to first char different to delim
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
	return (ptr);
}

/**
 *_strtok - replace _strtok function
 *@str: pointer to string
 *@delim: pointer to string delim
 *Return: pointer to string
 */

char *_strtok(char *str, const char *delim)
{
	char *aux2, *aux1;
	static char *ptr;
	if (str != NULL)
	{
		aux1 = look_first_char(str, delim);
		if (aux1 == NULL)
			return (NULL);
		aux2 = look_last_delim(aux1, delim);
		if (aux2[0] == '\0')
			ptr = aux2;
		else
			ptr = aux2 + 1;
		aux2[0] = '\0';
		if (aux2 <= aux1 || aux1 == NULL || aux1 [0] == '#')
			return (NULL);
		return (aux1);
	}
	aux1 = look_first_char(ptr, delim);
	if (aux1 == NULL)
		return (NULL);
	aux2 = look_last_delim(aux1, delim);
	if (aux2[0] == '\0')
		ptr = aux2;
	else
		ptr = aux2 + 1;
	aux2[0] = '\0';
	if (aux2 <= aux1 || aux1 == NULL || aux1[0] == '#')
		return (NULL);
	return (aux1);
}
