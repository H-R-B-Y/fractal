/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 20:07:53 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 20:07:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(t_list *lst, size_t index)
{
	if (!lst)
		return (0);
	while (index-- && lst)
		lst = lst->next;
	return (lst);
}
