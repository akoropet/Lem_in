/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:18:24 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/23 19:38:16 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int m;
	long int ln;

	ln = (long int)n;
	if (ln < 0)
	{
		ln = ln * -1;
		ft_putchar('-');
	}
	if (ln >= 0)
	{
		m = ln % 10;
		ln = ln / 10;
		if (ln > 0)
			ft_putnbr(ln);
		ft_putchar(m + 48);
	}
}
