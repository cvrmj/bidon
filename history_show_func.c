/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_show_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 13:52:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 13:53:23 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			dell_history(void)
{
	t_history	*history;
	t_history	*tmp;

	history = g_shell.history;
	while (history != NULL)
	{
		tmp = history->next;
		if (history->str)
			ft_strdel(&history->str);
		free(history);
		history = tmp;
	}
	free(history);
	g_shell.history = malloc(sizeof(*(g_shell.history)));
	g_shell.history->str = NULL;
	g_shell.history->next = NULL;
	g_shell.history->prev = NULL;
}

void			show_history_until(char *nb)
{
	int			i;
	int			j;
	int			len;
	t_history	*history;

	i = 0;
	j = 0;
	len = ft_atoi(nb);
	history = g_shell.history;
	while (history && j < len)
	{
		ft_putnbr(i++);
		if (i <= 10)
			ft_putstr("     ");
		else if (i <= 100)
			ft_putstr("    ");
		else
			ft_putstr("   ");
		ft_putendl(history->str);
		history = history->next;
		j++;
	}
}

void			show_history(void)
{
	int			i;
	t_history	*history;

	i = 0;
	history = g_shell.history;
	while (history)
	{
		ft_putnbr(i++);
		if (i <= 10)
			ft_putstr("     ");
		else if (i <= 100)
			ft_putstr("    ");
		else
			ft_putstr("   ");
		ft_putendl(history->str);
		history = history->next;
	}
}

void			show_history_rev(void)
{
	int			i;
	t_history	*history;

	i = g_shell.history_index;
	history = g_shell.history;
	while (history->next)
		history = history->next;
	while (history)
	{
		ft_putnbr(i--);
		if (i < 9)
			ft_putstr("     ");
		else if (i < 99)
			ft_putstr("    ");
		else
			ft_putstr("   ");
		ft_putendl(history->str);
		history = history->prev;
	}
}

void			show_history_rev_until(char *nb)
{
	int			i;
	int			j;
	int			len;
	t_history	*history;

	i = g_shell.history_index;
	len = ft_atoi(nb);
	j = i - len;
	history = g_shell.history;
	while (history->next)
		history = history->next;
	while (history && i > j)
	{
		ft_putnbr(i--);
		if (i < 9)
			ft_putstr("     ");
		else if (i < 99)
			ft_putstr("    ");
		else
			ft_putstr("   ");
		ft_putendl(history->str);
		history = history->prev;
	}
}
