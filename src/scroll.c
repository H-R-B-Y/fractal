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
	t_complex	*c;

	sim = param;
	mlx_get_mouse_pos(sim->mlx, &(sim->pos[0]), &(sim->pos[1]));
	if (sim->pos[0] < 0 || sim->pos[0] >= sim->canvas->width
		||sim->pos[1] < 0 || sim->pos[1] >= sim->canvas->height)
		return ;
	sim->tempscale = 0.9 + 0.2 * (ydelta > 0);
	c = map_to_complex(sim->current_fract, sim->pos[0], sim->pos[1]);
	sim->current_fract->plane->x_max = c->real
		+ (sim->current_fract->plane->x_max - c->real) * sim->tempscale;
	sim->current_fract->plane->x_min = c->real
		+ (sim->current_fract->plane->x_min - c->real) * sim->tempscale;
	sim->current_fract->plane->y_max = c->imag
		+ (sim->current_fract->plane->y_max - c->imag) * sim->tempscale;
	sim->current_fract->plane->y_min = c->imag
		+ (sim->current_fract->plane->y_min - c->imag) * sim->tempscale;
	sim->scale *= sim->tempscale;
	sim->redraw += 1;
	need_redraw(sim);
	free(c);
}
