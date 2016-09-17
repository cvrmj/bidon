/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_key3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 16:55:29 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 16:55:37 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int	is_left_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_right_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_enter_key(char *buffer)
{
	if (buffer[0] == 10 && buffer[1] == 0)
		return (1);
	return (0);
}

int	is_home_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_end_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}
