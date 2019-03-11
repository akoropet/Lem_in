/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 20:04:40 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/24 20:21:41 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_d(char *str, va_list ap)
{
	unsigned long long int	m;
	long long int			i;
	int						n;
	int						count;
	int						minus;

	if ((n = ft_modifier(str, 'd')) == 0)
		i = va_arg(ap, int);
	else if (n == 1)
		i = (signed char)va_arg(ap, int);
	else if (n == 2)
		i = (short)va_arg(ap, int);
	else if (n == 3)
		i = va_arg(ap, long long);
	else if (n == 4)
		i = va_arg(ap, long);
	else if (n == 5)
		i = va_arg(ap, size_t);
	else
		i = va_arg(ap, intmax_t);
	ft_flags(str, 'd');
	minus = i < 0 ? 1 : 0;
	m = minus ? i * -1 : i;
	count = check_flags(m, minus);
	return (count);
}

int		check_flags(unsigned long long int m, int minus)
{
	char	*num;
	char	*str;
	int		count;

	num = create_num(m);
	str = create_flags(ft_strlen(num), minus);
	ft_putstr(str);
	ft_putstr(num);
	count = ft_strlen(str) + ft_strlen(num) - 1;
	while (++count < g_flags->width && g_flags->minus)
		ft_putchar(' ');
	ft_strdel(&str);
	ft_strdel(&num);
	return (count);
}

int		len_str(int len, int minus)
{
	int		i;

	i = 0;
	if (!g_flags->minus && (g_flags->precision > len || g_flags->width > len))
		i = g_flags->precision > g_flags->width ? g_flags->precision - len :
			g_flags->width - len;
	if (!g_flags->minus && (g_flags->precision >= g_flags->width ||
		(g_flags->precision <= len && g_flags->width <= len)) && (g_flags->plus
		|| g_flags->space || minus))
		i++;
	if (g_flags->minus && g_flags->precision >= 0 && g_flags->precision > len)
		i = g_flags->precision - len;
	if (g_flags->minus && (g_flags->plus || g_flags->space || minus))
		i++;
	return (i);
}

char	*create_flags(int len, int minus)
{
	char	*str;
	int		i;
	int		n;

	n = -1;
	i = len_str(len, minus);
	str = (char *)malloc(sizeof(char) * (i + 1));
	str[i--] = '\0';
	while (++n + len < g_flags->precision || (g_flags->precision < 0 &&
		g_flags->zero && i > 0))
		str[i--] = '0';
	(ft_isdigit(str[i + 1]) || str[i + 1] == '\0') && minus ?
		str[i--] = '-' : 0;
	(ft_isdigit(str[i + 1]) || str[i + 1] == '\0') && !minus && g_flags->plus ?
		str[i--] = '+' : 0;
	while (i >= 0)
		str[i--] = !g_flags->zero || (g_flags->zero && g_flags->precision >= 0)
			|| g_flags->space ? ' ' : '0';
	return (str);
}

char	*create_num(unsigned long long int m)
{
	unsigned long long int		r;
	int							n;
	char						*num;

	r = m;
	n = 0;
	n = m == 0 ? n + 1 : n;
	while (r > 0 && ++n > 0)
		r /= 10;
	n = m == 0 && g_flags->precision == 0 && !g_flags->width ? n - 1 : n;
	num = (char *)malloc(sizeof(char) * (n + 1));
	num[n] = '\0';
	if (m == 0 && g_flags->precision == 0 && g_flags->width)
	{
		num[--n] = ' ';
		return (num);
	}
	while (--n >= 0)
	{
		num[n] = m % 10 + '0';
		m /= 10;
	}
	return (num);
}
