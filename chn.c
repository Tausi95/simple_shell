#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	size_t i = 0;
	char **strs;
	list_t *node = head;

	while (node)
	{
		i++;
		node = node->next;
	}

	if (!head || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	i = 0;
	while (head)
	{
		strs[i] = strdup(head->str);
		if (!strs[i])
		{
			while (i > 0)
				free(strs[--i]);
			free(strs);
			return (NULL);
		}
		head = head->next;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;
	char *num;

	while (h)
	{
		num = convert_number(h->num, 10, 0);
		_puts(num);
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		free(num);
		h = h->next;
		i++;
	}
	return i;
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	while (node)
	{
		if (node->str && strstr(node->str, prefix) == node->str)
		{
			if (c == -1 || node->str[strlen(prefix)] == c)
				return node;
		}
		node = node->next;
	}
	return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	for (ssize_t i = 0; head; head = head->next, i++)
	{
		if (head == node)
			return i;
	}
	return -1;
}
