/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 22:04:01 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/09 23:11:59 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset(t_data *data)
{
	// data->bfs = NULL;
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
}

int		ants_count(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (get_next_line(0, &str) <= 0 && ++data->error)
		return (0);
	// ft_putstr("\033[91m");
	ft_putendl(str);
	// ft_putstr("\033[0m");
	if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0' && ++data->error)
	{
		ft_strdel(&str);
		return (0);
	}
	if ((data->ants_count = ft_atoi(str)) == 0 && ++data->error)
		return (0);
	ft_strdel(&str);
	return (1);
}

void	reset_room(t_room **room, char *name, int x, int y)
{
	(*room)->name = name;
	(*room)->next = NULL;
	(*room)->coord_x = x;
	(*room)->coord_y = y;
	(*room)->ants = 0;
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
	return (1);
}

int		check_valid(char *str)
{
	int		j;
	int		i;

	i = 0;
	j = i;
	// printf("check_valid start->|%s|\n\n", str);
	while (str[i] && str[i] != ' ')
		i++;
	if (j == i)
		return (0);
	i = str[++i] && (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	if (!str[i] || (str[i] && !ft_isdigit(str[i])))
		return (0);
	while (str[i] && str[i] != ' ' && ft_isdigit(str[i]))
		i++;
	i = str[++i] && (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	if (!str[i] || (str[i] && !ft_isdigit(str[i])))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
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
		printf("%p\n", &str);
		printf("%p\n", data->start);
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

int		start_end(t_data *data, char *str, int *index)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	// printf("\n'start_end' start->|%s|\n", str);
	// ft_putstr("\033[91m");
	ft_putendl(str);
	// ft_putstr("\033[0m");
	if (get_next_line(0, &tmp) && check_valid(tmp) &&
		create_room(&(data->room), tmp, index))
	{
		// printf("	tmp = |%s|\n", tmp);
		ft_putendl(tmp);
		if ((!ft_strcmp(str, "##start") && data->start != NULL) ||
			(!ft_strcmp(str, "##end") && data->end != NULL))
		{
			data->end = NULL;
			data->start = NULL;
			return (0);
		}
		add_start_end(data, str, tmp, index);
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	data->end = NULL;
	data->start = NULL;
	return (0);
}

int		room_or_link(t_room **r, char *str)
{
	t_room	**room;
	char	*room_name;

	if (ft_strchr(str, '-'))
	{
		// ft_putendl(str);
		room = r;
		room_name = ft_strndup(str, '-');
		while ((*room))
		{
			if (!ft_strcmp((*room)->name, room_name))
			{
				ft_strdel(&room_name);
				return (1);
			}
			room = &(*room)->next;
		}
		ft_strdel(&room_name);
	}
	return (0);
}

void	creare_tabl(t_data *data, int index)
{
	int		n;
	int		i;

	data->count_room = index;
	n = data->count_room;
	data->links = (char **)malloc(sizeof(char *) * (n + 1));
	// printf("%p\n", &data->links);
	// printf("%p\n", data->links);
	data->links[n] = NULL;
	i = 0;
	while (i < n)
	{
		data->links[i] = ft_memalloc(n + 1);
		ft_memset(data->links[i], '0', n);
		i++;
	}
}

void	add_links(t_room **room1, t_room **room2, t_data *data, char **link)
{
	ft_strdel(link);
	data->links[(*room2)->index][(*room1)->index] = '1';
	data->links[(*room1)->index][(*room2)->index] = '1';
	(*room1)->step = data->count_room;
	(*room2)->step = data->count_room;
}

int		links(t_data *data, t_room **r, char *str)
{
	t_room	**room1;
	t_room	**room2;
	char	*link;

	room1 = r;
	if (str[0] == '#' && str[1] != '#')
		return (1);
	link = ft_strndup(str, '-');
	while ((*room1) && ft_strcmp((*room1)->name, link))
		room1 = &(*room1)->next;
	if ((*room1) && !ft_strcmp((*room1)->name, link))
	{
		ft_strdel(&link);
		room2 = r;
		link = ft_strdup(ft_strchr(str, '-') + 1);
		while ((*room2) && ft_strcmp((*room2)->name, link))
			room2 = &(*room2)->next;
		if ((*room2) && !ft_strcmp((*room2)->name, link))
		{
			add_links(room1, room2, data, &link);
			return (1);
		}
	}
	ft_strdel(&link);
	return (0);
}

int		valid_links(t_data *data, char **str)
{
	t_room	*room;
	char	*name;

	room = data->room;
	name = ft_strndup((*str), '-');
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	ft_strdel(&name);
	if (!room || !ft_strchr((*str), '-'))
		return (0);
	room = data->room;
	name = ft_strchr((*str), '-') + 1;
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	if (!room)
		return (0);
	return (1);
}

void	comment(t_data *data, char *str)
{
	if (!ft_strcmp("#color", str))
		data->comment_color = 1;
	if (!ft_strcmp("#error", str))
		data->comment_error = 1;
}

int		parcer_links(t_data *data, char **str)
{
	while ((*str))
	{
		if ((*str)[0] == '#' && (*str)[1] == '#')
			break ;
		else if ((*str)[0] != '#')
		{
			// ft_putstr("\033[91m");
			ft_putendl((*str));
			// ft_putstr("\033[0m");
			if (!valid_links(data, str))
			{
				data->error = data->error + 3;
				return (0);
			}
			room_or_link(&data->room, (*str));
			links(data, &(data->room), (*str));
		}
		else
			comment(data, (*str));
		ft_strdel(str);
		get_next_line(0, str);
	}
	ft_strdel(str);
	return (1);
}

int		parcer(t_data *data, int index)
{
	char	*str;
	int		status;

	str = NULL;
	status = 1;
	while (get_next_line(0, &str) && status && !room_or_link(&data->room, str))
	{
		if (str && str[0] != '#')
			ft_putendl(str);
		if (str[0] == '#' && str[1] != '#')
			comment(data, str);
		else if ((!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end")) &&
			!start_end(data, str, &index))
			status = 0;
		else if (ft_strcmp(str, "##start") && ft_strcmp(str, "##end") &&
			(!check_valid(str) || !create_room(&(data->room), str, &index)))
			status = 0;
		ft_strdel(&str);
	}
	comment(data, str);
	// printf("========== status = %d\n", status);
	data->error = !status ? data->error + 2 : data->error;
	status ? creare_tabl(data, index) : 0;
	// printf("1111 %d\n", status);
	status = status ? parcer_links(data, &str) : 0;
	ft_strdel(&str);
	// int i = -1;
	// while (++i < data->count_room)
	// 	printf("|%s|\n", data->links[i]);
	if (data->end == NULL || data->start == NULL || str != NULL || !status)
		return (0);
	return (1);
}

void	bfs_start(t_data *data)
{
	t_room	**room;
	t_bfs	**bfs;

	room = &(data->room);
	bfs = &(data->bfs);
	while ((*room) && data->index_start != (*room)->index)
		room = &(*room)->next;
	(*room)->step = 0;
	(*bfs)->queue = (*room)->index;
	(*bfs)->next = NULL;
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

void	add_in_queue(t_bfs **b, t_room *room)
{
	t_bfs	**bfs;

	bfs = b;
	while ((*bfs))
		bfs = &(*bfs)->next;
	(*bfs) = (t_bfs *)malloc(sizeof(t_bfs));
	// printf("%p\n", (*bfs));
	// printf("%p\n", &(*bfs));
	(*bfs)->queue = room->index;
	(*bfs)->next = NULL;
}

void	add_step_and_delete_first(t_data *data)
{
	t_room	*room1;
	t_room	*room2;
	t_bfs	*bfs;
	t_bfs	*b;

	room1 = find_room(data, data->bfs->queue);
	bfs = data->bfs;
	while (bfs)
	{
		room2 = find_room(data, bfs->queue);
		if (room1->step < room2->step)
			room2->step = room1->step + 1;
		bfs = bfs->next;
	}
	bfs = data->bfs;
	b = bfs;
	bfs = bfs->next;
	free(b);
	data->bfs = bfs;
}

t_room	*find_neighbor(t_data *data, t_room *r, int step)
{
	t_room	*room;
	int		i;

	i = 0;
	while (data->links[r->index][i])
	{
		if (data->links[r->index][i] == '1')
		{
			room = find_room(data, i);
			if (room && room->step == step - 1)
				return (room);
		}
		i++;
	}
	return (NULL);
}

int		add_way(t_data *data, t_way **way, t_room *room)
{
	int		i;
	int		numb;
	int		step;

	i = 0;
	numb = -1;
	while ((*way) != NULL && --numb)
		(way) = &(*way)->next;
	(*way) = (t_way *)malloc(sizeof(t_way));
	// printf("%p\n", &(*way));
	// printf("%p\n", (*way));
	(*way)->next = NULL;
	(*way)->range = room->step + 1;
	(*way)->queue = (int *)malloc(sizeof(int) * ((*way)->range));
	// printf("%p\n", (*way)->queue);
	// printf("%p\n", &(*way)->queue);
	(*way)->queue[i] = room->index;
	step = room->step;
	room->step = data->count_room;
	while (++i < (*way)->range)
	{
		room = find_neighbor(data, room, step);
		room->step = numb;
		(*way)->queue[i] = room->index;
		step--;
	}
	if ((*way)->range == 2)
		return (0);
	return (1);
}

int		ft_bfs(t_data *data)
{
	t_room	*room;
	t_bfs	*bfs;
	int		index;

	bfs_start(data);
	while (data->bfs != NULL)
	{
		index = 0;
		bfs = data->bfs;
		while (index < data->count_room)
		{
			room = find_room(data, index);
			if (data->links[bfs->queue][index] == '1' &&
				room->step == data->count_room)
				add_in_queue(&bfs, find_room(data, index));
			index++;
		}
		add_step_and_delete_first(data);
	}
	room = find_room(data, data->index_end);
	if (room->step == data->count_room)
		return (0);
	return (add_way(data, &(data->way), room));
}

void	reset_bfs(t_data *data)
{
	t_room	*room;

	room = data->room;
	while (room)
	{
		if (room->step > 0)
			room->step = data->count_room;
		room = room->next;
	}
	data->bfs = (t_bfs *)malloc(sizeof(t_bfs));
	// printf("%p\n", &data->bfs);
	// printf("%p\n", data->bfs);
}

void	error(t_data *data)
{
	if (data->error && data->comment_error)
	{
		ft_printf("\033[91m%lc ", L'😱');
		ft_putstr("ERROR");
		ft_printf(" %lc\033[0m", L'😱');
		ft_putchar('\n');
		if (data->error == 1 && !data->comment_color)
			ft_putstr("Invalid number of ants\n");
		if (data->error == 2 && !data->comment_color)
			ft_putstr("Invalid room data\n");
		if (data->error == 3 && !data->comment_color)
			ft_putstr("Invalid connection data\n");
		if (data->error == 1 && data->comment_color)
			ft_printf("%lc Invalid number of ants %lc\n", L'🐜', L'🐜');
		if (data->error == 2 && data->comment_color)
			ft_printf("%lc Invalid room data %lc\n", L'🏠', L'🏠');
		if (data->error == 3 && data->comment_color)
			ft_printf("%lc Invalid connection data %lc\n", L'🏘', L'🏘');
		data->error = 0;
	}
}

void	residue(t_data *data)
{
	char	*str;

	str = NULL;
	while (get_next_line(0, &str))
	{
		printf("|%s|\n", str);
		comment(data, str);
		ft_strdel(&str);
	}
	error(data);
}

void	create_ants(t_data *data)
{
	t_room	*room;
	int		i;

	i = 0;
	data->ants = (char **)malloc(sizeof(char *) * (data->ants_count + 1));
	// printf("%p\n", &data->ants);
	// printf("%p\n", data->ants);
	data->ants[data->ants_count] = NULL;
	while (i < data->ants_count)
	{
		room = find_room(data, data->index_start);
		data->ants[i] = (room->name);
		// printf("|%s|\n", data->ants[i]);
		i++;
	}
	ft_putstr("\n");
}

void	move_ants(t_data *data, t_way *way, int i, int ant)
{
	t_room	*room1;
	t_room	*room2;

	room1 = find_room(data, way->queue[i]);
	room2 = find_room(data, way->queue[i - 1]);
	if (i > 0 && (!room2->ants || room2->index == data->index_end))
	{
		room1->ants--;
		room2->ants++;
		data->ants[ant - 1] = room2->name;
		if (data->comment_color && room1->index == data->index_start)
			ft_putstr("\033[92m");
		else if (data->comment_color && room2->index == data->index_end)
			ft_putstr("\033[91m");
		else if (data->comment_color)
			ft_putstr("\033[93m");
		ft_printf("L%d-%s ", ant, data->ants[ant - 1]);
		ft_putstr("\033[0m");
	}
}

void	transfer(t_data *data)
{
	t_room	*room;
	t_way	*way;
	int		i;
	int		ant;

	ant = 1;
	while (ant <= data->ants_count)
	{
		way = data->way;
		while (way)
		{
			i = 0;
			while (++i < way->range)
			{
				room = find_room(data, way->queue[i]);
				if (!ft_strcmp(room->name, data->ants[ant - 1]))
					move_ants(data, way, i, ant);
			}
			way = way->next;
		}
		ant++;
	}
	ft_putstr("\n");
}

int		check_queue(t_way **w1, t_way **w2)
{
	int		i;

	i = 0;
	while (i < (*w1)->range && i < (*w2)->range &&
		(*w1)->queue[i] == (*w2)->queue[i])
		i++;
	if (i == (*w1)->range && i == (*w2)->range)
		return (0);
	return (1);
}

void	check_way(t_data *data)
{
	t_way	**w1;
	t_way	**w2;
	t_way	**wr;

	w1 = &(data->way);
	wr = &(data->way);
	while ((*w1))
	{
		wr = &(*w1)->next;
		while ((*wr) && (*w2))
		{
			w2 = &(*wr)->next;
			if ((*w1)->range == (*w2)->range && check_queue(w1, w2))
			{
				(*wr)->next = (*w2)->next;
				free((*w1));
			}
			w2 = &(*w2)->next;
			wr = &(*wr)->next;
		}
		w1 = &(*w1)->next;
	}
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
	free(data->start);
	free(data->end);
	free(data);
}

int		main(void)
{
	t_data		*data;
	t_room		*room;

	data = (t_data *)malloc(sizeof(t_data));
	// printf("+%p\n", &data);
	// printf("+%p\n", data);
	data->room = (t_room *)malloc(sizeof(t_room));
	// printf("=%p\n", &data->room);
	// printf("=%p\n", data->room);
	data->bfs = (t_bfs *)malloc(sizeof(t_bfs));
	// printf("%p\n", &data->bfs);
	// printf("%p\n", data->bfs);
	// data->way = (t_way *)malloc(sizeof(t_way));
	reset(data);
	if (ants_count(data) && parcer(data, 0))
	{
		residue(data);
		while (ft_bfs(data))
			reset_bfs(data);
		// check_way(data);
		room = find_room(data, data->index_end);
		create_ants(data);
		while (data->way->range > 1 && room->ants < data->ants_count)
			transfer(data);
		// transfer(data);
		// transfer(data);
		// transfer(data);
		// printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ %d -> %d\n", room->ants, data->ants_count);
		// transfer(data);
		// transfer(data);
		// t_way *way;
		// t_room *room;
		// int i = 0;
		// way = data->way;
		// while (way)
		// {
		// 	i = 0;
		// 	while (i < way->range)
		// 	{
		// 		room = find_room(data, way->queue[i]);
		// 		printf("%s->", room->name);
		// 		i++;
		// 	}
		// 	printf("	range = %d\n", way->range);
		// 	way = way->next;
		// }
	}
	else
	{
		residue(data);
		printf("\033[91mERROR3\033[0m\n");
	}
	printf("error = %d\n", data->error);
	printf("comment_color = %d\n", data->comment_color);
	printf("comment_error = %d\n", data->comment_error);
	freesher(data);
	// free(data->way);
	// free(data);
	system("leaks lem_in");
	return (0);
}
