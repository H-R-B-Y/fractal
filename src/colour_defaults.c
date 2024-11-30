/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_defaults.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-30 01:24:28 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-30 01:24:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

float	normalize(float from, float too, float t)
{
	return ((t - from) / (too - from));
}


uint32_t	defaultgetcolour(t_sim *sim, size_t depth)
{
	float	norm;

	norm = normalize(0, sim->max_depth, depth);
	return (lerp_colour(*sim->colours[0], *sim->colours[1], norm));
}
