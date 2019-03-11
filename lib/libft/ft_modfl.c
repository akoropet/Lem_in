/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modfl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 19:30:18 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/08 22:29:55 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double		ft_modfl(long double num, long double *full)
{
	unsigned long long int	a;
	int						minus;

	minus = num < 0 ? 1 : 0;
	minus == 1 ? num *= -1 : 0;
	a = num;
	*full = num > 18446744073709551615.0 ? num : a;
	a = 1000000000000000000;
	while (num < 9999999999999999 && num >= 1)
	{
		num < a ? a /= 10 : 0;
		num >= a ? num -= a : 0;
	}
	minus == 1 ? *full *= -1 : 0;
	if (num > 9999999999999999 && minus)
		return (-0.0);
	if (num > 9999999999999999 && !minus)
		return (0.0);
	if (minus)
		num *= -1;
	return (num);
}
