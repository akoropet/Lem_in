/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 17:26:25 by akoropet          #+#    #+#             */
/*   Updated: 2019/04/27 16:19:16 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(int k)
{
	int c;

	c = 0;
	if (k < 0)
	{
		k = k * -1;
		c++;
	}
	while (k > 0)
	{
		c++;
		k = k / 10;
	}
	return (c);
}

static char		*ft_revers(char *q, int i)
{
	int		j;
	char	k;
	int		m;

	j = 0;
	m = i;
	while (j <= (m / 2))
	{
		k = q[i];
		q[i] = q[j];
		q[j] = k;
		i--;
		j++;
	}
	q[m + 1] = '\0';
	return (q);
}

static void		ft_check(char *q, int n, int c)
{
	int minus;
	int i;

	minus = 0;
	if (n < 0)
	{
		n = n * -1;
		q[c - 1] = '-';
		minus++;
	}
	i = 0;
	while (n > 0)
	{
		q[i++] = (n % 10) + '0';
		n = n / 10;
	}
	if (minus == 1)
		ft_revers(q, i);
	else
		ft_revers(q, i - 1);
}

char			*ft_itoa(int n)
{
	char	*q;
	int		c;

	if (n == -2147483648)
		return (q = ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n == 0 || n == -0)
		c = 1;
	else
		c = ft_count(n);
	if ((q = (char *)malloc(sizeof(char) * (c + 1))) == NULL)
		return (NULL);
	if (n != 0)
		ft_check(q, n, c);
	else
		q = ft_strdup("0");
	return (q);
}
