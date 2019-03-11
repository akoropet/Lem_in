/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:16:12 by akoropet          #+#    #+#             */
/*   Updated: 2019/01/24 20:16:15 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int arg1, int arg2)
{
	int		res;
	int		n;

	n = 0;
	res = 1;
	if (arg2 == 0)
		return (1);
	if (arg1 == 0)
		return (0);
	while (n < arg2)
	{
		res = res * arg1;
		n++;
	}
	return (res);
}
