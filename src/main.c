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
#include <math.h>

void	temp_draw(t_sim *sim, t_img *img, t_fract *f)
{
	size_t		iter[2];
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
	float	md;

	iter[0] = 0;
	md = 50 + 10 * log10(1.0 / sim->scale);
	while (iter[0] < img->height)
	{
		iter[1] = 0;
		while (iter[1] < img->width)
		{
			complex = map_to_complex(f, iter[1], iter[0]);
			depth = f->get_depth(complex, md, f->data);
			free(complex);
			if (depth + 1 < md)
				mlx_put_pixel(img, iter[1], iter[0], 
			colors[depth % 8]);
			else if (depth + 1 >= md)
				mlx_put_pixel(img, iter[1], iter[0], 
			colors[4]);
			iter[1]++;
		}
		iter[0]++;
	}
	if (!img || !f)
		return ;
}

void	needs_redraw(void *param)
{
	t_sim	*sim;

	sim = param;
	if (sim->redraw > 0)
		sim->redraw -= sim->mlx->delta_time;
	if (sim->redraw < 0)
	{
		temp_draw(sim, sim->canvas, sim->current_fract);
		sim->redraw = 0;
	}
}
size_t newton_depth(const t_complex *c, size_t max_depth, const void *data);
int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = zeroit(malloc(sizeof(t_sim)), sizeof(t_sim));
	sim->mlx = mlx_init(SCRNWIDTH, SCRNHEIGHT, "fractol", 0);
	sim->canvas = mlx_new_image(sim->mlx, sim->mlx->width, sim->mlx->height);
	mlx_image_to_window(sim->mlx, sim->canvas, 0, 0);
	sim->scale = 1;
	sim->draw_steps = 500000;
	sim->current_fract = fract_select(argc - 1, &argv[1]);
	if (!sim->current_fract || !sim->current_fract->plane || !sim->canvas)
		return (destory_sim(sim), 1);
	temp_draw(sim, sim->canvas, sim->current_fract);
	mlx_scroll_hook(sim->mlx, scroll_through, sim);
	mlx_loop_hook(sim->mlx, redraw_hook, sim);
	temp_draw(sim, sim->canvas, sim->current_fract);
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
