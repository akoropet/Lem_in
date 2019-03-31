/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:48:46 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 05:51:48 by akoropet         ###   ########.fr       */
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
		if (data->u_color && room1->index == data->index_start)
			ft_putstr("\033[92m");
		else if (data->u_color && room2->index == data->index_end)
			ft_putstr("\033[91m");
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

// void	move_ants(t_data *data, t_way *way, int i, int ant)
// {
// 	t_room	*room1;
// 	t_room	*room2;
// 	char	*str;
// 	char	*num;
// 	// char	*tmp;

// 	room1 = find_room(data, way->queue[i]);
// 	room2 = find_room(data, way->queue[i - 1]);
// 	// printf("ant = %d\n", ant);
// 	// printf("%d+%d\n", i, (i - 1));
// 	// printf("%d_%d\n", way->queue[i], way->queue[i - 1]);
// 	// printf("%s = %s\n", room1->name, room2->name);
// 	// printf("|%d %d %d|\n", room2->ants, room2->index, data->index_end);
// 	if (i > 0 && (!room2->ants || room2->index == data->index_end))
// 	{
// 		room1->ants--;
// 		room2->ants++;
// 		// printf("in room -> %d\n", room2->index);
// 		// printf("data->ants[%d] = %s, room2->name = %s\n", ant - 1, data->ants[ant - 1], room2->name);
// 		data->ants[ant - 1] = room2->name;
// 		// printf("data->ants[%d] = %s, room2->name = %s\n", ant - 1, data->ants[ant - 1], room2->name);
// 		// if (data->comment_color && room1->index == data->index_start)
// 		// 	ft_putstr("\033[92m");
// 		// else if (data->comment_color && room2->index == data->index_end)
// 		// 	ft_putstr("\033[91m");
// 		// else if (data->comment_color)
// 		// 	ft_putstr("\033[93m");
// 		str = ft_memalloc(20);
// 		str[0] = 'L';
// 		num = ft_itoa(ant);
// 		ft_strcpy(str + 1, num);
// 		ft_strcpy(str + ft_strlen(num) + 1, "-");
// 		ft_strcpy(str + ft_strlen(num) + 2, data->ants[ant - 1]);
// 		ft_strcpy(str + ft_strlen(data->ants[ant - 1]) + ft_strlen(num) + 2, " ");
// 		ft_strcpy(data->output + ft_strlen(data->output), str);
// 		ft_strdel(&num);
// 		// ft_strdel(&str);
// 		// ft_putchar('L');
// 		// ft_putnbr(ant);
// 		// ft_putchar('-');
// 		// ft_putstr(data->ants[ant - 1]);
// 		// ft_printf("L%d-%s ", ant, data->ants[ant - 1]);
// 		// ft_putstr(" \033[0m");
// 	}
// }




// void	transfer(t_data *data, int ant)
// {
// 	t_room	*room;
// 	t_way	*way;
// 	int		i;
// 	// int		ant;

// 	while (ant <= data->ants_count)
// 	{
// 		// printf("way\n");
// 		way = data->way;
// 		// printf("way?\n");
// 		while (way && data->count_way >= way->index && ant <= data->ants_count && ft_go(data, way, data->index_start))
// 		{
// 			// printf("way!\n");
// 			i = 0;
// 			// printf("_way_index = %d\n", way->queue[i]);
// 			while (++i < way->range && ant <= data->ants_count)
// 			{
// 				// printf("way_index = %d\n", way->queue[i]);
// 				// printf("seg?\n");
// 				room = find_room(data, way->queue[i]);
// 				// printf("%d\n", way->index);
// 				// printf("fault?\n");
// 				if (!ft_strcmp(room->name, data->ants[ant - 1]) && ft_go(data, way, i))
// 				{
// 					// printf("range = %d\n", way->range);
// 					// printf("queue = %d\n", way->queue[i - 1]);
// 					// printf("i = %d\n", i);
// 					// printf("->%s[%d]\n", data->ants[ant - 1], ant);
// 					// printf("ant = %d\n", ant);
// 					move_ants(data, way, i, ant++);
// 					// printf("===================\n");
// 					// break ;
// 				}
// 			}
// 			way = way->next;
// 			if (!way)
// 				ants++;
// 		}
// 	}
// 	data->moves++;
// 	printf("moves = %d\n", data->moves);
// 	ft_putstr("\n");
// }

