/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:58:27 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/17 18:54:38 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lib/libft/libft.h"
# include <time.h>

typedef struct		s_room
{
	char			*name;
	int				index;
	int				reserv;
	int				status;
	int				ants;
	int				step;
	int				coord_x;
	int				coord_y;
	struct s_room	*next;
}					t_room;

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
	int				u_comment;
	int				u_time;
	int				count_way;
	int				count_room;
	int				ants_count;
	int				index_start;
	int				index_end;
	int				moves;
	char			**links;
	char			**ants;
	char			**locat;
	char			*output;
	char			*comment;
	char			*start;
	char			*end;
	struct s_room	*room;
	struct s_way	*way;
}					t_data;

int					links(t_data *data, t_room **r, char *str);
void				add_links(t_room **room1, t_room **room2, t_data *data,
	char **link);
void				creare_tabl(t_data *data, int index);
int					room_or_link(t_room *room, char *str);

int					check_valid(t_data *data, char *str, int i);
int					parcer_links(t_data *data, char **str);
int					valid_links(t_data *data, char **str);
int					ants_count(t_data *data);
int					parcer(t_data *data, int index);

void				reset_room(t_room **room, char *name, int x, int y);
int					create_room(t_room **r, char *str, int *index);
void				add_start_end(t_data *data, char *str, char *tmp,
	int *index);
t_room				*find_room(t_data *data, int index);
int					start_end(t_data *data, char *str, int *index);

t_room				*find_wave(t_data *data, int step);
void				wave(t_data *data, t_room *room, int step, int i);
int					one_way(t_data *data);
void				ft_clear(t_data *data);
t_room				*find_neig(t_data *data, t_room *room, int step);

int					ft_go(t_data *data, t_way *w, int i);
int					move_ants(t_data *data, t_way *way, int i, int ant);
int					transfer(t_data *data, int ant);
int					ft_algorithm(t_data *data, int status);

void				error(t_data *data, int status);
void				finish(t_data *data);
int					comment(t_data *data, char *str);
int					usage(t_data *data, int ac, char **av);

void				u_comment(t_data *data);
void				u_path(t_data *data);
void				u_time(t_data *data, clock_t start, clock_t end);
void				u_error(void);
void				u_reset(t_data *data);

int					normal_way(t_data *data, t_way *w);
void				clear_way(t_data *data);
t_room				*create_ants(t_data *data);
int					add_way(t_data *data);
t_room				*create_way(t_data *data, t_way **way, t_room *room);

void				reset(t_data *data);

#endif
