/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 22:04:01 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 00:02:02 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset(t_data *data)
{
	// data->bfs = NULL;
	data->moves = 0;
	data->way = NULL;
	data->ants = NULL;
	data->links = NULL;
	data->bfs->next = NULL;
	data->bfs->queue = 0;
	data->room->next = NULL;
	data->room->name = NULL;
	data->room->index = 0;
	data->room->ants = 0;
	data->room->coord_x = 0;
	data->room->coord_y = 0;
	data->count_room = 0;
	data->ants_count = 0;
	data->start = NULL;
	data->end = NULL;
	data->index_start = 0;
	data->index_end = 0;
	data->error = 0;
	data->comment_color = 0;
	data->comment_error = 0;
	data->comment_moves = 0;
	data->count_way = 0;
}

void	residue(t_data *data)
{
	char	*str;

	str = NULL;
	while (get_next_line(0, &str))
	{
		comment(data, str);
		ft_strdel(&str);
	}
	if ((!data->start && data->end) || (!data->end && data->start))
		data->error = 4;
	// printf("error = %d\n", data->error);
	// printf("start = |%s|. end = |%s|\n", data->start, data->end);
	error(data);
}

void	free_room(t_data *data)
{
	t_room	*r1;
	t_room	*r2;

	r1 = data->room;
	r2 = r1->next;
	while (r2)
	{
		free(r1->name);
		free(r1);
		r1 = r2;
		r2 = r2->next;
	}
	free(r1->name);
	// free(r1->next);
	free(r1);
}

void	free_bfs(t_data *data)
{
	t_bfs	*r1;

	r1 = data->bfs;
	// free(r1->next);
	free(r1);
}

void	free_way(t_data *data)
{
	t_way	*r1;
	t_way	*r2;

	r1 = data->way;
	if (r1)
	{
		r2 = r1->next;
		while (r2)
		{
			free(r1->queue);
			free(r1);
			r1 = r2;
			r2 = r2->next;
		}
		free(r1->queue);
		free(r1);
	}
}

void	freesher(t_data *data)
{
	int		i;

	i = 0;
	free_room(data);
	free_bfs(data);
	free_way(data);
	// printf("1\n");
	while (data->links && data->links[i])
	{
		// printf("===\n");
		free(data->links[i++]);
	}
	free(data->links);
	free(data->ants);
	// while (data->ants[i])
	// {
		// free(data->ants[i]);
		// i++;
	// }
	// free(data->room);
	// printf("1\n");
	// if (data->bfs)
	// {
	// 	free(data->bfs);
	// 	printf("=====\n");
	// }
	// free(data->way);
	// printf("_%p\n", data->start);
	free(data->start);
	free(data->end);
	// free(data);
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
			// printf("index room = %d, i = %d\n", room->index, i);
			neig = find_room(data, i);
			// printf("	step room = %d, step neig = %d\n", room->step, neig->step);
			// printf("index room = %d, i = %d, neig = %s\n", room->index, i, neig->name);
			if (neig && neig->step == step - 1 && !neig->reserv)
			{
				// printf("neig = %s\n", neig->name);
				return (neig);
			}
		}
		i++;
	}
	// printf("null\n");
	return (NULL);
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
		{
			// printf("room end ste[ = %d\n", room->step);
			room->step = data->count_room;
			// printf("room end ste[ = %d\n", room->step);
		}
		room = room->next;
	}
}

int		add_way(t_data *data)
{
	t_room	*room;
	t_way	**way;
	int		index;
	int		i;

	index = 1;
	i = 0;
	way = &(data->way);
	room = find_room(data, data->index_end);
	// printf("step = %d, count_room = %d\n", room->step, data->count_room);
	if (room->step == data->count_room)
	{
		// printf("END\n");
		return (0);
	}
	// printf("====\n");
	while ((*way) && ++index)
	{
		// printf("1111\n");
		way = &(*way)->next;
	}
	// printf("3333\n");
	data->count_way++;
	(*way) = (t_way *)malloc(sizeof(t_way));
	// printf("4444\n");
	(*way)->range = room->step;
	// printf("5555\n");
	(*way)->index = index;
	(*way)->next = NULL;
	(*way)->queue = (int *)malloc(sizeof(int) * ((*way)->range));
	// printf("6666\n");
	while (i < (*way)->range)
	{
		// printf("room->%s, index = %d\n", room->name, room->index);
		(*way)->queue[i++] = room->index;
		if (room->index == data->index_start)
			break ;
		// printf("queue = %d\n", (*way)->queue[i - 1]);
		room = find_neig(data, room, room->step);
		if (!room)
		{
			free((*way)->queue);
			free((*way));
			(*way) = NULL;
			// printf("ERRROOOOOORRRRRRRRRR!!!!!!!!!!!!!!!!!!!\n");
			return (0);
		}
		// printf("%s\n", room--);
		// printf("%d\n", room->reserv);
		// printf("1111 i = %d\n", i);
		// if (!room || room->reserv)
		// {
		// 	// printf("%s %d\n", room->name, room->reserv);
		// 	printf("FEEEEEEE\n");
		// 	free((*way)->queue);
		// 	free((*way));
		// 	(*way) = NULL;
		// 	return (0);
		// }
		// printf("room->%s\n", room->name);
		// printf("======\n");
		if (room->index != data->index_start && room->index != data->index_end)
		{
			// printf("reserv!!!!!!!!!!!\n");
			// printf("room = |%s|, reserv = %d\n", room->name, room->reserv);
			room->reserv = 1;
			// printf("room = |%s|, reserv = %d\n", room->name, room->reserv);
		}
	}
	ft_clear(data);
	// printf("clear done\n");
	return (room->index == data->index_start);
}

int		main(void)
{
	t_data		*data;
	t_room		*room;
	int n;

	data = (t_data *)malloc(sizeof(t_data));
	data->room = (t_room *)malloc(sizeof(t_room));
	data->bfs = (t_bfs *)malloc(sizeof(t_bfs));
	ft_printf("start\n");
	reset(data);
	ft_printf("reset done\n");
	if (ants_count(data) && parcer(data, 0))
	{
		ft_printf("parcer done\n");
		// printf("1111111\n");
		// residue(data);
		n = 0;
		room = find_room(data, data->index_start);
		room->step = 1;
		room->status = 0;
		printf("start wave\n");

		wave(data, 1);
		// printf("+\n");
		// add_way(data);
		printf("=========================================================================\n");
		// while (add_way(data))
		// {
		// 	printf("	2\n");
		// 	printf("=========================================================================\n");
		// 	wave(data, 1);
		// 	printf("3\n");
		// }
		printf("==========\n");
		// ft_bfs(data, room, 0);
		// add_way(data);
		// ft_bfs(data, room, 0);
		// add_way(data);
		// ft_bfs(data, room, 0);
		// add_way(data);
		// while (add_way(data))
		// 	printf("done\n");
		// while (add_way(data))
		// {
		// 	printf("finish add_way\n");
		// 	ft_bfs(data, room, 0);
		// 	printf("finish bfs\n");
		// }
		// room = data->room;
		// while (room)
		// {
		// 	printf("room[%d] = %s, step = %d\n", room->index, room->name, room->step);
		// 	room = room->next;
		// }


		// t_way		*way;
		// way = data->way;
		// int i;
		// while (way)
		// {
		// 	i = 0;
		// 	while (i < way->range)
		// 	{
		// 		// room = find_room(data, way->queue[i++]);
		// 		// printf("%s->", room->name);
		// 		printf("%d->", way->queue[i++]);
		// 	}
		// 	printf("\n\n");
		// 	way = way->next;
		// }


		// while (ft_bfs(data))
		// {
		// 	printf("bfs find\n");
		// 	reset_bfs(data);
		// 	printf("bfs clear\n");
		// }
		ft_printf("bfs done\n");
		// // printf("!!!!!!! %d %d %d\n", data->way->queue[0], data->way->queue[1], data->way->queue[2]);
		

		room = create_ants(data);
		

		// ft_printf("created grid\n");
		// // printf("!!!!!!! %d %d %d\n", data->way->queue[0], data->way->queue[1], data->way->queue[2]);
		// // printf("room_end = %s\n", room->name);
		// // int i = 0;
		// // while (data->ants[i])
		// // 	printf("->%s\n", data->ants[i++]);

		printf("123123\n");
		// int ant = 1;
		while (data->way && data->way->range > 1 &&
			room->ants < data->ants_count && data->start)
		{
			transfer(data, 1);
			printf("\n");
			data->moves++;
			// ant = 1;
			// // ft_printf("transfer cycle\n");
			// while (ant <= data->ants_count && room->ants < data->ants_count && transfer(data, ant))
			// {
			// 	// printf("transfer = %d\n", ant);
			// 	printf("\n");
			// 	ant++;
			// }
			// data->moves++;
			// printf("\n");
			// transfer(data, 1);
			// printf("ants int end = %d\n", room->ants);
			// printf("	cycle\n");
			// ft_strcpy(data->output + ft_strlen(data->output), "\n");
			// printf(" %d(%d, %d)", ++n, data->ants_count, room->ants);
		}
		// printf("transfer finish\n");
		// ft_putstr(data->output);

		// ft_printf("transfer done\n");
		// data->error = (data->way && data->way->range <= 1) ||
		// 	!data->way ? 4 : data->error;
		// (data->way && data->way->range <= 1) || !data->way ?
		// 	error(data) : finish(data);
		printf("count ine the end = %d\n", room->ants);
		printf("MOVES == %d\n", data->moves);
	}
	else
	{
		error(data);
		// printf("222222\n");
		// printf("error = %d\n", data->error);
		// residue(data);
	}
	freesher(data);
	system("leaks lem_in");
	return (0);
}
