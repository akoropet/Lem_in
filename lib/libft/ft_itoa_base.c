/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 19:27:21 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/18 15:12:32 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

void	make(long long int value, long base, char *str, int *i)
{
	char	*tmp;

	tmp = "0123456789abcdef";
	if (value <= -base || value >= base)
		make(value / base, base, str, i);
	str[(*i)++] = tmp[ABS(value % base)];
}

char	*ft_itoa_base(long long int value, long base)
{
	int		i;
	char	*str;

	i = 0;
	if (base < 2 || base > 16 || !(str = (char *)malloc(32)))
		return (0);
	if (base == 10 && value < 0)
		str[i++] = '-';
	make(value, base, str, &i);
	str[i] = '\0';
	return (str);
}
