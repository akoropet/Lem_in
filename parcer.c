/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:28:37 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 06:31:14 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_valid(t_data *data, char *str, int i)
{
	data->u_color ? ft_putstr("\033[95m") : 0;
	ft_putendl(str);
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

int		parcer_links(t_data *data, char **str)
{
	data->u_color ? ft_putstr("\033[96m") : 0;
	while ((*str))
	{
		// ft_putstr("\033[91m");
		ft_putendl((*str));
		// ft_putstr("\033[0m");
		if (!valid_links(data, str))
			return (0);
		// room_or_link(&data->room, (*str));
		links(data, &(data->room), (*str));
		ft_strdel(str);
		get_next_line(0, str);
	}
	ft_strdel(str);
	return (1);
}

int		valid_links(t_data *data, char **str)
{
	t_room	*room;
	char	*name;
	int		i;

	i = 0;
	while ((*str)[i] && ft_isprint((*str)[i]))
		i++;
	if ((*str)[i])
		return (0);
	room = data->room;
	if (!(name = ft_strndup((*str), '-')))
		return (0);
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	ft_strdel(&name);
	if (!room || !ft_strchr((*str), '-'))
		return (0);
	room = data->room;
	if (!(name = ft_strchr((*str), '-') + 1))
		return (0);
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	return (room != NULL);
}

int		ants_count(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (get_next_line(0, &str) <= 0)
		return (0);
	data->u_color ? ft_putstr("\033[93m") : 0;
	ft_putendl(str);
	if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
	{
		ft_strdel(&str);
		return (0);
	}
	if ((data->ants_count = ft_atoi(str)) <= 0)
	{
		ft_strdel(&str);
		return (0);
	}
	ft_strdel(&str);
	return (1);
}

int		parcer(t_data *data, int index)
{
	char	*str;
	int		status;

	str = NULL;
	status = 1;
	while (get_next_line(0, &str) > 0 && status &&
		!room_or_link(&data->room, str))
	{
		// ft_putendl(str);
		if (str[0] == '#' && ft_strcmp(str, "##start") &&
			ft_strcmp(str, "##end"))
			comment(data, str);
		else if (status && (!ft_strcmp(str, "##start") ||
			!ft_strcmp(str, "##end")) && !start_end(data, str, &index))
			status = 0;
		else if (status && ft_strcmp(str, "##start") && ft_strcmp(str, "##end")
			&& (!check_valid(data, str, 0) || !create_room(&(data->room), str, &index)))
			status = 0;
		ft_strdel(&str);
	}
	status && str ? creare_tabl(data, index) : 0;
	status = status && str ? parcer_links(data, &str) : 0;
	ft_strdel(&str);
	// printf("%s %s %s %d\n", data->end, data->start, str, status);
	// if (data->end == NULL || data->start == NULL || str != NULL || !status)
	// 	return (0);
	return (data->end != NULL && data->start != NULL && str == NULL);
}
