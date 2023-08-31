#ifndef __MULTITHREADS__
#define __MULTITHREADS__

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <stdint.h>

#include "list.h"

/**
 * struct pixel_s - RGS pixel
 *
 * @r: Red component
 * @g: Green component
 * @b: Blue component
 */

typedef struct pixel_s
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel_t;

/** struct img_s - Image
 *
 * @w: image width
 * @h: image height
 * @pixels: Array of pixels
 */

typedef struct img_s
{
	size_t w;
	size_t h;
	pixel_t *pixels;
} img_t;

/**
 * struct kernel_s - Convolution kernel
 *
 * @size: size of the matrix (both width and height)
 * @matrix: Kernel matrix
 */

typedef struct kernel_s
{
	size_t size;
	float **matrix;
} kernel_t;

/**
 * struct blur_portion_s - Information needed to blur a portion
 * of an image
 *
 * @img: Source image
 * @img_blur: Destination image
 * @x: X position of the portion in image
 * @y: Y position of the portion in image
 * @w: width of the portion
 * @h: height of the portion
 * @kernel: Convolution kernel to use
 */

typedef struct blur_portion_s
{
	img_t const *img;
	img_t *img_blur;
	size_t x;
	size_t y;
	size_t w;
	size_t h;
	kernel_t const *kernel;
} blur_portion_t;

/******************
 * *************
 * *******
 * struct for pool of thread -- final task
 *
 * function pointer declaration, task_entry_t represents that pointer to a function
 * Takes a single argument of type " void * ", typically used in threading or task scheduling
 * => we want to execute functions in parallel and pass data around
 * void* // *task_entry_t // (void *) Three little pigs, uh birds I meant ! (Bob Marley)
 */

typedef void *(*task_entry_t)(void *);

/**
 * enum task_status_e - Task statuses
 *
 * @PENDING: Task is pending
 * @STARTED: Task has been started
 * @SUCCESS: Task has been completed successfully
 * @FAILURE: Task has completed with issues
 */

typedef enum task_status_e
{
	PENDING = 0,
	STARTED,
	SUCCESS,
	FAILURE,
} task_status_t;

/**
 * struct task_s - Executable task structure
 *
 * @entry: Pointer to a function to serve as the task entry
 * @param: Address to a custion content to be passed to the entry function
 * @status: Task status, default to PENDING
 * @result: Stores the return value of the entry function
 * @lock: Task mutex
 */

typedef struct task_s
{
	task_entry_t entry;
	void *param;
	task_status_t status;
	void *result;
	pthread_mutex_t lock;
} task_t;

/* functions prototypes */
void *thread_entry(void *arg);
int tprintf(char const *format, ...);

/* Blurring functions */
void blur_portion(blur_portion_t const *portion);
void perform_bluring(const img_t *img, img_t *new_img, const kernel_t *kernel,
					 size_t x, size_t y);

/* prime factors functions */
list_t *prime_factors(char const *s);
/* prime factors with pool of threads */
task_t *create_task(task_entry_t entry, void *param);
void destroy_task(task_t *task);
void *exec_tasks(list_t const *tasks);

#endif /* __MULTITHREADS__ */
