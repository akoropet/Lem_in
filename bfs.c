/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:34:40 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 07:42:22 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


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

void	wave(t_data *data, t_room *room, int step)
{
	int		i;
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
		if (end->step != data->count_room && add_way(data))
		{
			end->step = data->count_room;
			step = 1;
		}
	}
}


// int		ft_bfs(t_data *data, t_room *room, int step)
// {
// 	int		i;
// 	t_room	*neig;

// 	i = 0;
// 	room->step = step++;
// 	room->status = 1;
// 	while (i < data->count_room)
// 	{
// 		if (data->links[room->index][i] == '1' && (neig = find_room(data, i)) &&
			// (!neig->status || neig->step > step) && !neig->reserv)
// 		{
// 			neig->step = step;
// 			ft_bfs(data, neig, step);
// 			if (neig->index == data->index_end)
// 				break ;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// t_room	*find_wave(t_data *data, int i, int step)

// void	ft_bfs(t_data *data, t_room *room, int step)
// {
// 	int		i;
// 	int		step;
// 	t_room	*neig;
// 	t_room	*end;

// 	end = find_room(data, data->index_end);
// 	step = 1;
// 	while (end->step == data->count_room)
// 	{
// 		i = 0;
// 		while (i < data->count_room)
// 		{
// 			if (data->links[room->index][i] == '1' && (neig = find_room(data, i)))
// 			{

// 			}
// 			i++;
// 		}
// 	}
// }












// void	bfs_start(t_data *data)
// {
// 	t_room	**room;
// 	t_bfs	**bfs;

// 	room = &(data->room);
// 	bfs = &(data->bfs);
// 	while ((*room) && data->index_start != (*room)->index)
// 		room = &(*room)->next;
// 	(*room)->step = 0;
// 	(*bfs)->queue = (*room)->index;
// 	(*bfs)->next = NULL;
// }

// int		ft_bfs(t_data *data)
// {
// 	t_room	*room;
// 	t_bfs	*bfs;
// 	int		index;

// 	bfs_start(data);
// 	while (data->bfs != NULL)
// 	{
// 		index = 0;
// 		bfs = data->bfs;
// 		while (index < data->count_room && room->index != data->index_end)
// 		{
// 			room = find_room(data, index);
// 			if (data->links[bfs->queue][index] == '1' &&
// 				room->step == data->count_room)
// 				add_in_queue(&bfs, find_room(data, index));
// 			index++;
// 		}
// 		add_step_and_delete_first(data);
// 	}
// 	room = find_room(data, data->index_end);
// 	if (room->step == data->count_room)
// 		return (0);
// 	return (add_way(data, &(data->way), room));
// }

// void	reset_bfs(t_data *data)
// {
// 	t_room	*room;

// 	room = data->room;
// 	while (room)
// 	{
// 		if (room->step > 0)
// 			room->step = data->count_room;
// 		room = room->next;
// 	}
// 	data->bfs = (t_bfs *)malloc(sizeof(t_bfs));
// 	// printf("%p\n", &data->bfs);
// 	// printf("%p\n", data->bfs);
// }

// void	add_in_queue(t_bfs **b, t_room *room)
// {
// 	t_bfs	**bfs;

// 	bfs = b;
// 	while ((*bfs))
// 		bfs = &(*bfs)->next;
// 	(*bfs) = (t_bfs *)malloc(sizeof(t_bfs));
// 	// printf("%p\n", (*bfs));
// 	// printf("%p\n", &(*bfs));
// 	(*bfs)->queue = room->index;
// 	(*bfs)->next = NULL;
// }

// void	add_step_and_delete_first(t_data *data)
// {
// 	t_room	*room1;
// 	t_room	*room2;
// 	t_bfs	*bfs;
// 	t_bfs	*b;

// 	room1 = find_room(data, data->bfs->queue);
// 	bfs = data->bfs;
// 	while (bfs)
// 	{
// 		room2 = find_room(data, bfs->queue);
// 		if (room1->step < room2->step)
// 			room2->step = room1->step + 1;
// 		bfs = bfs->next;
// 	}
// 	bfs = data->bfs;
// 	b = bfs;
// 	bfs = bfs->next;
// 	free(b);
// 	data->bfs = bfs;
// }

