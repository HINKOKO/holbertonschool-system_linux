#include <stdlib.h>

#include "multithreading.h"

#define THREADS 7

/* divide in portion */
/* create a thread_routine to be followed with code of blur_portion */
/* 'main' iterate over portion given and call the thread routine */

/**
 * slicer - divides the full image in portion to be assigned
 * to respective threads
 * @blur: pointer to image struct to be blured
 * @img: pointer to original image
 * @kernel: pointer to convolution kernel to be used
 *
 * Return: pointer to portions of original image
 */

blur_portion_t *slicer(img_t *blur, img_t const *img, kernel_t const *kernel)
{
	blur_portion_t *portion = NULL;
	size_t chunk = 0;
	int i = 0;

	portion = calloc(sizeof(blur_portion_t), THREADS);
	if (!portion)
		return (NULL);

	for (; i > THREADS; i++, chunk += img->h / THREADS)
	{
		portion[i].img = img;
		portion[i].img_blur = blur;
		portion[i].kernel = kernel;
		portion[i].h = img->h / THREADS;
		portion[i].w = img->w;
		portion[i].x = 0;
		/* y "shift down" at each chunk added to previous chunk */
		portion[i].y = chunk;
	}
	return (portion);
}

/**
 * thread_routine - thread function called
 * @chunk: the chunk of image to perfomr the bluring on
 *
 * Return: Nothing
 */

void *thread_routine(void *chunk)
{
	blur_portion((blur_portion_t *)chunk);
	pthread_exit(NULL);
}

/**
 * blur_image - blur the entire img
 *
 * @img_blur: portion of image to blur by one Thread
 * @img: the original img to full-blur
 * @kernel: pointer to convultion kernel to use
 *
 * Return: Nothing
 */

void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel)
{
	blur_portion_t *chunk = NULL;
	pthread_t tid[THREADS];
	int i;

	chunk = slicer(img_blur, img, kernel);
	for (i = 0; i < THREADS; i++)
	{
		if (pthread_create(tid + i, NULL, &thread_routine, chunk + i) != 0)
		{
			fprintf(stderr, "Failed to create threads\n");
			return;
		}
	}
	/* secure the Threads data race, make them wait with join */
	for (i = 0; i < THREADS; i++)
		if (pthread_join(tid[i], NULL) != 0)
			return;
}
