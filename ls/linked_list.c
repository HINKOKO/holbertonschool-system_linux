#include "hls.h"

/**
 * add_node - adds a new node to the linked list
 * used to store options args
 * @head: double pointer to head of LL
 * @str: string options
 * Return: pointer to new node
 */

opt_t *add_node(opt_t **head, char *str)
{
	opt_t *new = NULL, *curr = NULL;

	new = malloc(sizeof(opt_t));
	if (!new)
		return (NULL);
	/* fill value for new node */
	new->str = strdup(str);
	new->len = _strlen(str);
	new->next = NULL;
	/* list is empty ? */
	if (*head == NULL)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		/* append to the end */
		curr->next = new;
	}
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
