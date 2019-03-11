/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:45:47 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/10 19:54:30 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_width(char *str, char symb)
{
	int		n;
	int		i;

	n = 0;
	i = 1;
	while (str[i] != symb && !ft_isdigit(str[i]))
		i++;
	if (str[i] == symb || str[i - 1] == '.')
		return (0);
	else if (str[i] == '0')
	{
		i++;
		while (str[i] != symb && (!ft_isdigit(str[i]) || str[i] == '0'))
			i++;
		while (str[i] != symb && str[i - 1] != '.' && ft_isdigit(str[i]))
			n = n * 10 + (str[i++] - '0');
	}
	else
	{
		while (str[i] != '.' && ft_isdigit(str[i]))
			n = n * 10 + (str[i++] - '0');
	}
	return (n);
}

int		ft_precision(char *str, char symb)
{
	int		n;
	int		i;

	n = 0;
	i = 1;
	while (str[i] != symb && str[i] != '.')
		i++;
	if (str[i] == symb)
		return (-1);
	else
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			n = n * 10 + (str[i] - '0');
			i++;
		}
	}
	return (n);
}
