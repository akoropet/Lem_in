/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 20:08:19 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/13 17:55:02 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_modifier(char *str, char symb)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (str[++i] && str[i] != symb)
	{
		if (str[i] == 'h' && (str[i + 1] == 'h' || str[i - 1] == 'h'))
			n = 1;
		if (str[i] == 'h' && str[i - 1] != 'h')
			n = 2;
		if (str[i] == 'l' && str[i + 1] == 'l')
			n = 3;
		if (str[i] == 'l' && str[i + 1] != 'f')
			n = 4;
		if (str[i] == 'z')
			n = 5;
		if (str[i] == 'j')
			n = 6;
		if (str[i] == 'l' && str[i + 1] == 'f')
			n = 7;
		if (str[i] == 'L' && str[i + 1] == 'f')
			n = 8;
	}
	return (n);
}
