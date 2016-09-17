/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:36:05 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/29 17:43:15 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				press_enter_key(void)
{
	press_end_key();
	if (ft_init_verif())
		return (0);
	if (ft_strcmp(g_shell.shell_line, "") != 0 && g_shell.shell_heredoc == 0 && g_shell.shell_line[0] != '!')
		add_to_history(g_shell.history, g_shell.shell_line);
	g_shell.backslash_index = -1;
	if (g_shell.shell_heredoc == 0)
		g_shell.history_index = get_history_length();
	ft_putstr("\n");
	return (1);
}

void			press_shift_direction_key(char *buffer)
{
	if (is_shift_right(buffer[5]))
		press_shift_right(g_cursor, g_shell);
	else if (is_shift_left(buffer[5]))
		press_shift_left(g_cursor, g_shell);
	else if (is_shift_up(buffer[5]))
		press_shift_up();
	else if (is_shift_down(buffer[5]))
		press_shift_down();
}

void			press_shift_left(void)
{
	int			index_nw;
	int			index_c;

	index_c = g_cursor.position_line - 1;
	index_nw = get_next_word_before(g_shell.shell_line, index_c);
	if (index_nw < g_shell.last_backslash)
		index_nw = g_shell.last_backslash;
	while (index_c >= index_nw)
	{
		if (g_shell.backslash_index > 0)
			g_shell.backslash_index--;
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		index_c--;
	}
}

void			press_shift_right(void)
{
	int			index_nw;
	int			index_c;

	index_c = g_cursor.position_line;
	index_nw = get_next_word_after(g_shell.shell_line, index_c);
	while (index_c <= index_nw)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
		index_c++;
	}
}
