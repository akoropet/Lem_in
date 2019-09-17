/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:41:51 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/17 18:55:22 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	reset_room(t_room **room, char *name, int x, int y)
{
	(*room)->name = name;
	(*room)->next = NULL;
	(*room)->coord_x = x;
	(*room)->coord_y = y;
	(*room)->ants = 0;
	(*room)->status = 0;
	(*room)->reserv = 0;
}

int		create_room(t_room **r, char *str, int *index)
{
	int		x;
	int		y;
	char	*name;
	t_room	**room;

	room = r;
	x = ft_atoi(ft_strchr(str, ' '));
	y = ft_atoi(ft_strchr((ft_strchr(str, ' ') + 1), ' '));
	name = ft_strndup(str, ' ');
	while ((*index) > 0 && (*room) && ((*room)->coord_x != x ||
		(*room)->coord_y != y) && ft_strcmp((*room)->name, name))
		room = &(*room)->next;
	if (((*index) > 0 && (*room)))
	{
		ft_strdel(&name);
		return (0);
	}
	if (!(*room))
		(*room) = (t_room *)malloc(sizeof(t_room));
	reset_room(room, name, x, y);
	(*room)->index = (*index)++;
	return (1);
}

void	add_start_end(t_data *data, char *str, char *tmp, int *index)
{
	t_room	*room;

	if ((!ft_strcmp(str, "##start")))
	{
		data->start = ft_strndup(tmp, ' ');
		data->index_start = (*index) - 1;
		room = find_room(data, data->index_start);
		room->ants = data->ants_count;
		room->step = 1;
		room->status = 0;
	}
	if ((!ft_strcmp(str, "##end")))
	{
		data->end = ft_strndup(tmp, ' ');
		data->index_end = (*index) - 1;
	}
}

t_room	*find_room(t_data *data, int index)
{
	t_room	*room;

	room = data->room;
	while (room && room->index != index)
		room = room->next;
	if (room)
		return (room);
	return (NULL);
}

int		start_end(t_data *data, char *str, int *index)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	data->u_color ? ft_putstr("\033[95m") : 0;
	ft_putendl(str);
	if (get_next_line(0, &tmp) && tmp && check_valid(data, tmp, 0) &&
		create_room(&(data->room), tmp, index))
	{
		if ((!ft_strcmp(str, "##start") && data->start == NULL) ||
			(!ft_strcmp(str, "##end") && data->end == NULL))
		{
			add_start_end(data, str, tmp, index);
			ft_strdel(&tmp);
			return (1);
		}
	}
	ft_strdel(&tmp);
	ft_strdel(&data->end);
	ft_strdel(&data->start);
	return (0);
}
