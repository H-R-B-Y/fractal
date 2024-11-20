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

// Example for P(z) = z^3 - 1
t_complex polynomial(t_complex z) {
	return (t_complex){
		.real = z.real * z.real * z.real - 3 * z.real * z.imag * z.imag - 1,
		.imag = 3 * z.real * z.real * z.imag - z.imag * z.imag * z.imag
	};
}

t_complex derivative(t_complex z) {
	return (t_complex){
		.real = 3 * (z.real * z.real - z.imag * z.imag),
		.imag = 6 * z.real * z.imag
	};
}

t_complex newton_iterate(t_complex z, t_complex (*P)(t_complex), t_complex (*P_prime)(t_complex)) {
	t_complex p = P(z);
	t_complex p_prime = P_prime(z);
	t_complex correction = {
		.real = (p.real * p_prime.real + p.imag * p_prime.imag) /
				(p_prime.real * p_prime.real + p_prime.imag * p_prime.imag),
		.imag = (p.imag * p_prime.real - p.real * p_prime.imag) /
				(p_prime.real * p_prime.real + p_prime.imag * p_prime.imag)
	};
	return (t_complex){.real = z.real - correction.real, .imag = z.imag - correction.imag};
}

bool close_to(t_complex z, t_complex root, double epsilon) {
	return ((z.real - root.real) * (z.real - root.real) + 
			(z.imag - root.imag) * (z.imag - root.imag)) < epsilon * epsilon;
}

size_t newton_depth(const t_complex *c, size_t max_depth, const void *data) {
	const t_complex *roots = data; // Array of known roots
	size_t iterations = 0;
	t_complex z = *c;

	while (iterations < max_depth) {
		z = newton_iterate(z, polynomial, derivative);
		for (int i = 0; i < 3; i++) {
			if (close_to(z, roots[i], 1e-6))
				return iterations + i * max_depth; // Combine depth with root index
		}
		iterations++;
	}
	return max_depth;
}
