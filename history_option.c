/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 16:02:03 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/06 16:02:18 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			add_to_history(t_history *his, char *shell_line)
{
	t_history	*history;

	history = his;
	if (history->str == NULL)
		history->str = ft_strdup(shell_line);
	else
	{
		if (history->next)
		{
			while (history->next)
				history = history->next;
		}
		history->next = malloc(sizeof(*history));
		history->next->str = ft_strdup(shell_line);
		history->next->prev = history;
		history->next->next = NULL;
	}
}

void			read_loop(int out)
{
	t_history	*history;
	t_history	*tmp;
	char		*line;

	history = g_shell.history;
	if (get_next_line(out, &line) > 0)
	{
		history->str = ft_strdup(line);
		history->prev = NULL;
		history->next = NULL;
		while (get_next_line(out, &line) > 0)
		{
			history->next = (t_history *)malloc(sizeof(*(history)));
			tmp = history;
			history = history->next;
			history->str = ft_strdup(line);
			history->prev = tmp;
			history->next = NULL;
		}
	}
}

int				append_to_list(void)
{
	t_history	*tmp;
	int			out;

	out = open(".ftsh_history", O_RDWR);
	if (out < 0)
		return (-1);
	dell_history();
	read_loop(out);
	tmp = g_shell.history;
	while (tmp)
	{
		ft_putendl(tmp->str);
		tmp = tmp->next;
	}
	return (0);
}

void			add_arg_to_history(t_data *data)
{
	int			i;

	i = 2;
	if (data->args[2] == NULL)
	{
		ft_putendl("sh: history: give at least one argument");
		show_helper_history();
		data->binreturn = 255;
		return ;
	}
	while (data->args[i])
		add_to_history(g_shell.history, data->args[i++]);
}

void			append_to_file(void)
{
	t_history	*history;
	int			fd;

	history = g_shell.history;
	fd = open(".ftsh_history", O_WRONLY | O_TRUNC |
		O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR);
	while (history)
	{
		ft_putendl_fd(history->str, fd);
		history = history->next;
	}
}
