/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 20:17:22 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/28 19:59:33 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_p(char *str, va_list ap)
{
	unsigned long long int	s;
	char					*num;
	char					*arg;
	int						count;

	count = 0;
	s = va_arg(ap, long);
	ft_flags(str, 'p');
	num = ft_uitoa_base(s, 16);
	arg = create_arg(ft_strlen(num));
	count = s == 0 && g_flags->precision == 0 ? ft_strlen(arg) :
		ft_strlen(arg) + ft_strlen(num);
	write_all(num, arg, &count, s);
	ft_strdel(&num);
	ft_strdel(&arg);
	return (count);
}

char	*create_arg(int len)
{
	char	*arg;
	int		n;

	n = 2;
	if (g_flags->precision > len)
		n += g_flags->precision - len;
	if (!g_flags->minus && g_flags->precision < 0 && g_flags->zero &&
		g_flags->width > len + 2)
		n += g_flags->width - len - 2;
	arg = ft_memalloc(n-- + 1);
	arg[0] = '0';
	arg[1] = 'x';
	g_flags->precision > len || (g_flags->precision < 0 && g_flags->zero) ?
		ft_memset(arg + 2, '0', n - 1) : 0;
	return (arg);
}

void	write_all(char *num, char *arg, int *count, unsigned long long int s)
{
	while (!g_flags->minus && (*count) < g_flags->width)
	{
		(*count)++;
		ft_putchar(' ');
	}
	ft_putstr(arg);
	s == 0 && g_flags->precision == 0 ? 0 : ft_putstr(num);
	while (g_flags->minus && (*count) < g_flags->width)
	{
		(*count)++;
		ft_putchar(' ');
	}
}
