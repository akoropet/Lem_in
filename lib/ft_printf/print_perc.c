/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:35:46 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/28 13:34:39 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_perc(char *str)
{
	int		n;
	int		i;

	n = 0;
	i = 1;
	ft_flags(str, '%');
	while (str[i] != 0 && (ft_isdigit(str[i]) ||
		(str[i] >= 97 && str[i] <= 122) || str[i] == ' ' || str[i] == '.'))
		i++;
	while (g_flags->precision == -1 && g_flags->width == 0 && str[i] != 0 &&
		str[i] != '%' && ++n > 0)
		ft_putchar(str[i++]);
	n = n < 1 && str[i] != '\0' && str[i] != '\n' ? normal(str) : n;
	return (n);
}

int		write_upper(char *str, int i)
{
	int		n;

	n = 0;
	while (str[i] != 0)
	{
		ft_putchar(str[i]);
		n++;
		i++;
	}
	return (n);
}

int		normal(char *str)
{
	int		n;

	n = 0;
	while (!g_flags->minus && (str[n] < 65 || str[n] > 90) &&
		g_flags->width > ++n)
		g_flags->zero ? ft_putchar('0') : ft_putchar(' ');
	if ((str[n] < 65 || str[n] > 90))
		ft_putchar('%');
	else if (str[n] != 0)
		n += write_upper(str, n);
	while (g_flags->minus && g_flags->width > ++n)
		ft_putchar(' ');
	return (n);
}
