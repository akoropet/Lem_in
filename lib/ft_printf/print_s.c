/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:03:48 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/26 17:46:43 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_s(char *str, va_list ap)
{
	char	*arg;
	int		count;

	arg = va_arg(ap, char *);
	ft_flags(str, 's');
	count = arg == NULL ? create_str_s("(null)") : create_str_s(arg);
	return (count);
}

int		create_str_s(char *arg)
{
	char	*res;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(arg);
	if ((g_flags->precision < len && g_flags->precision >= 0) ||
		g_flags->width > len)
	{
		len = g_flags->precision < len && g_flags->precision > g_flags->width ?
			g_flags->precision : len;
		len = g_flags->precision < len && g_flags->precision < g_flags->width ?
			g_flags->width : len;
		len = g_flags->width > len ? g_flags->width : len;
		len = !g_flags->width && !g_flags->precision ? 0 : len;
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	while (++i < len)
		res[i] = ' ';
	g_flags->minus ? print_s_with_minus(res, arg) :
		print_s_without_minus(res, arg, len);
	return (len);
}

void	print_s_with_minus(char *res, char *arg)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (g_flags->precision > 0)
	{
		if (g_flags->precision == -1)
			g_flags->precision = 0;
		while (res[++i] && arg[i] && i < g_flags->precision)
			res[i] = arg[i];
	}
	else
	{
		while (g_flags->precision != 0 && res[++i] && arg[i])
			res[i] = arg[i];
	}
	ft_putstr(res);
	free(res);
}

void	print_s_without_minus(char *res, char *arg, int len)
{
	int		i;
	int		j;
	int		n;
	int		pre;

	i = 0;
	j = 0;
	n = ft_strlen(arg);
	pre = g_flags->precision;
	while (i < len - n)
		res[i++] = g_flags->zero ? '0' : ' ';
	while (g_flags->precision > 0 && i < len - pre)
		i++;
	while (i < len && g_flags->precision != 0)
		res[i++] = arg[j++];
	ft_putstr(res);
	free(res);
}
