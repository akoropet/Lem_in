/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 20:22:40 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/28 14:19:04 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*create_str_o(char *num, int len)
{
	char	*str;
	int		n;
	int		i;

	i = -1;
	n = 0;
	n = len_str(len, 0);
	n = (g_flags->space || g_flags->plus) && (g_flags->minus ||
		g_flags->width < len) ? n - 1 : n;
	n = g_flags->hashtag && ((g_flags->precision <= len && g_flags->minus) ||
		(g_flags->precision <= len && g_flags->width <= len)) &&
		ft_strcmp("0", num) ? n + 1 : n;
	if (n == 0)
		return (ft_memalloc(n));
	str = (char *)malloc(n + 1);
	ft_memset(str, ' ', n);
	str[n--] = '\0';
	if (g_flags->hashtag && ft_strcmp("0", num) && g_flags->precision < len + 1)
		str[n] = '0';
	while ((g_flags->precision > len + ++i ||
		(g_flags->precision < 0 && g_flags->zero)) && n >= 0)
		str[n--] = '0';
	return (str);
}

int		check_flags_o(char *num, int len)
{
	int		count;
	char	*str;

	count = 0;
	str = create_str_o(num, len);
	if (!ft_strcmp(num, "0") && g_flags->precision == 0 && !g_flags->hashtag)
		num[0] = ' ';
	ft_putstr(str);
	ft_putstr(num);
	count = ft_strlen(num);
	if (str != NULL)
		count += ft_strlen(str);
	while ((g_flags->precision > g_flags->width && count < g_flags->precision)
		|| (g_flags->precision < g_flags->width && count < g_flags->width))
	{
		ft_putchar(' ');
		count++;
	}
	ft_strdel(&num);
	ft_strdel(&str);
	return (count);
}

int		print_o(char *str, va_list ap)
{
	size_t		i;
	int			n;
	int			count;
	char		*num;

	if ((n = ft_modifier(str, 'o')) == 0)
		i = (unsigned int)va_arg(ap, unsigned int);
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
	else
		i = va_arg(ap, intmax_t);
	ft_flags(str, 'o');
	if (!g_flags->hashtag && !g_flags->precision && !g_flags->width && i == 0)
		return (0);
	num = ft_itoa_base(i, 8);
	count = check_flags_o(num, ft_strlen(num));
	return (count);
}
