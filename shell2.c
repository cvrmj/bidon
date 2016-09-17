/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 15:01:47 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/17 04:57:17 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void				*ft_realloc(void *ptr, size_t size)
{
	char			*newptr;

	newptr = NULL;
	if (ptr)
	{
		newptr = (char *)malloc(size);
		ft_bzero(newptr, size);
		if (!newptr)
			return (NULL);
		ft_memcpy(newptr, ptr, g_shell.length_line);
		ft_memdel(&ptr);
	}
	return (newptr);
}

int					shell_loop(t_term *term, t_data *data, char **env)
{
	(void)env;
	while (g_shell.shell_status)
	{
		g_shell.shell_backslash_level = 0;
		g_shell.last_backslash = 0;
		g_shell.history_index = get_history_length() + 1;
		prompt_line(data->env);
		shterm_listen(term);
		readgnl(data, g_shell.shell_line, 1);
		if ((g_shell.shell_line)[0] == '\0')
			continue ;
	}
	return (0);
}

int					shterm_listen(t_term *term)
{
	if (term)
		term->term_name = "a";
	cursor_init();
	g_shell.length_line = 0;
	ft_bzero(g_shell.shell_line, g_shell.size);
	shell_listening_char();
	return (-1);
}

void				update_shell_line_original(void)
{
	if (g_shell.history_index == get_history_length() + 1)
	{
		if (g_shell.backslash_index == -1)
		{
			if (ft_strcmp(g_shell.shell_line, g_shell.shell_line_original) != 0)
			{
				ft_bzero(g_shell.shell_line_original, g_shell.size);
				g_shell.shell_line_original =
				ft_strcat(g_shell.shell_line_original, g_shell.shell_line);
			}
		}
		else if (g_shell.shell_backslash_level != 0)
		{
			ft_bzero(g_shell.shell_line_original, g_shell.size);
			g_shell.shell_line_original = ft_strcat(g_shell.shell_line_original,
				&g_shell.shell_line[g_shell.last_backslash]);
		}
	}
	if (g_shell.length_line > (g_shell.size / 2) - 20)
	{
		g_shell.size = g_shell.size * 2;
		g_shell.shell_line = ft_realloc(g_shell.shell_line, g_shell.size);
		g_shell.shell_line_original =
			ft_realloc(g_shell.shell_line_original, g_shell.size);
	}
}
