/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 21:46:09 by akoropet          #+#    #+#             */
/*   Updated: 2018/04/11 15:48:43 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *q;

	q = NULL;
	if (c == '\0')
	{
		while (*s != c)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == c)
			q = (char *)s;
		s++;
	}
	return (q);
}
