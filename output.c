/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:47:52 by akoropet          #+#    #+#             */
/*   Updated: 2019/03/31 06:44:44 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// void	color(t_data *data)
// {
// 	if (data->error == 1 && data->comment_color)
// 	{
// 		ft_printf("%lc \033[96m Reason %lc\033[95m ", L'🐜', L'👉');
// 		ft_printf("Invalid number of ants %lc\n", L'🐜');
// 	}
// 	if (data->error == 2 && data->comment_color)
// 	{
// 		ft_printf("%lc \033[96m Reason %lc\033[95m ", L'🏠', L'👉');
// 		ft_printf("Invalid room data %lc\n", L'🏠');
// 	}
// 	if (data->error == 3 && data->comment_color)
// 	{
// 		ft_printf("\033[96m%lc  Reason %lc\033[95m ", L'🏘', L'👉');
// 		ft_printf("Invalid connection data %lc\n", L'🏘');
// 	}
// 	if (data->error == 4 && data->comment_color)
// 	{
// 		ft_printf("\033[96m%lc  Reason %lc\033[95m ", L'🚷', L'👉');
// 		ft_printf("Invalid way %lc\n", L'🚷');
// 	}
// 	ft_putstr("\033[0m");
// }

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
		// if (!data->comment_color && data->comment_error)
		// {
		// 	if (data->error == 1)
		// 		ft_printf("Reason %lc Invalid number of ants\n", L'☛');
		// 	if (data->error == 2)
		// 		ft_printf("Reason %lc Invalid room data\n", L'☛');
		// 	if (data->error == 3)
		// 		ft_printf("Reason %lc Invalid connection data\n", L'☛');
		// 	if (data->error == 4)
		// 		ft_printf("Reason %lc Invalid way\n", L'☛');
		// }
		// if (data->comment_color && data->comment_error)
		// 	color(data);
		// data->error = 0;
		// ft_putstr("\033[0m");
}

void	finish(t_data *data)
{
	if (data->u_color)
	{
		ft_printf("\033[96m\nCongratulations %lc ", L'🎊');
		ft_printf("\033[95mAll ants have reached their destination %lc", L'🐜');
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

int		hashtag(t_data *data, char *str)
{
	int		i;

	i = 0;
	if (!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end"))
		return (1);
	if (comment(data, str))
		return (1);
	while (!ft_isalpha(str[i]))
		i++;
	if (!ft_strcmp("end", str + i) || !ft_strcmp("start", str + i))
	{
		ft_putendl(str);
		return (0);
	}
	return (1);
}
