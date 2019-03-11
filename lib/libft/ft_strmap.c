/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:16:40 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 20:03:26 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*q;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
			i++;
		if ((q = (char *)malloc(sizeof(char) * (i + 1))) == 0)
			return (NULL);
		i = 0;
		while (s[i])
		{
			q[i] = f(s[i]);
			i++;
		}
		q[i] = '\0';
		return (q);
	}
	return (NULL);
}
