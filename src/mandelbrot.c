/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-18 15:20:06 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-18 15:20:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

/*
Given a point in the complex plane c, 
repeat z[n + 1] = z[n]^2 + c until either max depth
or escape clause (distance from origin) is greater than 2
distance from origin is 
sqrt((z.real ^ 2) + (z.imag ^ 2))

escape clause can be reduced to
(z.real ^ 2) + (z.imag ^ 2) < 4 
*/
size_t	mandelrot(t_complex *c,
	const size_t max_depth,
	const void *data)
{
	size_t		iterations;
	_Float64x	temp_real;
	t_complex	z;
	
	z = (t_complex){0, 0};
	(void)data;
	iterations = 0;
	while (z.real * z.real + z.imag * z.imag < 4.0f
		&& iterations < max_depth)
	{
		temp_real = z.real * z.real - z.imag * z.imag + c->real;
		z.imag = 2.0 * z.real * z.imag + c->imag;
		z.real = temp_real;
		iterations++;
	}
	return (iterations);
}
