/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 21:58:15 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 21:58:15 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

t_complex complex_mul(t_complex a, t_complex b)
{
	return ((t_complex){
		.real = a.real * b.real - a.imag * b.imag,
		.imag = a.real * b.imag + a.imag * b.real
	});
}

t_complex complex_add(t_complex a, t_complex b)
{
	return ((t_complex){
		.real = a.real + b.real,
		.imag = a.imag + b.imag
	});
}

t_complex complex_scale(t_complex z, double scale)
{
	return ((t_complex){
		.real = z.real * scale,
		.imag = z.imag * scale
	});
}

