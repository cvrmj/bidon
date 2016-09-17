/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_key5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 16:57:20 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 13:02:05 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int	is_shift_left(char buffer5)
{
	if (buffer5 == 68)
		return (1);
	return (0);
}

int	is_option_c(char *buffer)
{
	if (buffer[0] == -61 && buffer[1] == -89 && buffer[2] == 0)
		return (1);
	return (0);
}

int	is_ctrl_d(char *buffer)
{
	if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0 && buffer[3] == 0)
		return (1);
	return (0);
}

int	is_tab(char *buffer)
{
	if (buffer[0] == 9 && buffer[1] == 0 && buffer[2] == 0 && buffer[3] == 0)
		return (1);
	return (0);
}
