/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:47:52 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/17 18:55:18 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	error(t_data *data, int status)
{
	if (status == 0)
	{
		data->u_color ? ft_putstr("\033[91m") : 0;
		data->u_color ? ft_printf("%lc ", L'😱') : 0;
		ft_putstr("ERROR");
		data->u_color ? ft_printf(" %lc\033[0m\n", L'😱') : 0;
		!data->u_color ? ft_putstr("\n") : 0;
	}
	else if (status == 1)
	{
		data->u_color ? ft_putstr("\033[91m") : 0;
		data->u_color ? ft_printf("%lc ", L'🚷') : 0;
		ft_printf("No connection between start and end room");
		data->u_color ? ft_printf(" %lc\n", L'🚷') : 0;
		!data->u_color ? ft_putstr("\n") : 0;
	}
}

void	finish(t_data *data)
{
	data->u_paths ? u_path(data) : 0;
	if (data->u_color)
	{
		ft_printf("\033[95m\nCongratulations %lc ", L'🎊');
		ft_printf("\033[96mAll ants have reached their destination %lc", L'🐜');
		ft_printf("\033[94m Well done %lc\n", L'👍');
		if (data->u_moves)
		{
			ft_printf("\033[92mIt took \033[93m%d", data->moves);
			ft_printf(" \033[92mturns for the transfer %lc\n", L'👣');
		}
	}
	else
	{
		ft_printf("\nCongratulations! ");
		ft_printf("All ants have reached their destination.");
		ft_printf(" Well done %lc\n", L'✌');
		if (data->u_moves)
			ft_printf("It took %d turns for the transfer.\n", data->moves);
	}
	data->u_comment ? u_comment(data) : 0;
	ft_putstr("\033[0m");
}

int		comment(t_data *data, char *str)
{
	char	*tmp;

	if (!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end"))
		return (0);
	data->u_color ? ft_putstr("\033[94m") : 0;
	ft_putendl(str);
	if (data->u_comment)
	{
		if (data->comment == NULL)
			data->comment = ft_strdup(str);
		else
		{
			tmp = data->comment;
			data->comment = ft_strjoin(tmp, "\n");
			ft_strdel(&tmp);
			tmp = data->comment;
			data->comment = ft_strjoin(tmp, str);
			ft_strdel(&tmp);
		}
	}
	return (1);
}

int		usage(t_data *data, int ac, char **av)
{
	int		i;

	i = 0;
	u_reset(data);
	while (++i < ac)
	{
		if (!ft_strcmp("--color", av[i]))
			data->u_color = 1;
		else if (!ft_strcmp("--move", av[i]))
			data->u_moves = 1;
		else if (!ft_strcmp("--path", av[i]))
			data->u_paths = 1;
		else if (!ft_strcmp("--comment", av[i]))
			data->u_comment = 1;
		else if (!ft_strcmp("--time", av[i]))
			data->u_time = 1;
		else
		{
			u_error();
			return (0);
		}
	}
	return (1);
}
