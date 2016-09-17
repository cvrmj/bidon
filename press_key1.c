/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:13:17 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/24 15:31:45 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			go_inverse(void)
{
	char		a[2];

	a[0] = ' ';
	a[1] = '\n';
	tputs(tgetstr("mr", NULL), 0, tputs_putchar);
	press_home_key();
	press_printable_char(a);
	press_backspace_key();
}

void			press_option_left(void)
{
	char		a[2];
	int			temp;

	a[0] = ' ';
	a[1] = '\n';
	temp = g_cursor.position_line;
	if (g_cursor.position_line > 0)
	{
		if (g_shell.selected_end == g_shell.selected_start)
		{
			g_shell.selected_start = g_cursor.position_line;
			g_shell.selected_end = g_cursor.position_line;
			g_shell.selected_start--;
		}
		else if (g_shell.selected_end == g_cursor.position_line)
			g_shell.selected_end--;
		else if (g_shell.selected_start == g_cursor.position_line)
			g_shell.selected_start--;
	}
	press_left_key();
	press_printable_char(a);
	press_backspace_key();
	while (g_cursor.position_line < temp - 1)
		press_right_key();
}

void			press_option_right(void)
{
	int			temp;

	temp = g_cursor.position_line;
	if (g_cursor.position_line < g_shell.length_line)
	{
		if (g_shell.selected_end == g_shell.selected_start)
		{
			g_shell.selected_start = g_cursor.position_line;
			g_shell.selected_end = g_cursor.position_line + 1;
		}
		else if (g_shell.selected_end == g_cursor.position_line)
			g_shell.selected_end++;
		else if (g_shell.selected_start == g_cursor.position_line)
			g_shell.selected_start++;
	}
	press_left_key();
	press_printable_char(" ");
	press_backspace_key();
	while (g_cursor.position_line < temp + 1)
	{
		if (g_cursor.position_line == g_shell.length_line)
			break ;
		press_right_key();
	}
}

void			press_direction_key(char *buffer)
{
	if (is_up_key(buffer))
		press_up_key();
	else if (is_down_key(buffer))
		press_down_key();
	else if (is_left_key(buffer))
		press_left_key();
	else if (is_right_key(buffer))
		press_right_key();
}

void			press_option_key(char *buffer)
{
	if (is_option_c(buffer))
		press_option_c();
	else if (is_option_v(buffer))
		press_option_v();
	else if (is_option_right(buffer))
		press_option_right();
	else if (is_option_left(buffer))
		press_option_left();
}
