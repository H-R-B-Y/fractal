/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 15:26:01 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 15:26:01 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

t_complex newton_iterate(t_complex *z, t_polynomial *poly)
{
	t_complex p = poly->polynomial(z); // P(z)
	t_complex p_prime = poly->derivative(z); // P'(z)

	t_complex correction = {
		.real = (p.real * p_prime.real + p.imag * p_prime.imag) /
				(p_prime.real * p_prime.real + p_prime.imag * p_prime.imag),
		.imag = (p.imag * p_prime.real - p.real * p_prime.imag) /
				(p_prime.real * p_prime.real + p_prime.imag * p_prime.imag)
	};

	return (t_complex){
		.real = z->real - correction.real,
		.imag = z->imag - correction.imag
	};
}


bool close_to(t_complex z, t_complex root, double epsilon)
{
	return ((z.real - root.real) * (z.real - root.real) + 
			(z.imag - root.imag) * (z.imag - root.imag)) < epsilon * epsilon;
}

size_t newton_depth(t_complex *z, size_t max_depth, const void *data)
{
	t_polynomial *poly = (t_polynomial *)data;
	size_t iterations = 0;

	while (iterations < max_depth) {
		t_complex p = poly->polynomial(z);
		t_complex p_prime = poly->derivative(z);
		t_complex correction = {
			(p.real * p_prime.real + p.imag * p_prime.imag) /
					(p_prime.real * p_prime.real + p_prime.imag * p_prime.imag),
			(p.imag * p_prime.real - p.real * p_prime.imag) /
					(p_prime.real * p_prime.real + p_prime.imag * p_prime.imag)
		};
		z->real -= correction.real;
		z->imag -= correction.imag;
		for (size_t i = 0; i < poly->root_count; i++) {
			t_complex root = poly->roots[i];
			double distance = sqrt((z->real - root.real) * (z->real - root.real) +
								(z->imag - root.imag) * (z->imag - root.imag));
			if (distance < 1e-6) {
				return (iterations + i); // Include root index in depth for coloring
			}
		}
		iterations++;
	}
	return max_depth; // Max depth if it doesn't converge
}
