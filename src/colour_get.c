/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-30 01:16:07 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-30 01:16:07 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"

__uint8_t	rgba_get_red(__uint32_t colour)
{
	return ((colour & 0xFF000000) >> 24);
}

__uint8_t	rgba_get_green(__uint32_t colour)
{
	return ((colour & 0x00FF0000) >> 16);
}

__uint8_t	rgba_get_blue(__uint32_t colour)
{
	return ((colour & 0x0000FF00) >> 8);
}

__uint8_t	rgba_get_alph(__uint32_t colour)
{
	return (colour & 0x000000FF);
}
