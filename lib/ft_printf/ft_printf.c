/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 16:36:35 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/21 16:00:09 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(char *str, ...)
{
	va_list		ap;
	int			n;

	n = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
			n = check_arg(&str, n, ap);
		else
		{
			ft_putchar(*str);
			n++;
		}
		if (*str)
			str++;
	}
	va_end(ap);
	return (n);
}

int		check_arg(char **str, int n, va_list ap)
{
	int		i;
	int		m;

	m = print_type(*str, ap);
	if (**str == '%')
		(*str)++;
	while (**str)
	{
		i = 0;
		while (i < TYPE_NUM && **str != g_type[i].symb && **str != '%')
			i++;
		if (**str == g_type[i].symb || **str == '%')
			break ;
		(*str)++;
	}
	n += m;
	return (n);
}
