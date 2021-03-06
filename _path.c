#include "holberton.h"

/**
 * free_pointers - free all tokens
 * @ptr: all the tokens (aka characters)
 * Return: void
 */

void free_pointers(char **ptr)
{
	int i;

	for (i = 0; ptr[i] != NULL; i++)
		free(ptr[i]);
	free(ptr);
}

/**
 * _path - handles concatination of input and path directories
 * @t: string inputed into command line
 * Return: void
 */
void _path(char **t)
{

	list_tt *tmp_node, *head;
	char *path;
	int file, buffer;

	buffer = BUFSIZE;
	head = _build_list();
	path = malloc(sizeof(char) * buffer);
	tmp_node = head;
	while (1)
	{
		_pathhelper(file, t, head, path);
		path = _strcpy(path, tmp_node->str);
		path = _strcat(path, t[0]);
		file = access(path, X_OK);
		if (file == 0)
		{
			if (execve(path, t, environ) == -1)
				perror("error");
			free(path);
			free(head);
		}
		tmp_node = tmp_node->next;
		if (tmp_node->next == NULL)
		{
			_errorstring(t[0]);
			_errorstring(": command not found\n");
			free_pointers(t);
			free(path);
			free_list(head);
			_exit(98);
		}
	}
	free_list(head);
	free(path);
}

/**
 * _pathhelper - handles case if input begins with '/'
 * @file: checks if specific path file is found
 * @t: inputed string in command line
 * @list: build list from the environment
 * @path: each directory in path
 * Return: void
 */
void _pathhelper(int file, char **t, list_tt *list, char *path)
{
	if (t[0][0] == '/')
	{
		file = access(t[0], X_OK);
		if (file == 0)
			execve(t[0], t, environ);
		else
		{
			free_pointers(t);
			free(path);
			free(list);
			_errorstring("-bash: ");
			perror(t[0]);
			_exit(98);
		}
	}

}
