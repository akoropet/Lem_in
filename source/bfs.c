/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:34:40 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/17 18:55:02 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_room	*find_wave(t_data *data, int step)
{
	t_room	*neig;

	neig = data->room;
	while (neig)
	{
		if (neig->step == step && !neig->status && !neig->reserv)
		{
			neig->status = 1;
			return (neig);
		}
		neig = neig->next;
	}
	return (NULL);
}

void	wave(t_data *data, t_room *room, int step, int i)
{
	t_room	*end;
	t_room	*neig;

	end = find_room(data, data->index_end);
	while (end->step == data->count_room && step < data->count_room)
	{
		while ((room = find_wave(data, step)))
		{
			i = -1;
			while (++i < data->count_room)
			{
				if (data->links[room->index][i] == '1' &&
					(neig = find_room(data, i)) && (neig->step > step) &&
					!neig->reserv)
					neig->step = step + 1;
			}
		}
		step++;
		if ((end->step != data->count_room || step == data->count_room) &&
			add_way(data))
		{
			end->step = data->count_room;
			step = 1;
		}
	}
}

int		one_way(t_data *data)
{
	if (!data->links)
		return (1);
	if (data->links[data->index_start][data->index_end] == '1')
	{
		data->way = (t_way *)malloc(sizeof(t_way));
		data->way->index = 1;
		data->way->range = 2;
		data->way->queue = (int *)malloc(sizeof(int) * 2);
		data->way->queue[0] = data->index_end;
		data->way->queue[1] = data->index_start;
		data->way->next = NULL;
		return (1);
	}
	return (0);
}

void	ft_clear(t_data *data)
{
	t_room	*room;

	room = data->room;
	while (room)
	{
		if (!room->reserv)
		{
			if (room->index != data->index_start)
				room->step = data->count_room;
			room->status = 0;
		}
		if (room->index == data->index_end)
			room->step = data->count_room;
		room = room->next;
	}
}

t_room	*find_neig(t_data *data, t_room *room, int step)
{
	int		i;
	t_room	*neig;

	i = 0;
	while (i < data->count_room)
	{
		if (data->links[room->index][i] == '1')
		{
			neig = find_room(data, i);
			if (neig && neig->step == step - 1 && !neig->reserv)
				return (neig);
		}
		i++;
	}
	return (NULL);
}
