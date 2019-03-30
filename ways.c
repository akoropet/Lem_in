/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:44:16 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 00:01:47 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// int		add_way(t_data *data, t_way **way, t_room *room)
// {
// 	int		i;
// 	int		numb;
// 	int		step;

// 	i = 0;
// 	numb = -1;
// 	while ((*way) != NULL && --numb)
// 		(way) = &(*way)->next;
// 	(*way) = (t_way *)malloc(sizeof(t_way));
// 	// printf("%p\n", &(*way));
// 	// printf("%p\n", (*way));
// 	(*way)->next = NULL;
// 	(*way)->range = room->step + 1;
// 	(*way)->queue = (int *)malloc(sizeof(int) * ((*way)->range));
// 	// printf("%p\n", (*way)->queue);
// 	// printf("%p\n", &(*way)->queue);
// 	(*way)->queue[i] = room->index;
// 	(*way)->index = numb * -1;
// 	step = room->step;
// 	room->step = data->count_room;
// 	// printf("queue[%d] = %d, room->index = %d\n", i, (*way)->queue[i], room->index);
// 	while (++i < (*way)->range)
// 	{
// 		room = find_neighbor(data, room, step);
// 		room->step = numb;
// 		(*way)->queue[i] = room->index;
// 		// printf("queue[%d] = %d, room->index = %d\n", i, (*way)->queue[i], room->index);
// 		step--;
// 	}
// 	if ((*way)->range == 2)
// 		return (0);
// 	return (1);
// }

// t_room	*find_neighbor(t_data *data, t_room *r, int step)
// {
// 	t_room	*room;
// 	int		i;

// 	i = 0;
// 	while (data->links[r->index][i])
// 	{
// 		if (data->links[r->index][i] == '1')
// 		{
// 			room = find_room(data, i);
// 			if (room && room->step == step - 1)
// 				return (room);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

int		normal_way(t_data *data, t_way *w)
{
	t_way	*way;
	int		res;

	way = data->way;
	res = 0;
	while (way && way->index < w->index)
	{
		res += w->range - way->range;
		way = way->next;
	}
	// printf("ants_count = %d, res = %d, index = %d\n", data->ants_count, res, w->index);
	return (data->ants_count > res);
}

void	clear_way(t_data *data)
{
	// t_way	*start;
	t_way	*way;
	int		len;

	way = data->way;
	len = 0;
	// start = way;
	// printf("+++++\n");
	// printf("count_way = %d\n", data->count_way);
	while (way && normal_way(data, way))
	{
		len++;
		// printf("way++\n");
		way = way->next;
	}
	data->count_way = len;
	// printf("count_way = %d\n", data->count_way);
	// printf("=====\n");
	// while (way)
	// {
	// 	printf("delete index %d\n", way->index);
	// 	printf("1111\n");
	// 	tmp = &way;
	// 	way = way->next;
	// 	free((*tmp)->queue);
	// 	free((*tmp));
	// 	(*tmp) = NULL;
	// }
	// while (start)
	// {
	// 	printf("waaaaaaaaaayy!!!\n");
	// 	start = start->next;
	// }
	// printf("end\n");
}

t_room	*create_ants(t_data *data)
{
	t_room			*room;
	long long int	i;
	int				n;

	i = 0;
	n = -1;
	// printf("?!!!!!!! %d %d %d\n", data->way->queue[0], data->way->queue[1], data->way->queue[2]);
	data->ants = (char **)malloc(sizeof(char *) * (data->ants_count + 1));
	// printf("?!!!!!!! %d %d %d\n", data->way->queue[0], data->way->queue[1], data->way->queue[2]);
	data->ants[data->ants_count] = NULL;
	// printf("?!!!!!!! %d %d %d\n", data->way->queue[0], data->way->queue[1], data->way->queue[2]);
	// printf("malloc start\n");
	// if (!(data->output = (char **)malloc(sizeof(char *) * 101)))
	// 	printf("errror\n");
	// data->output[100] = NULL;
	// printf("malloc start 2\n");
	// while (++n < 100)
	// 	data->output[n] = ft_strnew(4000);
	// printf("malloc end\n");
	// data->output = ft_memalloc(400000);
	// printf("111\n");
	n = 0;
	data->locat = (char **)malloc(sizeof(char *) * (data->ants_count));
	while (n < data->ants_count)
	{
		data->locat[n] = ft_strnew(data->count_room);
		ft_memset(data->locat[n], '0', data->count_room);
		data->locat[n][data->index_start] = '1';
		n++;
	}
	// n = 0;
	// while (n < data->ants_count)
	// 	printf("%s\n", data->locat[n++]);
	// t_way	*way = data->way;
	// while (way)
	// {
	// 	printf("+1\n");
	// 	way = way->next;
	// }
	clear_way(data);
	// printf("222\n");
	while (i < data->ants_count)
	{
		room = find_room(data, data->index_start);
		data->ants[i] = room->name;
		// printf("|%s|->|%s|\n", room->name, data->ants[i]);
		i++;
	}
	// printf("?!!!!!!! %d %d %d\n", data->way->queue[0], data->way->queue[1], data->way->queue[2]);
	// printf("33333\n");
	ft_putstr("\n");
	return (find_room(data, data->index_end));
}

// void	check_way(t_data *data)
// {
// 	t_way	**w1;
// 	t_way	**w2;
// 	t_way	**wr;

// 	w1 = &(data->way);
// 	wr = &(data->way);
// 	while ((*w1))
// 	{
// 		wr = &(*w1)->next;
// 		while ((*wr) && (*w2))
// 		{
// 			w2 = &(*wr)->next;
// 			if ((*w1)->range == (*w2)->range && check_queue(w1, w2))
// 			{
// 				(*wr)->next = (*w2)->next;
// 				free((*w1));
// 			}
// 			w2 = &(*w2)->next;
// 			wr = &(*wr)->next;
// 		}
// 		w1 = &(*w1)->next;
// 	}
// }

// int		check_queue(t_way **w1, t_way **w2)
// {
// 	int		i;

// 	i = 0;
// 	while (i < (*w1)->range && i < (*w2)->range &&
// 		(*w1)->queue[i] == (*w2)->queue[i])
// 		i++;
// 	if (i == (*w1)->range && i == (*w2)->range)
// 		return (0);
// 	return (1);
// }
