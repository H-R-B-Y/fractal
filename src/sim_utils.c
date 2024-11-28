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
#include <math.h>

void	draw_pixel_fr(t_sim *sim, t_img *img, int32_t x, int32_t y)
{
	t_complex	complex;
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
	depth = sim->current_fract->get_depth(&complex, sim->current_depth,
		sim->current_fract->data);
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
			return ;
		}
		draw_pixel_fr(sim, sim->canvas, sim->iter[1], sim->iter[0]);
		sim->iter[1]++;
		iter++;
	}
}
