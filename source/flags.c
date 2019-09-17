/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 07:03:07 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/17 18:55:08 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	u_comment(t_data *data)
{
	if (data->comment)
	{
		data->u_color ? ft_putstr("\033[94m") : 0;
		ft_putstr("=======COMMENTS=======\n");
		data->u_color ? ft_putstr("\033[93m") : 0;
		ft_putendl(data->comment);
	}
}

void	u_path(t_data *data)
{
	t_way	*way;
	t_room	*room;
	int		i;

	way = data->way;
	ft_putstr("\n");
	data->u_color ? ft_putstr("\033[96m") : 0;
	while (way && data->count_way >= way->index)
	{
		i = way->range;
		while (--i >= 0)
		{
			room = find_room(data, way->queue[i]);
			ft_printf("[%s]", room->name);
			if (i > 0)
				ft_putstr("->");
		}
		way = way->next;
		ft_putstr("\n\n");
	}
}

void	u_time(t_data *data, clock_t start, clock_t end)
{
	float	time;

	if (data->u_time)
	{
		time = (float)(end - start) / CLOCKS_PER_SEC;
		data->u_color ? ft_putstr("\033[92mExecution time = \033[93m") :
			ft_putstr("Execution time = ");
		ft_printf("%.3f", time);
		data->u_color ? ft_putendl("\033[92m sec\033[0m") :
			ft_putendl(" sec");
	}
}

void	u_error(void)
{
	ft_putstr("\033[91m");
	ft_putstr("Invalid flags! Please, use next template.\n");
	ft_putstr("{ ./lem_in  ");
	ft_putstr("--color --move --path --comment --time ");
	ft_putstr("< [map path] }\n");
	ft_putstr("\033[0m");
}

void	u_reset(t_data *data)
{
	data->u_color = 0;
	data->u_moves = 0;
	data->u_paths = 0;
	data->u_comment = 0;
	data->u_time = 0;
}
