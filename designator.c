/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 13:31:53 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/05 13:32:06 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		*create_command(char *command, char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		command = ft_strcat(command, " ");
		command = ft_strcat(command, args[i]);
		i++;
	}
	return (command);
}

void		design_to_index_rev(t_data *data, int index)
{
	t_history	*history;
	int			i;
	int			len;

	i = g_shell.history_index;
	history = g_shell.history;
	len = i - index;
	while (history->next)
		history = history->next;
	while (history && i > len)
	{
		i--;
		history = history->prev;
	}
	if (i > len)
	{
		ft_putstr("sh: ");
		ft_putstr(data->args[0]);
		ft_putendl(": event not found");
		data->binreturn = 255;
		return ;
	}
	ft_putendl(history->str);
	readgnl(data, create_command(history->str, data->args), 1);
}

void		design_to_index(t_data *data, int index)
{
	t_history	*history;
	int			i;

	i = 1;
	history = g_shell.history;
	while (i < index && history)
	{
		i++;
		history = history->next;
	}
	if (i < index)
	{
		ft_putstr("sh: ");
		ft_putstr(data->args[0]);
		ft_putendl(": event not found");
		data->binreturn = 255;
		return ;
	}
	ft_putendl(history->str);
	readgnl(data, create_command(history->str, data->args), 1);
}

int			check_syntax_designator(t_data *data)
{
	if (data->args[0][0] == '!')
	{
		if (data->args[0][1] == '!' && data->args[0][2])
			return (-1);
		if (data->args[0][1] && data->args[0][1] != ' ')
			return (0);
	}
	return (-1);
}

void		designator(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_isdigit(data->args[0][1]) ||
		(data->args[0][1] == '-' && ft_isdigit(data->args[0][2])))
	{
		tmp = data->args[0];
		if (ft_strisdigit(++tmp) == 0)
			design_to_index(data, ft_atoi(tmp));
		else if (ft_strisdigit(++tmp) == 0)
			design_to_index_rev(data, ft_atoi(tmp));
	}
	else if (ft_strcmp(data->args[0], "!!") == 0)
		design_to_index_rev(data, 1);
	else if (data->args[0][1] == '?')
		design_to_string(data, data->args[0], 0);
	else
		design_to_start_string(data, data->args[0], 0);
}
