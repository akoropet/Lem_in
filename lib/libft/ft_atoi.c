/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:56:39 by akoropet          #+#    #+#             */
/*   Updated: 2018/04/13 13:39:02 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int						minus;
	unsigned long long int	rez;
	int						i;

	i = 0;
	minus = 1;
	rez = 0;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		rez = rez * 10 + (str[i] - '0');
		i++;
		if (rez > 9223372036754775807 && minus == 1)
			return (-1);
		if (rez > 9223372036754775807 && minus == -1)
			return (0);
	}
	return (rez * minus);
}
