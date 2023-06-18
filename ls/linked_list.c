#include "hls.h"

/**
 * add_node - adds a new node to the linked list
 * used to store options args
 * @head: double pointer to head of LL
 * @str: string options
 * Return: pointer to new node
 */

opt_t *add_node(opt_t **head, const char *str)
{
	int i;
	char *c;
	opt_t *new = NULL;

	new = malloc(sizeof(opt_t));
	if (!new)
		return (NULL);
	/* fill value for new node */
	c = _strdup(str);
	if (c == NULL)
	{
		free(new);
		return (NULL);
	}
	for (i = 0; str[i];)
		i++;
	new->str = c;
	new->len = i;
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * free_list - properly free space allocated
 * to store argument passed to ls
 * @head: pointer to head of linked list
 */

void free_list(opt_t *head)
{
	opt_t *savior;

	while (head)
	{
		savior = head->next;
		free(head->str);
		free(head);
		head = savior;
	}
}
