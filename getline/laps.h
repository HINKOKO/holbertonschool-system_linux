#ifndef RACE_CARS
#define RACE_CARS

#include <stdio.h>
#include <stdlib.h>

/**
 * struct car_s - struct to record laps by cars id's
 * @id: car identifier
 * @laps: number of laps completed
 * @next: pointer to next car struct
*/

typedef struct car_s
{
	int id;
	int laps;
	struct car_s *next;
} car_t;

void race_state(int *id, size_t size);
void newcar(car_t **head, int id);






#endif
