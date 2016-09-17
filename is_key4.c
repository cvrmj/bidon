/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_key4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 16:55:44 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 16:55:59 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int	is_printable_char(char *buffer)
{
	if ((buffer[0] > 31 && buffer[0] < 127) && buffer[1] == 0)
	{
		return (1);
	}
	return (0);
}

int	is_shift_direction_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 49 && \
	buffer[3] == 59 && buffer[4] == 50 && (buffer[5] > 64 && buffer[5] < 69))
		return (1);
	return (0);
}

int	is_shift_up(char buffer5)
{
	if (buffer5 == 65)
		return (1);
	return (0);
}

int	is_shift_down(char buffer5)
{
	if (buffer5 == 66)
		return (1);
	return (0);
}

int	is_shift_right(char buffer5)
{
	if (buffer5 == 67)
		return (1);
	return (0);
}
