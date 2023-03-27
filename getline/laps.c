#include "laps.h"


/**
 * race_state - computes and displays the state of the race
 * @id: array of int for `identifiers` of each cars
 * @size: size of id's array
*/

void race_state(int *id, size_t size)
{
	size_t i;
	static car_t *head, *node;
	/* need `static` for the values of laps to persists */
	/* between the function calls */
	/* of `race_state` inside the main */
	/* otherwise laps remain forever to 0 */
	if (!size)
	{
		while (head)
		{
			node = head->next;
			/* keep track because we going to free "previous head" */
			free(head);
			/* assign the new head to node for the while to roll on*/
			head = node;
		}
		return;
	}
	for (i = 0; i < size; i++)
		newcar(&head, id[i]);
	printf("Race state:\n");
	/* read the linked list to display race state */
	for (node = head; node != NULL; node = node->next)
		printf("Car %d [%d laps]\n", node->id, node->laps);
}

/**
 * newcar - function to add new contender entering the race
 * @head: double pointer ==> gives ability to modify head pointer
 * of linked list
 * any changes will persists outside the function.
 * single pointer ==> we would loose changes when newcar exits
 * @id: id of the car
*/

void newcar(car_t **head, int id)
{
	car_t *new, *browse;

	new = malloc(sizeof(car_t));
	if (!new)
		return;

	if (*head == NULL || id < (*head)->id)
	{
		new->id = id;
		new->laps = 0;
		new->next = *head;
		*head = new;
		printf("Car %d joined the race\n", id);
		return;
	}

	for (new = *head; new->next != NULL && new->next->id <= id; new = new->next)
		;
	/* semi-colon "trick" to execute the loop with empty body */
	/* Because we need that for loop to be executed repeatedly */
	/* but execute code only when certain conditions (below) are met */
	if (new->id == id)
	/* car id exists, increment its laps */
	new->laps++;
	else
	{
		/* for loop rolls along linked list */
		/* lets insert in correct position that new car */
		browse = malloc(sizeof(car_t));
		if (!browse)
			return;
		browse->id = id;
		browse->laps = 0;
		browse->next = new->next;
		new->next = browse;
		printf("Car %d joined the race\n", id);
		}
}
