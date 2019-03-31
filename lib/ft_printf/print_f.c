/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:17:08 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 08:27:25 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		in_the_end(int full, int drob, int minus)
{
	int		i;

	i = 0;
	if (g_flags->precision == 0 && !g_flags->hashtag)
		drob = 0;
	if (g_flags->precision == 0 && g_flags->hashtag)
		drob = 1;
	while (drob + i < g_flags->precision || (g_flags->precision < 0 && i < 5
		&& drob < 6))
	{
		i++;
		ft_putchar('0');
	}
	while (g_flags->minus && full + drob + i < g_flags->width - 1)
	{
		g_flags->minus && full + drob + i == g_flags->width - 2 && (minus ||
			g_flags->plus || g_flags->space) ? 0 : ft_putchar(' ');
		i++;
	}
	i = g_flags->minus && full + drob + i == g_flags->width - 1 && (minus ||
			g_flags->plus || g_flags->space) ? i - 1 : i;
	if (g_flags->minus && g_flags->precision == 0 &&
		g_flags->width > drob + full && ++i > 0)
		ft_putchar(' ');
	return (i);
}

char	*create_drob(long double d, int n)
{
	int				i;
	char			*drob;
	char			*r;
	long double		f;
	int				zero;

	i = -1;
	zero = 0;
	d = ft_modfl(d, &f);
	while (++i < 16 - n)
	{
		d *= 10;
		if (d > 0 && d < 1)
			zero++;
	}
	r = ft_itoa_base(d, 10);
	i = g_flags->precision > 0 ? g_flags->precision : 6;
	drob = ft_memalloc(i + 1);
	if (zero > 0)
		ft_memset(drob, '0', zero);
	ft_strncat(drob, r, i-- - zero);
	correct_drob(drob, r, i, zero);
	return (drob);
}

char	*write_flags(int full, int drob, int minus)
{
	int		i;
	int		len;
	char	*str;

	len = g_flags->precision >= 0 ? full + g_flags->precision : 0;
	len = g_flags->precision < 0 ? full + drob : len;
	len = (g_flags->hashtag && g_flags->precision == 0) ||
		g_flags->precision != 0 ? len + 1 : len;
	i = (g_flags->width > full + drob || g_flags->width > g_flags->precision) &&
		!g_flags->minus ? len_str(len, minus) : 0;
	i = i == 0 && (g_flags->space || g_flags->plus || minus) ? 1 : i;
	str = ft_memalloc(i-- + 1);
	drob = (g_flags->precision == 0 && g_flags->hashtag) ||
		g_flags->precision != 0 ? drob + 1 : drob;
	while (((g_flags->precision == 0 && g_flags->width > full + 1) ||
		(g_flags->precision != 0 && g_flags->width > full + drob)) &&
		g_flags->zero && i > 0)
		str[i--] = '0';
	(ft_isdigit(str[i + 1]) || str[i + 1] == '\0') && minus ?
		str[i--] = '-' : 0;
	(ft_isdigit(str[i + 1]) || str[i + 1] == '\0') && !minus && g_flags->plus ?
		str[i--] = '+' : 0;
	while (i >= 0)
		str[i--] = !g_flags->zero || g_flags->space ? ' ' : '0';
	return (str);
}

int		create_float(long double d, int minus)
{
	size_t	count;
	char	*full;
	char	*drob;
	char	*str;

	full = ft_itoa_base(d, 10);
	drob = create_drob(d, ft_strlen(full));
	if (drob[0] > '9' || (g_flags->precision == 0 && drob[0] >= '5'))
		full = correct_full(full, drob);
	str = write_flags(ft_strlen(full), ft_strlen(drob), minus);
	ft_putstr(str);
	count = ft_strlen(str);
	ft_putstr(full);
	count += ft_strlen(full);
	((g_flags->precision == 0 && g_flags->hashtag) || g_flags->precision != 0)
		&& ++count > 0 ? ft_putchar('.') : 0;
	if (g_flags->precision != 0 && (count += ft_strlen(drob)) > 0)
		ft_putstr(drob);
	count += in_the_end(ft_strlen(full), ft_strlen(drob), minus);
	ft_strdel(&str);
	ft_strdel(&full);
	ft_strdel(&drob);
	return (count);
}

int		print_f(char *str, va_list ap)
{
	long double		d;
	int				n;
	int				minus;
	int				count;

	if ((n = ft_modifier(str, 'f')) <= 7)
		d = va_arg(ap, double);
	else
		d = va_arg(ap, long double);
	ft_flags(str, 'f');
	minus = d < 0 ? 1 : 0;
	d = minus == 1 ? d * -1 : d;
	count = create_float(d, minus);
	return (count);
}
