/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-18 15:26:46 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-18 15:26:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

size_t		julia(const t_complex *st,
	const size_t max_depth,
	const void *constant)
{
	size_t	iterations;
	_Float64x	temp_real;
	t_complex	c;
	t_complex	z;

	c = *((t_complex *)constant);
	z = *st;
	iterations = 0;
	while (z.real * z.real + z.imag * z.imag < 4.0f
		&& iterations < max_depth)
	{
		temp_real = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2.0 * z.real * z.imag + c.imag;
		z.real = temp_real;
		iterations++;
	}
	return (iterations);
}
