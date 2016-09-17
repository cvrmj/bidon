/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:35:10 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 14:35:23 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			movements_delete(int a)
{
	int h[2];

	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
	h[0] = ft_putstr_i(g_shell.shell_line, g_cursor.position_line);
	h[1] = h[0];
	while (h[0] - 1 > 0)
	{
		move_cursor_right(g_cursor, g_shell);
		h[0]--;
	}
	if ((g_cursor.position_x_rel == g_shell.shell_win_size - 1) && \
			g_cursor.position_line != g_shell.length_line)
	{
		ft_putstr(" ");
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
	move_cursor_right(g_cursor, g_shell);
	while (h[1] - a > 0)
	{
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		h[1]--;
	}
}

void			press_backspace_key(void)
{
	if (g_cursor.position_line > 0 && g_shell.backslash_index != 0)
	{
		g_shell.shell_line =
			del_from_arr(g_shell.shell_line, g_cursor.position_line);
		g_shell.length_line--;
		press_left_key();
		movements_delete(0);
	}
}

void			press_delete_key(void)
{
	if (g_cursor.position_line >= 0 &&
		g_cursor.position_line != g_shell.length_line)
	{
		g_shell.shell_line = del_from_arr(g_shell.shell_line, \
				g_cursor.position_line + 1);
		g_shell.length_line--;
		movements_delete(0);
	}
}

void			print_history(t_history *history)
{
	t_history	*his;

	his = history;
	while (his)
	{
		ft_putstr_fd(his->str, 2);
		ft_putstr_fd("\n", 2);
		his = his->next;
	}
}

void			press_up_key(void)
{
	t_history	*history;

	if (g_shell.history_index > 0)
	{
		history = g_shell.history;
		if (g_shell.backslash_index != -1)
		{
			g_shell.history_index--;
			if (g_shell.history_index > 0)
				replace_shell_backslash_line(
				get_history_i(g_shell.history_index - 1));
			if (g_shell.history_index == 0)
				g_shell.history_index++;
		}
		else if (g_shell.history_index != 1)
		{
			g_shell.history_index--;
			replace_shell_line(get_history_i(g_shell.history_index - 1));
		}
	}
}
