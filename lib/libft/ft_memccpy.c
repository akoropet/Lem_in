/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 21:02:55 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/23 21:21:35 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*q;
	unsigned const char	*a;
	unsigned char		z;

	i = 0;
	q = (unsigned char *)dst;
	a = (unsigned const char *)src;
	z = (unsigned char)c;
	while (i < n)
	{
		q[i] = a[i];
		if (a[i] == z)
			return (q + (i + 1));
		i++;
	}
	return (NULL);
}
