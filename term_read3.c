/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 16:53:26 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 16:53:43 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	go_left(void)
{
	if (g_cursor.position_x_rel == 0)
	{
		tputs(tgetstr("up", NULL), 0, tputs_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, \
					g_shell.shell_win_size - 1), 1, tputs_putchar);
	}
	else if (g_cursor.position_line != 0)
	{
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
}

void	go_right(void)
{
	if (g_cursor.position_x_rel == g_shell.shell_win_size - 1)
	{
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, tputs_putchar);
		tputs(tgetstr("do", NULL), 0, tputs_putchar);
	}
	else
	{
		tputs(tgoto(tgetstr("nd", NULL), 0, 0), 0, tputs_putchar);
	}
}

int		get_n_line(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.shell_backslash_level > 0)
		return ((g_shell.backslash_index + 3) / g_shell.shell_win_size);
	return ((g_cursor.position_line + 6) / g_shell.shell_win_size);
}

int		get_pos_l(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.shell_backslash_level > 0)
		return ((g_shell.backslash_index + 2) % g_shell.shell_win_size);
	if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
		return (0);
	else
		return (6 + (g_cursor.position_line % g_shell.shell_win_size));
}

void	update_cursor(void)
{
	g_cursor.position_x_rel = get_pos_l();
	g_cursor.position_y_rel = get_n_line();
}
