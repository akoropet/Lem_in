/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 22:04:01 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/17 18:55:13 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

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

int		main(int ac, char **av)
{
	t_data		*data;
	int			status;
	clock_t		start;
	clock_t		end;

	status = 0;
	start = clock();
	data = (t_data *)malloc(sizeof(t_data));
	data->room = (t_room *)malloc(sizeof(t_room));
	if (!usage(data, ac, av))
		return (0);
	reset(data);
	while (ants_count(data) && parcer(data, 0))
	{
		status = ft_algorithm(data, status);
		if (status == 1)
			break ;
		finish(data);
		status = 2;
		break ;
	}
	error(data, status);
	end = clock();
	u_time(data, start, end);
	return (0);
}
