/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 15:37:06 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 15:37:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

void	print_usage(void)
{
	ft_putendl_fd("Error: Invalid usage.", 2);
	ft_putendl_fd("Usage: ./PROGRAMNAME {fractal name} <options for fractal>", 1);
	ft_putendl_fd("Fractals:", 1);
	ft_putendl_fd("	mandelbrot.\n		options: none.", 1);
	ft_putendl_fd("	julia.", 1);
	ft_putstr_fd("		options: {float: real part of complex number c}", 1);
	ft_putendl_fd(", <float: imaginary part of complex number c>", 1);
}

t_fract	*create_mandelbrot()
{
	t_fract	*output;

	output = create_fract((int[2]){SCRNWIDTH, SCRNHEIGHT},
		create_cplane(-2.0, 2.0, -2.0, 2.0), mandelrot, 0);
	return (output);
}

t_fract	*create_julia(int argc, char **argv)
{
	t_fract	*output;
	float	input[2];

	input[0] = strtofloat(argv[0]);
	input[1] = strtofloat(argv[1]);
	output = create_fract((int[2]){SCRNWIDTH, SCRNHEIGHT},
		create_cplane(-2.0, 2.0, -2.0, 2.0), julia, 
		create_complex(input[0], input[1]));
	output->del = free;
	return (output);
}

t_fract	*fract_select(int argc, char **argv)
{
	if (!ft_strncmp(argv[0], "mandelbrot", 11))
		return (create_mandelbrot());
	else if (!ft_strncmp(argv[0], "julia", 6) && argc >= 3)
		return (create_julia(argc - 1, &argv[1]));
	else
		print_usage();
	return (0);
}
