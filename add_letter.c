/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_letter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 15:59:27 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/03 16:01:42 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		ft_strlend(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	delete_last_backslash(void)
{
	g_shell.shell_line = del_from_arr(g_shell.shell_line, g_shell.length_line);
}

int		get_history_length(void)
{
	t_history	*history;
	int			i;

	history = g_shell.history;
	if (history->str)
		i = 1;
	else
		i = 0;
	while (history->next)
	{
		history = history->next;
		i++;
	}
	return (i);
}
