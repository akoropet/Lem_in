/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_big_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:54:00 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/28 13:33:40 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_big_x(char *str, va_list ap)
{
	unsigned long long int	i;
	int						n;
	int						count;
	char					*num;

	if ((n = ft_modifier(str, 'X')) == 0)
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
		i = va_arg(ap, intmax_t);
	ft_flags(str, 'X');
	num = ft_uitoa_base(i, 16);
	count = i == 0 && g_flags->precision == 0 ? 0 :
		check_flags_big_x(num, ft_strlen(num));
	return (count);
}

int		check_flags_big_x(char *num, int len)
{
	int		count;
	int		i;
	char	*str;

	count = 0;
	i = -1;
	str = create_str_x(num, len);
	count += str != NULL ? ft_strlen(str) + ft_strlen(num) : ft_strlen(num);
	to_upper_x(num, str);
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

void	to_upper_x(char *num, char *str)
{
	int		i;

	i = 0;
	while (num[i] != '\0')
	{
		num[i] = ft_toupper(num[i]);
		i++;
	}
	if (str != NULL && g_flags->hashtag)
		str[1] = ft_toupper(str[1]);
}
