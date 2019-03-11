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
	int				*links;
	int				index;
	int				ants;
	int				coord_x;
	int				coord_y;
	struct s_room	*next;
}					t_room;

typedef struct		s_data
{
	int				ants_count;
	char			*start;
	char			*end;
}					t_data;

#endif
