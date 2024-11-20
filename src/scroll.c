/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 13:48:19 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 13:48:19 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

void scroll_through(double xdelta, double ydelta, void *param)
{
	t_sim		*sim;
	int32_t		pos[2];
	float		scale;
	t_complex	*c;

	sim = param;
	mlx_get_mouse_pos(sim->mlx, &(pos[0]), &(pos[1]));
	if (pos[0] < 0 || pos[0] >= sim->canvas->width
		||pos[1] < 0 || pos[1] >= sim->canvas->height)
		return ;
	scale = 0.9 + 0.2 * (ydelta > 0);
	c = map_to_complex(sim->current_fract, pos[0], pos[1]);
	sim->current_fract->plane->x_max = c->real
		+ (sim->current_fract->plane->x_max - c->real) * scale;
	sim->current_fract->plane->x_min = c->real
		+ (sim->current_fract->plane->x_min - c->real) * scale;
	sim->current_fract->plane->y_max = c->imag
		+ (sim->current_fract->plane->y_max - c->imag) * scale;
	sim->current_fract->plane->y_min = c->imag
		+ (sim->current_fract->plane->y_min - c->imag) * scale;
	sim->scale *= scale;
	sim->redraw += 0.1;
	free(c);
}
