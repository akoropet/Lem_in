/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 19:17:43 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 18:22:07 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	q;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)b;
	q = (unsigned char)c;
	while (i < n)
	{
		a[i] = q;
		i++;
	}
	return (b);
}
