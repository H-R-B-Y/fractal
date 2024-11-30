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
	uint32_t	colour;
	size_t		depth;

	complex = map_to_complex(sim->fract, x, y);
	depth = sim->fract->get_depth(&complex, sim->max_depth,
		sim->fract->data);
	colour = sim->get_colour(sim, depth);
	mlx_put_pixel(img, x, y, colour);
}

void	redraw_hook(void *param)
{
	t_sim		*sim;
	uint32_t	iter;

	sim = param;
	if (!sim || !sim->redraw)
		return ;
	iter = 0;
	while (iter < sim->draw_steps)
	{
		if (sim->iter[1] == sim->fract->width)
		{
			sim->iter[0]++;
			sim->iter[1] = 0;
		}
		if (sim->iter[0] == sim->fract->height)
		{
			sim->redraw = 0;
			return ;
		}
		draw_pixel_fr(sim, sim->canvas, sim->iter[1], sim->iter[0]);
		sim->iter[1]++;
		iter++;
	}
}
