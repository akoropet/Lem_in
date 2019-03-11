/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 20:00:50 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/23 19:56:17 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int m;
	long int ln;

	ln = (long int)n;
	if (ln < 0)
	{
		ln = ln * -1;
		ft_putchar_fd('-', fd);
	}
	if (ln >= 0)
	{
		m = ln % 10;
		ln = ln / 10;
		if (ln > 0)
			ft_putnbr_fd(ln, fd);
		ft_putchar_fd(m + 48, fd);
	}
}
