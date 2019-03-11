/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ap.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 21:03:48 by akoropet          #+#    #+#             */
/*   Updated: 2019/02/27 20:51:04 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_type	g_type[TYPE_NUM] =
{
	{'s', &print_s},
	{'p', &print_p},
	{'d', &print_d},
	{'i', &print_i},
	{'o', &print_o},
	{'u', &print_u},
	{'x', &print_x},
	{'X', &print_big_x},
	{'c', &print_c},
	{'C', &print_big_c},
	{'f', &print_f},
};

t_flags	g_flags[5] =
{
	{0, 0, 0, 0, 0, 0, 0},
};
