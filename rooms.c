/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:41:51 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/29 14:03:54 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

	// ft_putendl(str);
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
	// ft_strdel(&name);
	// printf("_%p\n", (*room));
	// printf("_%p\n", &(*room));
	// (*room)->name = name;
	// (*room)->next = NULL;
	// (*room)->coord_x = x;
	// (*room)->coord_y = y;
	// (*room)->index = (*index)++;
	// (*room)->ants = 0;
	// printf("%s=%s\n", name, (*room)->name);
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
		// printf("%p\n", &str);
		// printf("%p\n", data->start);
		// data->index_start = data->index_start - 1;
		// printf("\nindex_start = %d\n\n", data->index_start);
	}
	if ((!ft_strcmp(str, "##end")))
	{
		data->end = ft_strndup(tmp, ' ');
		data->index_end = (*index) - 1;
		// printf("\nindex_end = %d\n\n", data->index_end);
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
	if (comment(data, str))
		return (1);
	// if (get_next_line(0, &tmp))
		// ft_putendl(tmp);
	if (get_next_line(0, &tmp) && tmp && check_valid(tmp) && create_room(&(data->room), tmp, index))
	{
		ft_putendl(tmp);
		if ((!ft_strcmp(str, "##start") && data->start == NULL) ||
			(!ft_strcmp(str, "##end") && data->end == NULL))
		{
			add_start_end(data, str, tmp, index);
			ft_strdel(&tmp);
			return (1);
		}
		// add_start_end(data, str, tmp, index);
		// ft_strdel(&tmp);
		// return (1);
	}
	ft_putendl(tmp);
	ft_strdel(&tmp);
	ft_strdel(&data->end);
	ft_strdel(&data->start);
	return (0);
}
