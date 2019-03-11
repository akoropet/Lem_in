/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:03:18 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 20:04:51 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] >= 33 && s[i] <= 126 && s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				break ;
		}
		i++;
	}
	return (count);
}

static void		ft_write_word(char *q, const char *s, int i, char c)
{
	int h;

	h = 0;
	while (s[i] != c && s[i] != '\0')
	{
		q[h] = s[i];
		h++;
		i++;
	}
	q[h] = '\0';
}

static void		ft_write_str(char **q, char const *s, char c)
{
	int i;
	int m;
	int k;

	i = -1;
	k = 0;
	while (s[++i])
	{
		m = 0;
		if (s[i] >= 33 && s[i] <= 126 && s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
			{
				m++;
				i++;
			}
			if (m > 0)
			{
				q[k] = (char *)malloc(sizeof(char) * (m + 1));
				ft_write_word(q[k], s, i - m, c);
				k++;
			}
		}
	}
}

char			**ft_strsplit(char const *s, char c)
{
	int		count;
	char	**q;

	if (s != NULL)
	{
		count = ft_count_words(s, c);
		q = (char **)malloc(sizeof(char *) * (count + 1));
		if (q == NULL)
			return (NULL);
		q[count] = NULL;
		ft_write_str(q, s, c);
		return (q);
	}
	return (NULL);
}
