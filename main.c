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
	if ((data->ants_count = ft_atoi(str)) <= 0 && ++data->error)
	{
		ft_strdel(&str);
		return (0);
	}
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
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (str[0] == '#' && str[1] == '#' && ft_strcmp(str, "##end") &&
		ft_strcmp(str, "##start") && ft_printf("%s\n", str))
		i = 0;
	if (i == 0 || str[0] == 'L' || str[0] == '#')
		return (0);
	i = str[++i] && (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	if (!str[i] || (str[i] && !ft_isdigit(str[i])))
		return (0);
	while (str[i] && str[i] != ' ' && ft_isdigit(str[i]))
		i++;
	if (!str[i++])
		return (0);
	i = str[i] && (str[i] == '-' || str[i] == '+') ? i + 1 : i;
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
		// printf("%p\n", &str);
		// printf("%p\n", data->start);
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
	if (comment(data, str))
		return (1);
	ft_putendl(str);
	if (get_next_line(0, &tmp))
		ft_putendl(tmp);
	if (tmp && check_valid(tmp) && create_room(&(data->room), tmp, index))
	{
		if ((!ft_strcmp(str, "##start") && data->start == NULL) ||
			(!ft_strcmp(str, "##end") && data->end == NULL))
		{
			add_start_end(data, str, tmp, index);
			ft_strdel(&tmp);
			return (1);
		}
		// add_start_end(data, str, tmp, index);
		// ft_strdel(&tmp);
		// return (1);
	}
	ft_strdel(&tmp);
	ft_strdel(&data->end);
	ft_strdel(&data->start);
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

int		comment(t_data *data, char *str)
{
	if (str && !ft_strcmp("#color", str))
	{
		data->comment_color = 1;
		return (1);
	}
	if (str && !ft_strcmp("#error", str))
	{
		data->comment_error = 1;
		return (1);
	}
	if (str && !ft_strcmp("#moves", str))
	{
		data->comment_moves = 1;
		return (1);
	}
	return (0);
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

int		hashtag(t_data *data, char *str)
{
	int		i;

	i = 0;
	if (!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end"))
		return (1);
	if (comment(data, str))
		return (1);
	while (!ft_isalpha(str[i]))
		i++;
	if (!ft_strcmp("end", str + i) || !ft_strcmp("start", str + i))
	{
		ft_putendl(str);
		return (0);
	}
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
		if (str[0] == '#')
			status = hashtag(data, str);
		// if (str[0] == '#' && str[1] != '#')
		// 	comment(data, str);
		if (status && (!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end"))
			&& !comment(data, str) && !start_end(data, str, &index))
			status = 0;
		if (status && ft_strcmp(str, "##start") && ft_strcmp(str, "##end") &&
			!comment(data, str) && (!check_valid(str) ||
				!create_room(&(data->room), str, &index)))
			status = 0;
		ft_strdel(&str);
	}
	// printf("status = %d\n", status);
	comment(data, str);
	// printf("1111\n");
	data->error = !status || !str ? data->error + 2 : data->error;
	status && str ? creare_tabl(data, index) : 0;
	status = status && str ? parcer_links(data, &str) : 0;
	ft_strdel(&str);
	// if (data->end == NULL || data->start == NULL || str != NULL || !status)
	// 	return (0);
	return (data->end != NULL && data->start != NULL && str == NULL && status);
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

void	color(t_data *data)
{
	if (data->error == 1 && data->comment_color)
	{
		ft_printf("%lc \033[96m Reason %lc\033[95m ", L'🐜', L'👉');
		ft_printf("Invalid number of ants %lc\n", L'🐜');
	}
	if (data->error == 2 && data->comment_color)
	{
		ft_printf("%lc \033[96m Reason %lc\033[95m ", L'🏠', L'👉');
		ft_printf("Invalid room data %lc\n", L'🏠');
	}
	if (data->error == 3 && data->comment_color)
	{
		ft_printf("\033[96m%lc  Reason %lc\033[95m ", L'🏘', L'👉');
		ft_printf("Invalid connection data %lc\n", L'🏘');
	}
	if (data->error == 4 && data->comment_color)
	{
		ft_printf("\033[96m%lc  Reason %lc\033[95m ", L'🚷', L'👉');
		ft_printf("Invalid way %lc\n", L'🚷');
	}
	ft_putstr("\033[0m");
}

void	error(t_data *data)
{
	if (data->error)
	{
		data->comment_color ? ft_putstr("\033[91m") : 0;
		data->comment_color ? ft_printf("%lc", L'😱') :
			ft_printf("%lc", L'⏏');
		ft_putstr(" ERROR ");
		data->comment_color ? ft_printf("%lc\n", L'😱') :
			ft_printf("%lc\n", L'⏏');
		if (!data->comment_color && data->comment_error)
		{
			if (data->error == 1)
				ft_printf("Reason %lc Invalid number of ants\n", L'☛');
			if (data->error == 2)
				ft_printf("Reason %lc Invalid room data\n", L'☛');
			if (data->error == 3)
				ft_printf("Reason %lc Invalid connection data\n", L'☛');
			if (data->error == 4)
				ft_printf("Reason %lc Invalid way\n", L'☛');
		}
		if (data->comment_color && data->comment_error)
			color(data);
		data->error = 0;
		ft_putstr("\033[0m");
	}
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

t_room	*create_ants(t_data *data)
{
	t_room	*room;
	long long int		i;

	i = 0;
	// printf("%lld\n", data->ants_count);
	data->ants = (char **)malloc(sizeof(char *) * (data->ants_count));
	// printf("%p\n", &data->ants);
	// printf("%p\n", data->ants);
	data->ants[data->ants_count] = NULL;
	// printf("3333\n");
	while (i < data->ants_count)
	{
		room = find_room(data, data->index_start);
		data->ants[i] = (room->name);
		// printf("|%s|\n", data->ants[i]);
		i++;
	}
	// printf("33333\n");
	ft_putstr("\n");
	return (find_room(data, data->index_end));
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

void	finish(t_data *data)
{
	if (data->comment_color)
	{
		ft_printf("\033[96m\nCongratulations %lc ", L'🎊');
		ft_printf("\033[95mAll ants have reached their destination %lc", L'🐜');
		ft_printf("\033[94m Well done %lc\n", L'👍');
		if (data->comment_moves)
		{
			ft_printf("\033[92mIt took \033[93m%d", data->moves);
			ft_printf(" \033[92mturns for the transfer %lc\n", L'👣');
		}
	}
	else
	{
		ft_printf("\nCongratulations! ");
		ft_printf("All ants have reached their destination.");
		ft_printf(" Well done %lc\n", L'✌');
		if (data->comment_moves)
			ft_printf("It took %d turns for the transfer.\n", data->moves);
	}
	ft_putstr("\033[0m");
}

// it took 6 turns for the transfer
// 👣

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
	data->moves++;
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
	// printf("_%p\n", data->start);
	free(data->start);
	free(data->end);
	// free(data);
}

int		main(void)
{
	t_data		*data;
	t_room		*room;

	data = (t_data *)malloc(sizeof(t_data));
	data->room = (t_room *)malloc(sizeof(t_room));
	data->bfs = (t_bfs *)malloc(sizeof(t_bfs));
	reset(data);
	if (ants_count(data) && parcer(data, 0))
	{
		// printf("1111111\n");
		residue(data);
		while (ft_bfs(data))
			reset_bfs(data);
		room = create_ants(data);
		while (data->way && data->way->range > 1 &&
			room->ants < data->ants_count && data->start)
			transfer(data);
		data->error = (data->way && data->way->range <= 1) ||
			!data->way ? 4 : data->error;
		(data->way && data->way->range <= 1) || !data->way ?
			error(data) : finish(data);
	}
	else
	{
		// printf("222222\n");
		// printf("error = %d\n", data->error);
		residue(data);
	}
	freesher(data);
	// system("leaks lem_in");
	return (0);
}
