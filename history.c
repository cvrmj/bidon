/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:03:52 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/05 18:40:50 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			sub_del_offset(int offset)
{
	t_history	*history;
	t_history	*tmp;
	int			i;

	i = 0;
	history = g_shell.history;
	while (history != NULL && i < offset)
	{
		tmp = history->next;
		if (history->str)
			ft_strdel(&history->str);
		free(history);
		history = tmp;
		i++;
	}
	g_shell.history = history;
	if (history == NULL)
	{
		free(history);
		g_shell.history = malloc(sizeof(*(g_shell.history)));
		g_shell.history->str = NULL;
		g_shell.history->next = NULL;
		g_shell.history->prev = NULL;
	}
}

void			dell_history_offset(t_data *data, char *offset)
{
	int			real_offset;

	if (offset != NULL)
	{
		real_offset = ft_atoi(offset);
		if (ft_strisdigit(offset) != 0 ||
			real_offset >= ft_get_lenght_list(g_shell.history))
		{
			ft_putstr("sh: history: ");
			ft_putstr(offset);
			ft_putendl(": history position out of range");
			data->binreturn = 255;
			return ;
		}
		sub_del_offset(real_offset);
	}
	else if (offset == NULL)
	{
		ft_putendl("sh: history: -d: option requires an argument");
		show_helper_history();
		data->binreturn = 255;
		return ;
	}
}

void			switch_option_2(t_data *data, char *str)
{
	if (str[1] == 'r')
	{
		if (append_to_list() == -1)
		{
			ft_putendl("sh: history: no history source file");
			data->binreturn = 255;
		}
	}
	if (str[1] == 'w')
		append_to_file();
	if (str[1] == 's')
		add_arg_to_history(data);
}

void			switch_option(t_data *data, char *str)
{
	int i;

	i = 0;
	if (ft_strcmp(str, "--help") == 0)
		show_helper_history();
	else if (str[2])
	{
		ft_putendl("sh: history: cannot use more than one option");
		show_helper_history();
		data->binreturn = 255;
		return ;
	}
	else if (str[1] == 'c')
		dell_history();
	else if (str[1] == 'd')
		dell_history_offset(data, data->args[2]);
	else if (str[1] == 'i')
	{
		if (data->args[2] == NULL)
			show_history_rev();
		else if (ft_strisdigit(data->args[2]) != -1)
			show_history_rev_until(data->args[2]);
	}
	else
		switch_option_2(data, str);
}

void			history(t_data *data)
{
	int			len;

	len = ft_strlentab(data->args);
	if (check_syntax(data->args) == 1)
	{
		show_helper_history();
		data->binreturn = 255;
		return ;
	}
	if (data->args[1] == NULL)
		show_history();
	else if (data->args[1][0] == '-')
		switch_option(data, data->args[1]);
	else if (data->args[1] && ft_strisdigit(data->args[1]) != -1)
		show_history_until(data->args[1]);
}
