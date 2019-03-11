/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 19:31:09 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/27 20:36:59 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	**create_mask(size_t len)
{
	char	**mask;
	int		n;
	int		i;

	n = 0;
	i = 1;
	if (++n > 0 && len <= 7 &&
		(mask = (char **)malloc(sizeof(char *) * (n + 1))))
		mask[0] = ft_strdup("00000000");
	else if (++n > -1 && len <= 11 &&
		(mask = (char **)malloc(sizeof(char *) * (n + 1))))
		mask[0] = ft_strdup("11000000");
	else if (++n > 0 && len <= 16 &&
		(mask = (char **)malloc(sizeof(char *) * (n + 1))))
		mask[0] = ft_strdup("11100000");
	else if (++n > 0 && (mask = (char **)malloc(sizeof(char *) * (n + 1))))
		mask[0] = ft_strdup("11110000");
	while (i < n)
	{
		mask[i] = ft_strdup("10000000");
		i++;
	}
	mask[i] = NULL;
	return (mask);
}

void	write_to_mask(char **mask, char *bin, int len)
{
	int		n;
	int		i;
	int		j;

	i = 0;
	while (mask[i + 1])
		i++;
	while (i >= 0)
	{
		j = 7;
		n = -1;
		while (++n < 6 && len >= 0)
		{
			mask[i][j] = bin[len--];
			j--;
		}
		i--;
	}
}

int		bin_to_dec(char *bin)
{
	int		i;
	int		n;
	int		res;

	i = 7;
	n = 1;
	res = 0;
	while (i >= 0)
	{
		if (bin[i] == '1')
			res = res + n;
		n = n * 2;
		i--;
	}
	return (res);
}

char	*print_unicode(int num)
{
	char	*bin;
	char	**mask;
	char	*res;
	int		i;

	i = -1;
	if (num > 127)
	{
		bin = ft_itoa_base(num, 2);
		mask = create_mask(ft_strlen(bin));
		write_to_mask(mask, bin, ft_strlen(bin) - 1);
		res = ft_memalloc(33);
		while (mask[++i])
			res[i] = bin_to_dec(mask[i]);
		while (i >= 0)
			free(mask[i--]);
		free(mask);
		free(bin);
	}
	else
	{
		res = ft_memalloc(2);
		res[0] = num;
	}
	return (res);
}
