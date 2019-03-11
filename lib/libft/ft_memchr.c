/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:53:49 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 18:20:24 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*q;
	size_t				i;
	unsigned char		k;

	i = 0;
	q = (unsigned char *)s;
	k = (unsigned char)c;
	while (i < n)
	{
		if (*q == k)
			return (q);
		q++;
		i++;
	}
	return (NULL);
}
