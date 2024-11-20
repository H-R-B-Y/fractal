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

t_fract	*fract_select(int argc, char **argv)
{
	if (!ft_strncmp(argv[0], "mandelbrot", 11))
		return (create_mandelbrot());
	else if (!ft_strncmp(argv[0], "julia", 6) && argc > 1)
		return (create_julia());
	
}
