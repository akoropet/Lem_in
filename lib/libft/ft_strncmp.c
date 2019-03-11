/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:40:34 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 18:24:22 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *q1, const char *q2, size_t len)
{
	unsigned long i;
	unsigned char *s1;
	unsigned char *s2;

	i = 0;
	if (len <= 0)
		return (0);
	s1 = (unsigned char *)q1;
	s2 = (unsigned char *)q2;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < (len - 1))
		i++;
	return (s1[i] - s2[i]);
}
