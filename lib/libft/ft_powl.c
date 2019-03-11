/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:36:07 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/08 22:29:43 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double		ft_powl(long double arg1, long double arg2)
{
	long double		res;
	long double		n;

	n = 0.0;
	res = 1.0;
	if (arg2 == 0.0)
		return (1.0);
	if (arg1 == 0.0)
		return (0.0);
	while (arg2 > 0 && n < arg2)
	{
		res = res * arg1;
		n++;
	}
	while (arg2 < 0 && n > arg2)
	{
		res *= 1 / arg1;
		n--;
	}
	return (res);
}
