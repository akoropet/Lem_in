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

void	reset(t_data *data, t_room *room)
{
	room->next = NULL;
	room->name = NULL;
	room->index = 0;
	room->ants = 0;
	room->coord_x = 0;
	room->coord_y = 0;
	data->ants_count = 0;
	data->start = NULL;
	data->end = NULL;
}

int		ants_count(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (get_next_line(0, &str) <= 0)
		return (0);
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
	int		i;
	int		x;
	int		y;
	t_room	**room;

	room = r;
	i = 0;
	x = ft_atoi(ft_strchr(str, ' '));
	y = ft_atoi(ft_strchr((ft_strchr(str, ' ') + 1), ' '));
	printf("->%s - %d - %d\n", str, x, y);
	printf("index = %d\n", (*index));
	while ((*index) > 0 && (*room) && ((*room)->coord_x != x ||
		(*room)->coord_y != y))
	{
		printf("-->%s - %d\n", (*room)->name, (*room)->index);
		room = &(*room)->next;
	}
	if ((*index) > 0 && (*room))
		return (0);
	*room = (t_room *)malloc(sizeof(t_room));
	(*room)->name = ft_strndup(str, ' ');
	printf(">%s<\n", str);
	(*room)->next = NULL;
	(*room)->coord_x = x;
	(*room)->coord_y = y;
	(*room)->index = (*index);
	(*room)->ants = 0;
	(*index)++;
	return (1);
}

int		check_valid(char *str)
{
	int		i;

	i = 0;
	printf("check_valid - %s\n", str);
	while (str[i] && str[i] != ' ')
		i++;
	i = str[++i] && (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	if (!str[i] || (str[i] && !ft_isdigit(str[i])))
		return (0);
	while (str[i] && str[i] != ' ' && ft_isdigit(str[i]))
		i++;
	i = str[++i] && (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	printf("|%s| - %d\n", str, i);
	if (!str[i] || (str[i] && !ft_isdigit(str[i])))
		return (0);
	printf("11111\n");
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int		start_end(t_data **data, t_room *room, char *str, int *index)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	printf("?%s?\n", str);
	if (get_next_line(0, &tmp) && check_valid(tmp) &&
		create_room(&room, tmp, index))
	{
		printf("!%s!\n", tmp);
		if ((!ft_strcmp(str, "##start") && (*data)->start != NULL) ||
			(!ft_strcmp(str, "##end") && (*data)->end != NULL))
		{
			(*data)->end = NULL;
			(*data)->start = NULL;
			return (0); 
		}
		if ((!ft_strcmp(str, "##start")))
			(*data)->start = ft_strndup(tmp, ' ');
		if ((!ft_strcmp(str, "##end")))
			(*data)->end = ft_strndup(tmp, ' ');
		printf("%s!\n", tmp);
		ft_strdel(&tmp);
		return (1);
	}
	(*data)->end = NULL;
	(*data)->start = NULL;
	return (0);
}

int		parcer(t_data *data, t_room *room)
{
	char	*str;
	int		index;
	int		n;

	str = NULL;
	index = 0;
	if (!ants_count(data))
		return (0);
	while (get_next_line(0, &str))
	{
		printf("      |%s|\n", str);
		if ((!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end")) &&
			!start_end(&data, room, str, &index))
			break ;
		else if (!check_valid(str) || !create_room(&room, str, &index))
			break ;
		printf("   ??%s??\n", str);
		ft_strdel(&str);
	}
	ft_strdel(&str);
	printf("start = %s, end = %s\n", data->start, data->end);
	if (data->end != NULL && data->start != NULL)
		return (1);
	return (0);
}

int		main(void)
{
	t_data		*data;
	t_room		*room;

	room = (t_room *)malloc(sizeof(t_room));
	data = (t_data *)malloc(sizeof(t_data));
	reset(data, room);
	if (!parcer(data, room))
		printf("\033[91mERROR\033[0m\n");
	else
		printf("\033[92mHAKEY\033[0m\n");
	return (0);
}
