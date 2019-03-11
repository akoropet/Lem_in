/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:31:33 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 20:05:10 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*q;
	unsigned int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
			i++;
		if (i <= start)
			return (0);
		if ((q = (char *)malloc(sizeof(char) * (len + 1))) == 0)
			return (NULL);
		i = 0;
		while (len > 0)
		{
			q[i] = s[start];
			i++;
			start++;
			len--;
		}
		q[i] = '\0';
		return (q);
	}
	return (NULL);
}
