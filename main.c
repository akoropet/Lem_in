/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 22:04:01 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 06:41:16 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset(t_data *data)
{
	data->comment = NULL;
	data->moves = 0;
	data->way = NULL;
	data->ants = NULL;
	data->links = NULL;
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
	data->count_way = 0;
}

// void	residue(t_data *data)
// {
// 	char	*str;

// 	str = NULL;
// 	while (get_next_line(0, &str))
// 	{
// 		comment(data, str);
// 		ft_strdel(&str);
// 	}
// 	if ((!data->start && data->end) || (!data->end && data->start))
// 		data->error = 4;
// 	error(data);
// }

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

// void	free_bfs(t_data *data)
// {
// 	t_bfs	*r1;

// 	r1 = data->bfs;
// 	// free(r1->next);
// 	free(r1);
// }

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
	// free_bfs(data);
	free_way(data);
	while (data->links && data->links[i])
		free(data->links[i++]);
	free(data->links);
	free(data->ants);
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
			neig = find_room(data, i);
			if (neig && neig->step == step - 1 && !neig->reserv)
				return (neig);
		}
		i++;
	}
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
			room->step = data->count_room;
		room = room->next;
	}
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
		room = find_neig(data, room, room->step);
		if (room->index != data->index_start && room->index != data->index_end)
			room->reserv = 1;
	}
	return (room);
}

int		add_way(t_data *data)
{
	t_room	*room;
	t_way	**way;
	int		index;

	index = 1;
	way = &(data->way);
	room = find_room(data, data->index_end);
	if (room->step == data->count_room)
		return (0);
	while ((*way) && ++index)
		way = &(*way)->next;
	data->count_way++;
	(*way) = (t_way *)malloc(sizeof(t_way));
	(*way)->range = room->step;
	(*way)->index = index;
	(*way)->next = NULL;
	(*way)->queue = (int *)malloc(sizeof(int) * ((*way)->range));
	room = create_way(data, way, room);
	ft_clear(data);
	return (room->index == data->index_start);
}

void	u_error(void)
{
	ft_putstr("\033[91m");
	ft_putstr("Invalid flags! Please, use next template.\n");
	ft_putstr("{ ./lem_in  ");
	ft_putstr("--color --move --path --leak --comment --time ");
	ft_putstr("< [map path] }\n");
	ft_putstr("\033[0m");
}

void	u_reset(t_data *data)
{
	data->u_color = 0;
	data->u_moves = 0;
	data->u_paths = 0;
	data->u_leaks = 0;
	data->u_comment = 0;
	data->u_time = 0;
}

int		usage(t_data *data, int ac, char **av)
{
	int		i;

	i = 0;
	u_reset(data);
	while (++i < ac)
	{
		if (!ft_strcmp("--color", av[i]))
			data->u_color = 1;
		else if (!ft_strcmp("--move", av[i]))
			data->u_moves = 1;
		else if (!ft_strcmp("--path", av[i]))
			data->u_paths = 1;
		else if (!ft_strcmp("--leak", av[i]))
			data->u_leaks = 1;
		else if (!ft_strcmp("--comment", av[i]))
			data->u_comment = 1;
		else if (!ft_strcmp("--time", av[i]))
			data->u_time = 1;
		else
		{
			u_error();
			return (0);
		}
	}
	return (1);
}


int		main(int ac, char **av)
{
	t_data		*data;
	t_room		*room;
	int			status;


	data = (t_data *)malloc(sizeof(t_data));
	data->room = (t_room *)malloc(sizeof(t_room));
	if (!usage(data, ac, av))
		return (0);
	// data->bfs = (t_bfs *)malloc(sizeof(t_bfs));
	reset(data);
	status = 0;
	while (ants_count(data) && parcer(data, 0))
	{
		room = find_room(data, data->index_start);
		room->step = 1;
		room->status = 0;
		wave(data, find_room(data, data->index_start), 1);
		if (!data->way && ++status)
			break ;
		room = create_ants(data);
		while (data->way && data->way->range > 1 &&
			room->ants < data->ants_count && data->start)
		{
			transfer(data, 1);
			ft_putstr("\n");
			data->moves++;
		}
		// printf("count ine the end = %d\n", room->ants);
		// printf("MOVES == %d\n", data->moves);
		finish(data);
		status = 2;
		break ;
	}
	error(data, status);
		// printf("222222\n");
		// printf("error = %d\n", data->error);
		// residue(data);
	// system("leaks lem_in");
	freesher(data);
	// system("leaks lem_in");
	return (0);
}
