/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 14:31:35 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 14:31:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

void	redraw_hook(void *param)
{
	t_sim	*sim;
	int		iter;

	sim = param;
	if (sim->recalc)
		process_frame(sim->depth_array, sim->current_fract, sim);
	if (sim->redraw)
		draw_depth_map(sim);
}
