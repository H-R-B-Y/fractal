/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 15:35:59 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-11 15:35:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42.h"

uint32_t mlx_get_pixel(mlx_image_t *img, size_t x, size_t y)
{
	uint8_t *pixelstart;
	uint32_t color;
	if (!img || x >= img->width || y >= img->height)
		return 0;
	color = 0;
	pixelstart = &img->pixels[(y * img->width + x) * sizeof(int32_t)];
	color |= (uint32_t)pixelstart[0] << 24;
	color |= (uint32_t)pixelstart[1] << 16;
	color |= (uint32_t)pixelstart[2] << 8;
	color |= (uint32_t)pixelstart[3];
	return (color);
}
