/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:40:43 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/28 13:33:57 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_i(char *str, va_list ap)
{
	unsigned long long int	m;
	long long int			i;
	int						n;
	int						count;
	int						minus;

	if ((n = ft_modifier(str, 'i')) == 0)
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
	ft_flags(str, 'i');
	minus = i < 0 ? 1 : 0;
	m = minus ? i * -1 : i;
	count = check_flags(m, minus);
	return (count);
}
