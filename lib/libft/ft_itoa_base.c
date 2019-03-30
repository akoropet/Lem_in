/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 19:27:21 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/28 13:39:39 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

static int		size_str(size_t value, size_t base)
{
	int		count;

	count = 1;
	while (value >= base)
	{
		value /= base;
		count++;
	}
	return (count);
}

char			*ft_itoa_base(long long int v, size_t base)
{
	char	*str;
	int		count;
	char	*tmp;
	size_t	value;

	tmp = "0123456789abcdef";
	count = 0;
	if (base < 2 || base > 16)
		return (NULL);
	value = v < 0 && base == 10 ? v * -1 : v;
	count = size_str(value, base);
	count = v < 0 && base == 10 ? count + 1 : count;
	str = (char *)malloc(count + 1);
	str[count--] = '\0';
	v < 0 && base == 10 ? str[0] = '-' : 0;
	while (count >= 0 && str[count] != '-')
	{
		str[count] = tmp[ABS(value % base)];
		value /= base;
		count--;
	}
	return (str);
}
