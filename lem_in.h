/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:58:27 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/09 19:23:40 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "./lib/libft/libft.h"
#include <stdio.h>

typedef struct		s_room
{
	char			*name;
	int				index;
	// int				number_ant;
	int				ants;
	int				step;
	int				coord_x;
	int				coord_y;
	struct s_room	*next;
}					t_room;

typedef struct		s_bfs
{
	int				queue;
	struct s_bfs	*next;
}					t_bfs;

typedef struct		s_way
{
	int				*queue;
	int				range;
	struct s_way	*next;
}					t_way;

typedef struct		s_data
{
	char			**links;
	char			**ants;
	int				count_room;
	long long int				ants_count;
	int				index_start;
	int				index_end;
	int				comment_color;
	int				comment_error;
	int				error;
	char			*start;
	char			*end;
	struct s_room	*room;
	struct s_bfs	*bfs;
	struct s_way	*way;
}					t_data;

t_room	*find_room(t_data *data, int index);

#endif

