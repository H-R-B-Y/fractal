/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 18:44:26 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 18:44:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

void	draw_depth_map(t_sim *sim)
{
	int32_t	iter[2];
	const uint32_t colors[] = {
		0xFF0000FF, // Red
		0x00FF00FF, // Green
		0x0000FFFF, // Blue
		0xFFFF00FF, // Yellow
		0x000000FF, // Black
		0xFF00FFFF, // Magenta
		0x00FFFFFF, // Cyan
		0xFFFFFFFF // White
	};

	iter[0] = 0;
	while (iter[0] < sim->current_fract->height)
	{
		iter[1] = 0;
		while (iter[1] < sim->current_fract->width)
		{
			mlx_put_pixel(sim->canvas, iter[1], iter[0],
				colors[sim->depth_array[(sim->current_fract->width * iter[0]) + iter[1]] % 8]);
			iter[1]++;
		}
		iter[0]++;
	}
	sim->redraw = 0;
}

void	*compute_depth(void *arg)
{
	t_thread_data	*d;
	int				index;
	t_complex		c;

	d = arg;
	index = 0;
	while (index < d->count)
	{
		c = map_to_complex(d->fract, (d->offset + index) % d->fract->width, (d->offset + index) / d->fract->width);
		d->data[d->offset + index] = d->fract->get_depth(&c, d->fract->max_depth, d->fract->data);
		index++;
	}
	return ((void *)0);
}

// Function to process a new frame
void	process_frame(int *data, t_fract *f, t_sim *sim) {
	pthread_t threads[NUM_THREADS];
	t_thread_data thread_data[NUM_THREADS];
	
	// Split the work among the threads
	int pixels_per_thread = (f->width * f->height) / NUM_THREADS;
	
	for (int i = 0; i < NUM_THREADS; i++) {
		thread_data[i].offset = i * pixels_per_thread;
		thread_data[i].count = pixels_per_thread;
		thread_data[i].data = data;
		thread_data[i].fract = f;
		
		// Create threads for each portion of the canvas
		pthread_create(&threads[i], NULL, compute_depth, &thread_data[i]);
	}

	// Handle remaining pixels (if not evenly divisible)
	int remaining_pixels = (f->width * f->height) % NUM_THREADS;
	if (remaining_pixels > 0) {
		int start_offset = NUM_THREADS * pixels_per_thread;
		for (int i = 0; i < remaining_pixels; i++) {
			int x = (start_offset + i) % f->width;
			int y = (start_offset + i) / f->width;
			t_complex c = map_to_complex(f, x, y);
			data[start_offset + i] = f->get_depth(&c, f->max_depth, f->data);
		}
	}
	
	// Wait for all threads to finish
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	sim->recalc = 0;
	sim->redraw = 1;
}
