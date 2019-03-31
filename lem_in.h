/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:58:27 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 06:35:54 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "./lib/libft/libft.h"
# include <time.h>
#include <stdio.h>

typedef struct		s_room
{
	char			*name;
	int				index;
	// int				number_ant;
	int				reserv;
	int				status;
	int				ants;
	int				step;
	int				coord_x;
	int				coord_y;
	struct s_room	*next;
}					t_room;

// typedef struct		s_bfs
// {
// 	int				queue;
// 	struct s_bfs	*next;
// }					t_bfs;

typedef struct		s_way
{
	int				*queue;
	int				range;
	int				index;
	struct s_way	*next;
}					t_way;

typedef struct		s_data
{
	int				u_color;
	int				u_moves;
	int				u_paths;
	int				u_leaks;
	int				u_comment;
	int				u_time;
	char			**links;
	char			**ants;
	char			**locat;
	char			*output;
	char			*comment;
	int				count_way;
	int				count_room;
	int				ants_count;
	int				index_start;
	int				index_end;
	int				moves;
	char			*start;
	char			*end;
	struct s_room	*room;
	// struct s_bfs	*bfs;
	struct s_way	*way;
}					t_data;

int		check_valid(t_data *data, char *str, int i);
int		parcer(t_data *data, int index);
int		parcer_links(t_data *data, char **str);
int		valid_links(t_data *data, char **str);
int		ants_count(t_data *data);

int		create_room(t_room **r, char *str, int *index);
void	add_start_end(t_data *data, char *str, char *tmp, int *index);
int		start_end(t_data *data, char *str, int *index);
void	reset_room(t_room **room, char *name, int x, int y);
t_room	*find_room(t_data *data, int index);

// int		ft_bfs(t_data *data, t_room *room, int step);
t_room	*find_wave(t_data *data, int step);
void	wave(t_data *data, t_room *room, int step);
int		add_way(t_data *data);
// int		ft_bfs(t_data *data);
// void	bfs_start(t_data *data);
// void	add_step_and_delete_first(t_data *data);
// void	add_in_queue(t_bfs **b, t_room *room);
// void	reset_bfs(t_data *data);

int		links(t_data *data, t_room **r, char *str);
void	add_links(t_room **room1, t_room **room2, t_data *data, char **link);
void	creare_tabl(t_data *data, int index);
int		room_or_link(t_room **r, char *str);

// int		add_way(t_data *data, t_way **way, t_room *room);
// t_room	*find_neighbor(t_data *data, t_room *r, int step);
t_room	*create_ants(t_data *data);

// void	color(t_data *data);
void	error(t_data *data, int status);
void	finish(t_data *data);
int		comment(t_data *data, char *str);
int		hashtag(t_data *data, char *str);

int		move_ants(t_data *data, t_way *way, int i, int ant);
int		transfer(t_data *data, int ant);

void	reset(t_data *data);

#endif

