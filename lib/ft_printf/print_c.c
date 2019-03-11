/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:23:48 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/17 21:06:12 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_c(char *str, va_list ap)
{
	unsigned char	s;
	int				count;

	if (ft_modifier(str, 'c') == 4)
		return (print_big_c(str, ap));
	s = (unsigned char)va_arg(ap, int);
	ft_flags(str, 'c');
	if (g_flags->width <= 1)
	{
		ft_putchar(s);
		return (1);
	}
	else
		count = g_flags->minus ? print_c_with_minus(s, g_flags->width) :
			print_c_without_minus(s, g_flags->width);
	return (count);
}

int		print_c_with_minus(char s, int width)
{
	int		count;

	count = 1;
	ft_putchar(s);
	while (width > 1)
	{
		ft_putchar(' ');
		width--;
		count++;
	}
	return (count);
}

int		print_c_without_minus(char s, int width)
{
	int		count;

	count = 1;
	while (width > 1)
	{
		g_flags->zero ? ft_putchar('0') : ft_putchar(' ');
		width--;
		count++;
	}
	ft_putchar(s);
	return (count);
}

int		print_big_c(char *str, va_list ap)
{
	wchar_t		wc;
	int			count;
	int			i;
	char		*res;
	int			len;

	i = -1;
	count = -1;
	ft_modifier(str, 'c') == 4 ? ft_flags(str, 'c') : ft_flags(str, 'C');
	wc = (wchar_t)va_arg(ap, wint_t);
	res = print_unicode(wc);
	len = ft_strlen(res);
	while (!g_flags->minus && len < g_flags->width &&
		g_flags->width - len > ++count)
		g_flags->zero ? ft_putchar('0') : ft_putchar(' ');
	count = g_flags->width <= len ? count + 1 : count;
	count += len;
	ft_putstr(res);
	while (g_flags->minus && len < g_flags->width &&
		g_flags->width > ++count)
		ft_putchar(' ');
	free(res);
	return (count);
}
