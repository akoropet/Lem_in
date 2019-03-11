/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 17:09:15 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/26 17:36:00 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_type(char *str, va_list ap)
{
	int		n;
	int		i;
	int		j;

	n = 0;
	j = 1;
	while (str[j] != '\0')
	{
		i = 0;
		while (i < TYPE_NUM && str[j] != g_type[i].symb && str[j] != '%')
			i++;
		if (str[j] && str[j] == g_type[i].symb)
		{
			n = g_type[i].ft(str, ap);
			break ;
		}
		if (str[j] == '\0' || str[j] == '%')
		{
			n = print_perc(str);
			break ;
		}
		j++;
	}
	return (n);
}
