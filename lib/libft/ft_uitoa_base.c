/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:29:03 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/18 15:12:42 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

void	u_make(unsigned long long int value,
	unsigned long long int base, char *str, int *i)
{
	char	*tmp;

	tmp = "0123456789abcdef";
	if (value >= base)
		u_make(value / base, base, str, i);
	str[(*i)++] = tmp[ABS(value % base)];
}

char	*ft_uitoa_base(unsigned long long int value,
	unsigned long long int base)
{
	int		i;
	char	*str;

	i = 0;
	if (base < 2 || base > 16 || !(str = (char *)malloc(64)))
		return (0);
	u_make(value, base, str, &i);
	str[i] = '\0';
	return (str);
}
