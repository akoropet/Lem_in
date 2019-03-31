/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:44:16 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 01:56:15 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
