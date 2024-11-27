/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 22:12:46 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 22:12:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fract.h"


t_complex polynomial4(t_complex *z) {
	double cosh_real = cosh(z->real) * cos(z->imag); // Real part of cosh(z)
	double cosh_imag = sinh(z->real) * sin(z->imag); // Imaginary part of cosh(z)
	t_complex cosh_z = {.real = cosh_real, .imag = cosh_imag};

	t_complex term1 = complex_add(cosh_z, (t_complex){.real = -1, .imag = 0}); // cosh(z) - 1
	return ((t_complex){term1.real, term1.imag});
}

t_complex derivative4(t_complex *z) {
	double sinh_real = sinh(z->real) * cos(z->imag); // Real part of sinh(z)
	double sinh_imag = cosh(z->real) * sin(z->imag); // Imaginary part of sinh(z)
	t_complex sinh_z = {.real = sinh_real, .imag = sinh_imag};

	return ((t_complex){sinh_z.real, sinh_z.imag}); // sinh(z)
}

void	delete4(void *data)
{
	t_polynomial *p;

	p = data;
	free(p->roots);
	free(p);
}

t_fract	*poly4(t_sim *sim)
{
	t_polynomial *p;
	t_fract	*out;

	p = malloc(sizeof(t_polynomial));
	p->derivative = derivative4;
	p->polynomial = polynomial4;
	p->roots = malloc(sizeof(t_complex) * 5);
	p->roots[0] = (t_complex){.real = 0.0, .imag = 0.0};
	p->roots[1] = (t_complex){.real = 0.0, .imag = 2 * MY_PI};
	p->roots[2] = (t_complex){.real = 0.0, .imag = -2 * MY_PI};
	p->roots[3] = (t_complex){.real = 0.0, .imag = 4 * MY_PI};
	p->roots[4] = (t_complex){.real = 0.0, .imag = -4 * MY_PI};
	p->root_count = 5;
	out = create_fract((int[2]){sim->mlx->width, sim->mlx->height},
		create_cplane(-2.5f, 2.5f, -2.5f, 2.5f), newton_depth, p);
	out->del = delete4;
	return (out);
}