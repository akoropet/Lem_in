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
}

int		ants_count(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (get_next_line(0, &str) <= 0)
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
	{
		ft_strdel(&str);
		return (0);
	}
	if ((data->ants_count = ft_atoi(str)) == 0)
		return (0);
	ft_strdel(&str);
	return (1);
}

int		create_room(t_room **r, char *str, int *index)
{
	int		x;
	int		y;
	char	*name;
	t_room	**room;

	printf("\ncreate_room start|%s|\n", str);
	room = r;
	x = ft_atoi(ft_strchr(str, ' '));
	y = ft_atoi(ft_strchr((ft_strchr(str, ' ') + 1), ' '));
	name = ft_strndup(str, ' ');
	while ((*index) > 0 && (*room) && ((*room)->coord_x != x ||
		(*room)->coord_y != y) && ft_strcmp((*room)->name, name))
	{
		printf("	room->%s - %d\n", (*room)->name, (*room)->index);
		room = &(*room)->next;
	}
	if (((*index) > 0 && (*room)))
		return (0);
	*room = (t_room *)malloc(sizeof(t_room));
	(*room)->name = name;
	(*room)->next = NULL;
	(*room)->coord_x = x;
	(*room)->coord_y = y;
	(*room)->index = (*index);
	printf("	new_room->%s, index = %d\n", (*room)->name, (*room)->index);
	(*room)->ants = 0;
	(*index)++;
	printf("create_room end\n");
	return (1);
}

int		check_valid(char *str)
{
	int		i;

	i = 0;
	printf("\ncheck_valid start->|%s|\n", str);
	while (str[i] && str[i] != ' ')
		i++;
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
	if ((!ft_strcmp(str, "##start")))
	{
		data->start = ft_strndup(tmp, ' ');
		data->index_start = (*index) - 1;
		// data->index_start = data->index_start - 1;
		printf("\nindex_start = %d\n\n", data->index_start);
	}
	if ((!ft_strcmp(str, "##end")))
	{
		data->end = ft_strndup(tmp, ' ');
		data->index_end = (*index) - 1;
		printf("\nindex_end = %d\n\n", data->index_end);
	}
}

int		start_end(t_data *data, char *str, int *index)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	printf("\n'start_end' start->|%s|\n", str);
	if (get_next_line(0, &tmp) && check_valid(tmp) &&
		create_room(&(data->room), tmp, index))
	{
		printf("	tmp = |%s|\n", tmp);
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
		room = r;
		room_name = ft_strndup(str, '-');
		while ((*room))
		{
			if (!ft_strcmp((*room)->name, room_name))
				return (1);
			room = &(*room)->next;
		}
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
	return (0);
}

void	parcer_links(t_data *data, char **str)
{
	while ((*str))
	{
		if ((*str)[0] == '#' && (*str)[1] == '#')
			break ;
		else if ((*str)[0] != '#')
		{
			room_or_link(&data->room, (*str));
			links(data, &(data->room), (*str));
		}
		ft_strdel(str);
		get_next_line(0, str);
	}
	ft_strdel(str);
}

int		parcer(t_data *data)
{
	char	*str;
	int		index;

	str = NULL;
	index = 0;
	while (get_next_line(0, &str) && !room_or_link(&data->room, str))
	{
		if (str[0] == '#' && str[1] != '#')
			continue ;
		else if ((!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end")) &&
			!start_end(data, str, &index))
			break ;
		else if (ft_strcmp(str, "##start") && ft_strcmp(str, "##end") &&
			(!check_valid(str) || !create_room(&(data->room), str, &index)))
			break ;
		ft_strdel(&str);
	}
	creare_tabl(data, index);
	parcer_links(data, &str);
	int i = -1;
	while (++i < data->count_room)
		printf("|%s|\n", data->links[i]);
	if (data->end == NULL || data->start == NULL || str != NULL)
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
	bfs = bfs->next == NULL ? NULL : bfs->next;
	free(b);
	data->bfs = bfs;
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
	room = data->room;
	while (room)
	{
		printf("room = %s, step = %d\n", room->name, room->step);
		room = room->next;
	}
	printf("===============================================\n");
	room = find_room(data, data->index_end);
	if (room->step == data->count_room)
		return (0);
	return (1);
}

int		main(void)
{
	t_data		*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->room = (t_room *)malloc(sizeof(t_room));
	data->bfs = (t_bfs *)malloc(sizeof(t_bfs));
	reset(data);
	if (ants_count(data))
	{
		if (!parcer(data))
			printf("\033[91mERROR1\033[0m\n");
		else
		{
			if (!ft_bfs(data))
				printf("\033[91mERROR2\033[0m\n");
			else
				printf("\033[92mHAKEY\033[0m\n");
		}
	}
	else
		printf("\033[91mERROR3\033[0m\n");
	return (0);
}
