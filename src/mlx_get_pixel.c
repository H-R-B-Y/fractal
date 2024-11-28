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
	if (!img || x >= img->width || y >= img->height)
		return 0;

	uint8_t *pixelstart = &img->pixels[(y * img->width + x) * sizeof(int32_t)];
	uint32_t color = 0;

	color |= (uint32_t)pixelstart[0] << 24; // Red
	color |= (uint32_t)pixelstart[1] << 16; // Green
	color |= (uint32_t)pixelstart[2] << 8;  // Blue
	color |= (uint32_t)pixelstart[3];       // Alpha

	return (color);
}