/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:11:41 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/13 15:12:24 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags(char *str, char symb)
{
	int		i;

	i = 1;
	g_flags->minus = 0;
	g_flags->plus = 0;
	g_flags->zero = 0;
	g_flags->space = 0;
	g_flags->hashtag = 0;
	while (str[i] && str[i] != symb)
	{
		if (str[i] == '-')
			g_flags->minus = 1;
		if (str[i] == '+')
			g_flags->plus = 1;
		if (str[i] == '0' && str[i + 1] != '.' && str[i - 1] != '.' &&
			!ft_isdigit(str[i - 1]) && str[i + 1] != '0')
			g_flags->zero = 1;
		if (str[i] == ' ')
			g_flags->space = 1;
		if (str[i] == '#')
			g_flags->hashtag = 1;
		i++;
	}
	g_flags->width = ft_width(str, symb);
	g_flags->precision = ft_precision(str, symb);
}
