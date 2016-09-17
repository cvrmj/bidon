/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:36:34 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 14:36:55 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			press_shift_up(void)
{
	int			h;
	int			k;

	k = g_shell.shell_win_size;
	h = g_cursor.position_line;
	while (h > 0 && k > 0)
	{
		if (g_shell.backslash_index == 0)
			break ;
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		if (g_shell.backslash_index > 0)
			g_shell.backslash_index--;
		h--;
		k--;
	}
}

void			press_shift_down(void)
{
	int			h;
	int			k;

	k = g_shell.shell_win_size;
	h = g_cursor.position_line;
	while (h < g_shell.length_line && k > 0)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
		h++;
		k--;
	}
}

char			*extract_str(char *str, int a, int b)
{
	char		*res;
	int			i;
	int			temp;

	i = 0;
	temp = b - a + 1;
	res = (char *)malloc(sizeof(*res) * (b - a + 2));
	res[b - a + 1] = '\0';
	while (i < (temp))
	{
		res[i] = str[a];
		a++;
		i++;
	}
	return (res);
}

void			press_option_c(void)
{
	if (g_shell.selected_start != -1 && g_shell.selected_end != -1)
	{
		if (ft_strcmp(g_shell.selected_copy, "") != 0)
			ft_strdel(&g_shell.selected_copy);
		g_shell.selected_copy = extract_str(g_shell.shell_line, \
				g_shell.selected_start, g_shell.selected_end);
	}
}

void			press_option_v(void)
{
	char		*str;
	size_t		i;
	char		a[2];

	i = 0;
	str = g_shell.selected_copy;
	a[1] = '\0';
	while (i < ft_strlen(str))
	{
		a[0] = str[i];
		press_printable_char(a);
		i++;
	}
}
