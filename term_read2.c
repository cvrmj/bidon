/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 16:53:08 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 16:53:21 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		ft_putstr_i(char *str, int i)
{
	int res;

	res = 0;
	while (str[i])
	{
		if (i >= g_shell.selected_start && i <= g_shell.selected_end)
		{
			tputs(tgetstr("mr", NULL), 0, tputs_putchar);
		}
		ft_putchar(str[i]);
		i++;
		res++;
		tputs(tgetstr("me", NULL), 0, tputs_putchar);
	}
	return (res);
}

char	*add_to_array(char *str, char c, int i, int len)
{
	while (len >= i)
	{
		str[len + 1] = str[len];
		len--;
	}
	str[i] = c;
	return (str);
}

char	*del_from_arr(char *str, int i)
{
	while (str[i])
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i - 1] = '\0';
	return (str);
}

void	move_cursor_left(void)
{
	if (g_cursor.position_line != 0)
	{
		g_cursor.position_line--;
		if (g_cursor.position_x_rel == 0)
		{
			g_cursor.position_y_rel--;
			g_cursor.position_x_rel = g_shell.shell_win_size - 1;
			g_cursor.position_y_abs--;
		}
		else
			g_cursor.position_x_rel--;
	}
}

void	move_cursor_right(void)
{
	if (g_cursor.position_line < g_shell.length_line)
	{
		if (g_cursor.position_x_rel == g_shell.shell_win_size - 1)
		{
			g_cursor.position_x_rel = -1;
			g_cursor.position_y_abs++;
		}
		g_cursor.position_line++;
		g_cursor.position_x_rel++;
	}
}
