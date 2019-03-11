/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:34:04 by akoropet          #+#    #+#             */
/*   Updated: 2018/06/07 19:36:34 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*str;
	char		*dest;

	dest = dst;
	str = src;
	if (dest <= str)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = str[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			dest[i - 1] = str[i - 1];
			i--;
		}
	}
	return (dest);
}
