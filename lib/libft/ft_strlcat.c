/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:24:46 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/23 20:47:47 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t a;

	i = 0;
	j = 0;
	a = 0;
	while (dst[i])
		i++;
	while (src[j])
		j++;
	if (i > size)
		return (j + size);
	while ((i + a + 1) < size && src[a])
	{
		dst[i + a] = src[a];
		a++;
	}
	dst[i + a] = '\0';
	return (i + j);
}
