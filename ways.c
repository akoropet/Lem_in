/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:44:16 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 16:44:20 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		normal_way(t_data *data, t_way *w)
{
	t_way	*way;
	int		res;

	way = data->way;
	res = 0;
	while (way && w && way->index < w->index)
	{
		res += w->range - way->range;
		way = way->next;
	}
	return (data->ants_count > res);
}

void	clear_way(t_data *data)
{
	t_way	*way;
	int		len;

	way = data->way;
	len = 0;
	while (way && normal_way(data, way))
	{
		len++;
		way = way->next;
	}
	data->count_way = len;
}

t_room	*create_ants(t_data *data)
{
	t_room			*room;
	long long int	i;
	int				n;

	i = 0;
	n = 0;
	data->ants = (char **)malloc(sizeof(char *) * (data->ants_count + 1));
	data->ants[data->ants_count] = NULL;
	data->locat = (char **)malloc(sizeof(char *) * (data->ants_count));
	while (n < data->ants_count)
	{
		data->locat[n] = ft_strnew(data->count_room);
		ft_memset(data->locat[n], '0', data->count_room);
		data->locat[n][data->index_start] = '1';
		n++;
	}
	clear_way(data);
	while (i < data->ants_count)
	{
		room = find_room(data, data->index_start);
		data->ants[i] = room->name;
		i++;
	}
	ft_putstr("\n");
	return (find_room(data, data->index_end));
}

int		add_way(t_data *data)
{
	t_room	*room;
	t_way	**way;
	int		index;

	index = 1;
	way = &(data->way);
	room = find_room(data, data->index_end);
	while ((*way) && ++index)
		way = &(*way)->next;
	data->count_way++;
	(*way) = (t_way *)malloc(sizeof(t_way));
	(*way)->range = room->step;
	(*way)->index = index;
	(*way)->next = NULL;
	(*way)->queue = (int *)malloc(sizeof(int) * ((*way)->range));
	if (!(room = create_way(data, way, room)))
	{
		free((*way)->queue);
		free((*way));
		(*way) = NULL;
		return (0);
	}
	ft_clear(data);
	return (room->index == data->index_start);
}

t_room	*create_way(t_data *data, t_way **way, t_room *room)
{
	int		i;

	i = 0;
	while (i < (*way)->range)
	{
		(*way)->queue[i++] = room->index;
		if (room->index == data->index_start)
			break ;
		if (!(room = find_neig(data, room, room->step)))
			return (NULL);
		if (room->index != data->index_start && room->index != data->index_end)
			room->reserv = 1;
	}
	return (room);
}
