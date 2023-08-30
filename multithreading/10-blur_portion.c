#include "multithreading.h"
#include <sys/types.h>

/**
 * blur_portion - blurs a portion of an image using a GAUSSIAN BLUR
 *
 * @portion: pointer to data struct blur_portion_t
 */

void blur_portion(blur_portion_t const *portion)
{
	size_t j, i;

	if (!portion || !portion->img || !portion->img_blur ||
		!portion->kernel)
		return;

	/* loop through given portion of img */
	for (j = portion->y; j < portion->y + portion->h; j++)
		for (i = portion->x; i < portion->x + portion->w; i++)
			perform_bluring(portion->img, portion->img_blur, portion->kernel,
							i, j);
}

void perform_bluring(const img_t *img, img_t *new_img, const kernel_t *kernel,
					 size_t x, size_t y)
{
	float divider = 0, avg_r = 0, avg_g = 0, avg_b = 0;
	size_t radius = 0, pos_i = 0, i = 0, j;
	ssize_t pos_x = 0, pos_y = 0;

	/* radius is distance from center pixel to edge cells */
	/* here the life is sweet because we prefer and odd-sized kernel */
	radius = kernel->size / 2;

	/* place the kernel on portion and loop through it */
	for (pos_y = y - radius; i < kernel->size; pos_y++, i++)
		for (j = 0, pos_x = x - radius; j < kernel->size; pos_x++, j++)
		{
			/* check if we are inside boundaries */
			if (pos_y >= 0 && (size_t)pos_y < img->h &&
				pos_x >= 0 && (size_t)pos_x < img->w)
			{
				/* update divider and pos_i, formula works thanks to 2D array */
				/* that is storing pixels postion */
				divider += kernel->matrix[i][j];
				pos_i = (pos_y * img->w) + pos_x;
				/* update each r,g,b color average as looping through */
				/* multiply corresponding kernel cell by img cell */
				avg_r += img->pixels[pos_i].r * kernel->matrix[i][j];
				avg_g += img->pixels[pos_i].g * kernel->matrix[i][j];
				avg_b += img->pixels[pos_i].b * kernel->matrix[i][j];
			}
		}
	/* divide each average by average of all kernel cells */
	avg_r /= divider;
	avg_g /= divider;
	avg_b /= divider;

	/* set those values in new_img , don't mess up the original one, thug !*/
	/* ( set i 'cursor' in new_img at proper position) */
	pos_i = (y * new_img->w) + x;
	new_img->pixels[pos_i].r = (uint8_t)avg_r;
	new_img->pixels[pos_i].g = (uint8_t)avg_g;
	new_img->pixels[pos_i].b = (uint8_t)avg_b;
}
