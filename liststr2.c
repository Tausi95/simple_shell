#include "shell.h"

/**
 * list_len - Determines the length of the linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
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
 * list_to_strings - Returns an array of strings from the list.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
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
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
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
 * node_starts_with - Returns the node whose string starts with the prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matching node or NULL if not found.
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
 * get_node_index - Gets the index of a node in the linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
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
