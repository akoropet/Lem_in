/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:10:59 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 20:03:10 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*q;
	int		n;
	int		i;

	i = 0;
	n = 0;
	if (s1 != NULL && s2 != NULL)
	{
		while (s1[i])
			i++;
		while (s2[n])
			n++;
		if ((q = (char *)malloc(sizeof(char) * (i + n + 1))) == 0)
			return (NULL);
		i = 0;
		n = 0;
		while (s1[i])
			q[n++] = s1[i++];
		i = 0;
		while (s2[i])
			q[n++] = s2[i++];
		q[n] = '\0';
		return (q);
	}
	return (NULL);
}
