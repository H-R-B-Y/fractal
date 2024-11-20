/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 14:31:35 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 14:31:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

void	need_redraw(t_sim *sim)
{
	sim->redraw = 1;
	sim->canvas_scaled = 0;
	sim->iter[0] = 0;
	sim->iter[1] = 0;
	sim->current_depth = 50 + 10 * log10(1.0 / sim->scale);
	if (!sim->pre_img)
		sim->pre_img = mlx_new_image(sim->mlx,
			sim->current_fract->width, sim->current_fract->height);
}

void redraw_scaled_image(t_img *canvas, t_sim *sim)
{
	int	scaled_width;
	int	scaled_height;
	int	offset_x;
	int	offset_y;

	if (sim->tempscale == 0.9)
		sim->tempscale = 1.1;
	else if (sim->tempscale = 1.1)
		sim->tempscale = 0.9;
	// Calculate scaled dimensions
	scaled_width = canvas->width * sim->tempscale;
	scaled_height = canvas->height * sim->tempscale;

	// Calculate offsets to center the scaling on the mouse position
	offset_x = (sim->pos[0] - canvas->width / 2) * (1 - sim->tempscale);
	offset_y = (sim->pos[1] - canvas->height / 2) * (1 - sim->tempscale);

	// Resize the canvas
	mlx_resize_image(sim->canvas, scaled_width, scaled_height);

	// Apply the calculated offsets to the canvas instance
	sim->canvas->instances[0].x = offset_x;
	sim->canvas->instances[0].y = offset_y;

	// Mark the canvas as scaled
	sim->canvas_scaled = 1;
}

void	swap_images(t_sim *sim)
{
	if (!sim || !sim->pre_img)
		return ;
	mlx_delete_image(sim->mlx, sim->canvas);
	mlx_image_to_window(sim->mlx, sim->pre_img, 0, 0);
	sim->canvas = sim->pre_img;
	sim->pre_img = 0;
}

void	draw_pixel_fr(t_sim *sim, t_img *img, int32_t x, int32_t y)
{
	t_complex	*complex;
	size_t		depth;
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

	complex = map_to_complex(sim->current_fract, x, y);
	depth = sim->current_fract->get_depth(complex, sim->current_depth, sim->current_fract->data);
	free(complex);
	if (depth + 1 < sim->current_depth)
		mlx_put_pixel(img, x, y, colors[depth % 8]);
	else if (depth + 1 >= sim->current_depth)
		mlx_put_pixel(img, x, y, colors[4]);
}

void	redraw_hook(void *param)
{
	t_sim	*sim;
	int		iter;

	sim = param;
	if (!sim || !sim->redraw)
		return ;
	// if (!sim->canvas_scaled)
	// 	redraw_scaled_image(sim->canvas, sim);
	iter = 0;
	while (iter < sim->draw_steps)
	{
		if (sim->iter[1] == sim->current_fract->width)
		{
			sim->iter[0]++;
			sim->iter[1] = 0;
		}
		if (sim->iter[0] == sim->current_fract->height)
		{
			sim->redraw = 0;
			// swap_images(sim);
			return ;
		}
		draw_pixel_fr(sim, sim->canvas, sim->iter[1], sim->iter[0]);
		sim->iter[1]++;
		iter++;
	}
}
