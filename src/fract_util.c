/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-18 15:10:28 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-18 15:10:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

t_complex	*create_complex(float real, float imag)
{
	t_complex	*out;
	
	out = malloc(sizeof(t_complex));
	out->imag = (_Float64x)imag;
	out->real = (_Float64x)real;
	return (out);
}

t_complex	*map_to_complex(const t_fract *fract, int col, int row)
{
	t_complex	*result;

	result = zeroit(malloc(sizeof(t_complex)), sizeof(t_complex));
	result->real = fract->plane->x_min
		+ (fract->plane->x_max - fract->plane->x_min)
			* col / (fract->width - 1);
	result->imag = fract->plane->y_min
		+ (fract->plane->y_max - fract->plane->y_min)
			* row / (fract->height - 1);
	return (result);
}

t_cplane	*create_cplane(_Float64x	x_min,
	_Float64x	x_max,
	_Float64x	y_min,
	_Float64x	y_max)
{
	t_cplane	*p;
	p = malloc(sizeof(t_cplane));
	if (!p)
		return (0);
	p->x_max = x_max;
	p->x_min = x_min;
	p->y_max = y_max;
	p->y_min  = y_min;
	return (p);
}

t_fract	*create_fract(int screen[2],
	t_cplane *plane,
	size_t (*fn)(const t_complex *, const size_t, const void *),
	void *data)
{
	t_fract	*p;

	p = malloc(sizeof(t_fract));
	if (!p)
		return (0);
	p->width = screen[0];
	p->height = screen[1];
	p->get_depth = fn;
	p->data = data;
	p->plane = plane;
	return (p);
}
