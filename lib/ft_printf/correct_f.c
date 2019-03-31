/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:11:09 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 08:22:48 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	correct_drob(char *drob, char *r, int i, int zero)
{
	if (g_flags->precision != 0 && r[i - zero + 1] != '\0' &&
		r[i - zero + 1] >= '5')
		drob[i] += 1;
	while (i > 0)
	{
		if (drob[i] > '9')
		{
			drob[i] = '0';
			drob[i - 1] += 1;
		}
		i--;
	}
	ft_strdel(&r);
}

char	*correct_full(char *full, char *drob)
{
	size_t		i;
	char		*r;

	drob[0] = '0';
	i = ft_strlen(full) - 1;
	full[i] += 1;
	while (i > 0)
	{
		if (full[i] > '9' && full[i] != '\0')
		{
			full[i] = '0';
			full[i - 1] += 1;
		}
		i--;
	}
	if (full[0] > '9')
	{
		full[0] = '0';
		r = full;
		full = ft_strjoin("1", r);
		free(r);
	}
	return (full);
}
