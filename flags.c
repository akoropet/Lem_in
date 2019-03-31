/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 07:03:07 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 07:29:08 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_comment(t_data *data)
{
	if (data->comment)
	{
		data->u_color ? ft_putstr("\033[94m") : 0;
		ft_putstr("=======COMMENTS=======\n");
		data->u_color ? ft_putstr("\033[93m") : 0;
		ft_putendl(data->comment);
	}
}

void	ft_path(t_data *data)
{
	t_way	*way;
	t_room	*room;
	int		i;

	way = data->way;
	ft_putstr("\n");
	data->u_color ? ft_putstr("\033[96m") : 0;
	while (way)
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