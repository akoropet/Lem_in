/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:33:21 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/11 20:05:29 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_find_end(char const *start, char const *finish, int n)
{
	char *q;

	if ((q = (char *)malloc(sizeof(char) * (n + 2))) == 0)
		return (NULL);
	n = 0;
	while (start++ <= finish)
		q[n++] = *start;
	q[n] = '\0';
	return (q);
}

char			*ft_strtrim(char const *start)
{
	char		*q;
	int			n;
	char const	*finish;

	n = 0;
	if (start != NULL)
	{
		while (*start == ' ' || *start == '\t' || *start == '\n')
			start++;
		finish = start--;
		if (*finish == '\0')
			return (ft_strdup("\0"));
		while (*finish++ != '\0')
			n++;
		finish--;
		while ((*finish == ' ' || *finish == '\t' ||
			*finish == '\n' || *finish == '\0') && n-- > 0)
			finish--;
		finish--;
		q = ft_find_end(start, finish, n);
		return (q);
	}
	return (NULL);
}
