/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:48:46 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 16:43:41 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_go(t_data *data, t_way *w, int i)
{
	t_room		*room;
	t_way		*way;
	int			res;

	res = 0;
	if (w->queue[i] == data->index_start)
	{
		room = find_room(data, data->index_start);
		way = data->way;
		while (room->ants && way->index < w->index)
		{
			res += w->range - way->range;
			way = way->next;
		}
		return (room->ants > res);
	}
	return (1);
}

int		move_ants(t_data *data, t_way *way, int i, int ant)
{
	t_room	*room1;
	t_room	*room2;
	int		n;

	room2 = find_room(data, way->queue[i - 1]);
	if (!room2->ants || room2->index == data->index_end)
	{
		n = 0;
		data->locat[ant - 1][way->queue[i]] = '0';
		data->locat[ant - 1][way->queue[i - 1]] = '1';
		room1 = find_room(data, way->queue[i]);
		room1->ants--;
		room2->ants++;
		if (data->u_color && room2->index == data->index_end)
			ft_putstr("\033[91m");
		else if (data->u_color && room1->index == data->index_start)
			ft_putstr("\033[92m");
		else if (data->u_color)
			ft_putstr("\033[93m");
		ft_printf("L%d-%s ", ant, room2->name);
		return (1);
	}
	return (0);
}

int		transfer(t_data *data, int ant)
{
	t_way	*way;
	int		i;

	way = data->way;
	while (ant <= data->ants_count)
	{
		way = data->way;
		if (data->locat[ant - 1][way->queue[0]] == '1')
			ant++;
		while (way && ant <= data->ants_count &&
			data->locat[ant - 1][way->queue[0]] != '1')
		{
			i = 1;
			while (ant <= data->ants_count && i < way->range)
			{
				if (data->locat[ant - 1][way->queue[i]] == '1' &&
					ft_go(data, way, i))
					move_ants(data, way, i, ant);
				i++;
			}
			way = way->next;
		}
		ant++;
	}
	return (1);
}

int		ft_algorithm(t_data *data, int status)
{
	t_room	*room;

	room = find_room(data, data->index_start);
	room->step = 1;
	room->status = 0;
	if (!one_way(data))
		wave(data, find_room(data, data->index_start), 1, -1);
	if (!data->way && ++status)
		return (status);
	room = create_ants(data);
	while (data->way && data->way->range > 1 &&
		room->ants < data->ants_count && data->start)
	{
		transfer(data, 1);
		ft_putstr("\n");
		data->moves++;
	}
	return (status);
}
