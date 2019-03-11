/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:23:33 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/28 14:48:58 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_x(char *str, va_list ap)
{
	unsigned long long int	i;
	int						n;
	int						count;
	char					*num;

	if ((n = ft_modifier(str, 'x')) == 0)
		i = va_arg(ap, unsigned int);
	else if (n == 1)
		i = (unsigned char)va_arg(ap, int);
	else if (n == 2)
		i = (unsigned short)va_arg(ap, int);
	else if (n == 3)
		i = va_arg(ap, unsigned long long);
	else if (n == 4)
		i = va_arg(ap, unsigned long);
	else if (n == 5)
		i = va_arg(ap, size_t);
	else if (n == 6)
		i = va_arg(ap, long long);
	ft_flags(str, 'x');
	if (!g_flags->precision && !g_flags->width && i == 0)
		return (0);
	num = ft_uitoa_base(i, 16);
	count = check_flags_x(num, ft_strlen(num));
	return (count);
}

int		check_flags_x(char *num, int len)
{
	int		count;
	char	*str;

	count = 0;
	str = create_str_x(num, len);
	count += str != NULL ? ft_strlen(str) + ft_strlen(num) : ft_strlen(num);
	while (!g_flags->minus && count < g_flags->width)
	{
		count++;
		g_flags->precision < 0 && g_flags->zero ? ft_putchar('0') :
			ft_putchar(' ');
	}
	str != NULL ? ft_putstr(str) : 0;
	ft_putstr(num);
	while (g_flags->minus && count < g_flags->width)
	{
		count++;
		ft_putchar(' ');
	}
	ft_strdel(&num);
	ft_strdel(&str);
	return (count);
}

char	*create_str_x(char *num, int len)
{
	char	*str;
	int		n;
	int		i;

	n = 0;
	i = 0;
	if (g_flags->precision > len)
		n += g_flags->precision - len;
	if (!g_flags->minus && g_flags->precision < 0 && g_flags->zero &&
		g_flags->width > len + 2)
		n += g_flags->width - len;
	if (g_flags->hashtag && ft_strcmp("0", num) && (n == 0 ||
		g_flags->precision > len))
		n += 2;
	str = ft_memalloc(n + 1);
	if (g_flags->hashtag && ft_strcmp("0", num))
	{
		str[0] = '0';
		str[1] = 'x';
	}
	i = g_flags->hashtag && ft_strcmp("0", num) ? 2 : 0;
	g_flags->hashtag && ft_strcmp("0", num) ? ft_memset(str + 2, '0', n - 2) :
		ft_memset(str, '0', n);
	return (str);
}
