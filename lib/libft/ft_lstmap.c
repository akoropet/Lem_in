/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 21:28:49 by akoropet          #+#    #+#             */
/*   Updated: 2018/05/27 21:28:54 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;
	t_list *q;

	if (lst != NULL)
	{
		res = f(lst);
		if (res == NULL)
			return (NULL);
		lst = lst->next;
		q = res;
		while (lst != NULL)
		{
			res->next = f(lst);
			if (res == NULL)
				return (NULL);
			lst = lst->next;
			res = res->next;
		}
		return (q);
	}
	return (NULL);
}
