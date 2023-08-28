#ifndef __MULTITHREADS__
#define __MULTITHREADS__

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <stdint.h>

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

/* functions prototypes */
void *thread_entry(void *arg);

#endif /* __MULTITHREADS__ */
