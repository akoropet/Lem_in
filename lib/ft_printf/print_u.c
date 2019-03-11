/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:51:38 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/26 21:57:06 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_u(char *str, va_list ap)
{
	unsigned long long int	i;
	int						n;
	int						count;
	char					*num;

	if ((n = ft_modifier(str, 'u')) == 0)
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
	else
		i = va_arg(ap, long long);
	ft_flags(str, 'u');
	num = ft_uitoa_base(i, 10);
	count = i == 0 && g_flags->precision == 0 ? 0 :
		check_flags_u(num, ft_strlen(num));
	free(num);
	return (count);
}

int		check_flags_u(char *num, int len)
{
	int		count;
	int		i;
	char	*res;

	count = 0;
	i = 0;
	res = create_str_u(len);
	write_to_res_u(res, num, len);
	while (!g_flags->minus && g_flags->precision < 0 && g_flags->zero && res[i]
		&& res[i] == ' ')
		res[i++] = '0';
	ft_putstr(res);
	count = ft_strlen(res);
	free(res);
	return (count);
}

char	*create_str_u(int len)
{
	char	*res;
	int		i;

	if (g_flags->precision > len || g_flags->width > len)
		len = g_flags->precision > g_flags->width ?
			g_flags->precision : g_flags->width;
	res = ft_strnew(len);
	i = 0;
	while (i < len)
	{
		res[i] = ' ';
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	write_to_res_u(char *res, char *num, int len)
{
	int		i;
	int		n;
	int		j;

	n = ft_strlen(res);
	i = 0;
	j = 0;
	if (g_flags->minus)
	{
		while (g_flags->precision > len && i < g_flags->precision - len)
			res[i++] = '0';
	}
	else
	{
		while (i < n - g_flags->precision && i < n - len)
			i++;
		while (g_flags->precision > len && i < n - len)
			res[i++] = '0';
	}
	while (num[j])
		res[i++] = num[j++];
}
