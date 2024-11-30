/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-18 15:35:48 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-18 15:35:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

void	need_redraw(t_sim *sim)
{
	sim->redraw = 1;
	sim->iter[0] = 0;
	sim->iter[1] = 0;
}

uint32_t	**default_colour_array(void)
{
	uint32_t	**t;

	t = malloc(3 * sizeof(uint32_t *));
	if (!t)
		return (0);
	t[0] = malloc(sizeof(uint32_t));
	*t[0] = 0x000000FF;
	t[1] = malloc(sizeof(uint32_t));
	*t[1] = 0x20AF20FF;
	t[2] = 0;
	return (t);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = zeroit(malloc(sizeof(t_sim)), sizeof(t_sim));
	sim->mlx = mlx_init(SCRNWIDTH, SCRNHEIGHT, "fractol", 0);
	sim->canvas = mlx_new_image(sim->mlx, sim->mlx->width, sim->mlx->height);
	mlx_image_to_window(sim->mlx, sim->canvas, 0, 0);
	sim->scale = 1;
	sim->draw_steps = SCRNHEIGHT * SCRNWIDTH;
	sim->max_depth = 50;
	sim->fract = fract_select(argc - 1, &argv[1]);
	sim->colours = default_colour_array();
	sim->get_colour = defaultgetcolour;
	if (!sim->fract || !sim->fract->plane || !sim->canvas)
		return (destory_sim(sim), 1);
	need_redraw(sim);
	mlx_scroll_hook(sim->mlx, scroll_through, sim);
	mlx_loop_hook(sim->mlx, redraw_hook, sim);
	mlx_mouse_hook(sim->mlx, click_hook, sim);
	mlx_loop(sim->mlx);
	destory_sim(sim);
	return (0);
}
