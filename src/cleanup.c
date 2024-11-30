/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 14:18:53 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-20 14:18:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

void	ft_deletearray(void **splt)
{
	int	index;

	index = 0;
	while(splt && splt[index])
		free(splt[index++]);
	free(splt);
}

void	destory_fract(t_fract *fract)
{
	if (!fract)
		return ;
	if (fract->plane)
		free(fract->plane);
	if (fract->del)
		fract->del(fract->data);
	free(fract);
}

void	destory_sim(t_sim *sim)
{
	if (!sim)
		return ;
	if (sim->canvas)
		mlx_delete_image(sim->mlx, sim->canvas);
	if (sim->fract)
		destory_fract(sim->fract);
	if (sim->mlx)
		mlx_terminate(sim->mlx);
	if (sim->colours)
		ft_deletearray((void **)sim->colours);
	free(sim);
}
