/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 15:59:46 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/06 16:00:00 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char			*get_history_i(int i)
{
	t_history	*history;
	int			j;

	j = 0;
	history = g_shell.history;
	while (j < i)
	{
		history = history->next;
		j++;
	}
	return (history->str);
}

int				check_syntax(char **command)
{
	if (command[1] != NULL &&
		(ft_strisdigit(command[1]) == -1 && command[1][0] != '-'))
	{
		ft_putendl("sh: history: illegal usage");
		return (1);
	}
	if ((command[1] != NULL && command[1][0] == '-') && (command[1][1] != 'c'
		&& command[1][1] != 'r' && command[1][1] != 'w' && command[1][1] != 'i'
		&& command[1][1] != 'd' && command[1][1] != 's'))
	{
		ft_putstr("sh: history: ");
		ft_putstr(command[1]);
		ft_putendl(": invalid option");
		return (1);
	}
	return (0);
}

int				ft_get_lenght_list(t_history *history)
{
	int			i;

	i = 0;
	while (history)
	{
		i++;
		history = history->next;
	}
	return (i);
}

int				ft_strisdigit(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

void			show_helper_history(void)
{
	ft_putendl("Syntax:");
	ft_putendl("        history");
	ft_putendl("        history [n]");
	ft_putendl("        history [-crw]");
	ft_putendl("        history -d offset");
	ft_putendl("        history -s arg");
}
