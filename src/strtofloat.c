/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtofloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:58:09 by hbreeze           #+#    #+#             */
/*   Updated: 2025/01/29 14:25:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract.h"


float	strtofloat(const char *str)
{
	float	output;
	char	*tmp;
	char	*sep;
	float	div;

	if (!str)
		return (0.0f);
	tmp = ft_strdup(str);
	sep = ft_strtrim(tmp, " 	f");
	free(tmp);
	tmp = sep;
	sep = ft_strchr(tmp, '.');
	if (!sep)
		return ((float)ft_atoi(str));
	*sep = '\0';
	sep++;
	output = ft_atoi(sep);
	div = ft_strlen(sep);
	while (div--)
		output /= 10;
	output += ft_atoi(tmp);
	free(tmp);
	return ((float)output);
}
