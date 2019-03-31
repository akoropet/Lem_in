/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:42:47 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 06:57:27 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		links(t_data *data, t_room **r, char *str)
{
	t_room	**room1;
	t_room	**room2;
	char	*link;

	room1 = r;
	if (str[0] == '#')
		return (comment(data, str));
	link = ft_strndup(str, '-');
	while ((*room1) && ft_strcmp((*room1)->name, link))
		room1 = &(*room1)->next;
	if ((*room1) && !ft_strcmp((*room1)->name, link))
	{
		ft_strdel(&link);
		room2 = r;
		link = ft_strdup(ft_strchr(str, '-') + 1);
		while ((*room2) && ft_strcmp((*room2)->name, link))
			room2 = &(*room2)->next;
		if ((*room2) && !ft_strcmp((*room2)->name, link))
		{
			add_links(room1, room2, data, &link);
			return (1);
		}
	}
	ft_strdel(&link);
	return (0);
}

void	add_links(t_room **room1, t_room **room2, t_data *data, char **link)
{
	ft_strdel(link);
	data->links[(*room2)->index][(*room1)->index] = '1';
	data->links[(*room1)->index][(*room2)->index] = '1';
	(*room1)->step = data->count_room;
	(*room2)->step = data->count_room;
}

void	creare_tabl(t_data *data, int index)
{
	int		n;
	int		i;

	data->count_room = index;
	n = data->count_room;
	data->links = (char **)malloc(sizeof(char *) * (n + 1));
	data->links[n] = NULL;
	i = 0;
	while (i < n)
	{
		data->links[i] = ft_memalloc(n + 1);
		ft_memset(data->links[i], '0', n);
		i++;
	}
}

int		room_or_link(t_room **r, char *str)
{
	t_room	**room;
	char	*room_name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '-')
		i++;
	if (str[i] && (room_name = ft_strndup(str, '-')))
	{
		room = r;
		while ((*room) && (*room)->name)
		{
			if (!ft_strcmp((*room)->name, room_name))
			{
				ft_strdel(&room_name);
				return (1);
			}
			room = &(*room)->next;
		}
		ft_strdel(&room_name);
	}
	return (0);
}
