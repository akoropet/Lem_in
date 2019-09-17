/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:00:39 by akoropet          #+#    #+#             */
/*   Updated: 2019/04/27 15:20:17 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfjoin(char *s1, char *s2, int n)
{
	char	*str;

	if (s1 && s2)
	{
		if (!(str = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		ft_strcpy(str, s1);
		ft_strcpy(ft_strchr(str, '\0'), s2);
		if (n == 1 || n == 3)
			ft_strdel(&s1);
		if (n == 2 || n == 3)
			ft_strdel(&s2);
		return (str);
	}
	return (NULL);
}
