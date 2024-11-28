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

int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = zeroit(malloc(sizeof(t_sim)), sizeof(t_sim));
	sim->mlx = mlx_init(SCRNWIDTH, SCRNHEIGHT, "fractol", 0);
	sim->canvas = mlx_new_image(sim->mlx, sim->mlx->width, sim->mlx->height);
	mlx_image_to_window(sim->mlx, sim->canvas, 0, 0);
	sim->scale = 1;
	sim->draw_steps = 500000;
	sim->current_depth = 50;
	sim->current_fract = fract_select(argc - 1, &argv[1]);
	if (!sim->current_fract || !sim->current_fract->plane || !sim->canvas)
		return (destory_sim(sim), 1);
	need_redraw(sim);
	mlx_scroll_hook(sim->mlx, scroll_through, sim);
	mlx_loop_hook(sim->mlx, redraw_hook, sim);
	mlx_mouse_hook(sim->mlx, click_hook, sim);
	mlx_loop(sim->mlx);
	destory_sim(sim);
	return (0);
}

// // sim->current_fract = create_fract((int[2]){1920, 1080},
// // 	create_cplane(-2.5f, 2.5f, -2.5f, 2.5f), mandelrot, 0);
// // sim->current_fract = create_fract((int[2]){1920, 1080},
// // 	create_cplane(-2.5f, 2.5f, -2.5f, 2.5f), julia, create_complex(-0.8, 0.156f));
// sim->current_fract = create_fract((int[2]){1920, 1080},
// 	create_cplane(-2.5f, 2.5f, -2.5f, 2.5f), newton_depth, (t_complex[3]){{.real = 1.0, .imag = 0.0},
// 	{.real = -0.5, .imag = sqrt(3) / 2.0},
// 	{.real = -0.5, .imag = -sqrt(3) / 2.0}});
