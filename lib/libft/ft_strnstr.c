/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:58:38 by akoropet          #+#    #+#             */
/*   Updated: 2018/06/14 17:58:40 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char *h;
	char *n;
	char *tmp;

	h = (char *)haystack;
	if (!*needle)
		return (h);
	while (*h && (h - haystack) < (long int)len)
	{
		n = (char *)needle;
		if (*h == *n)
		{
			tmp = h;
			while (*h && *n && *h == *n && (h++ - haystack) < (long int)len)
				n++;
			if (!*n)
				return (tmp);
			h = tmp;
		}
		h++;
	}
	return (NULL);
}
