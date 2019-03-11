/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:13:50 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 19:58:34 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *i;

	if (size == 0)
		return (0);
	i = (void *)malloc(size);
	if (i == 0)
		return (0);
	i = ft_memset(i, '\0', size);
	return (i);
}
