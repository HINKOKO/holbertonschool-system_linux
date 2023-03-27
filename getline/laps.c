#include "laps.h"

/**
 * 
 * 
 * 
 * 
*/

void race_state(int *id, size_t size)
{
	size_t i;
	int laps = 0;

	for (i = 0; i < size; i++)
	{
		printf("Car %d joined the race\n", id[i]);
		laps++;
	}
	printf("Race state:\n");
}
