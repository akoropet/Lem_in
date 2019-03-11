/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:46:25 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/23 20:54:39 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t			i;
	unsigned char	*q;
	unsigned char	*a;

	i = 0;
	q = (unsigned char *)dst;
	a = (unsigned char *)src;
	while (i < n)
	{
		q[i] = a[i];
		i++;
	}
	return (dst);
}
