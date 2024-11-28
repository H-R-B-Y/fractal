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

void	scrdepth(double ydelta, t_sim *sim)
{
	sim->current_depth += ydelta;
	need_redraw(sim);
}

void	scroll_through(double xdelta, double ydelta, void *param)
{
	t_sim		*sim;
	t_complex	c;
	double		tempscale;

	sim = param;
	if (mlx_is_key_down(sim->mlx, MLX_KEY_LEFT_SHIFT)
		&& (scrdepth(ydelta, sim), 1))
		return ;
	mlx_get_mouse_pos(sim->mlx, &(sim->pos[0]), &(sim->pos[1]));
	if (sim->pos[0] < 0 || sim->pos[0] >= sim->canvas->width
		||sim->pos[1] < 0 || sim->pos[1] >= sim->canvas->height)
		return ;
	tempscale = 0.9 + 0.2 * (ydelta > 0);
	c = map_to_complex(sim->current_fract, sim->pos[0], sim->pos[1]);
	sim->current_fract->plane->x_max = c.real
		+ (sim->current_fract->plane->x_max - c.real) * tempscale;
	sim->current_fract->plane->x_min = c.real
		+ (sim->current_fract->plane->x_min - c.real) * tempscale;
	sim->current_fract->plane->y_max = c.imag
		+ (sim->current_fract->plane->y_max - c.imag) * tempscale;
	sim->current_fract->plane->y_min = c.imag
		+ (sim->current_fract->plane->y_min - c.imag) * tempscale;
	sim->scale *= tempscale;
	need_redraw(sim);
}

void	translate_viewport(t_sim *sim)
{
	t_complex	pos[2];

	pos[0] = map_to_complex(sim->current_fract,
		sim->mos.start[0], sim->mos.start[1]);
	pos[1] = map_to_complex(sim->current_fract,
		sim->mos.end[0], sim->mos.end[1]);
	pos[0] = (t_complex){pos[0].real - pos[1].real,
		pos[0].imag - pos[1].imag};
	sim->current_fract->plane->x_max -= pos[0].real;
	sim->current_fract->plane->y_max -= pos[0].imag;
	sim->current_fract->plane->x_min -= pos[0].real;
	sim->current_fract->plane->y_min -= pos[0].imag;
	ft_memset(&sim->mos, 0, sizeof(t_mdata));
	need_redraw(sim);
}

void	click_hook(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param)
{
	t_sim	*sim;
	int32_t pos[2];

	sim = param;
	if (button == MLX_MOUSE_BUTTON_LEFT
		&& action == MLX_PRESS
		&& !ft_memcmp(&sim->mos.start,
			(int32_t[2]){0, 0}, sizeof(int32_t) * 2))
		mlx_get_mouse_pos(sim->mlx,
			&sim->mos.start[0], &sim->mos.start[1]);
	else if (button == MLX_MOUSE_BUTTON_LEFT
		&& action == MLX_RELEASE)
	{
		mlx_get_mouse_pos(sim->mlx, &sim->mos.end[0], &sim->mos.end[1]);
		translate_viewport(sim);
	}
}
