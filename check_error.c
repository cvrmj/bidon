/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 13:50:40 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 11:39:01 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			check_pipe(t_tk *liste)
{
	while (liste)
	{
		if (ft_strcmp(liste->arg, "|") == 0 || liste->tk == OPBI)
		{
			if (liste->next == NULL || (liste->next->tk > 1 &&
				(ft_strcmp(liste->next->arg, ">") != 0 &&
					ft_strcmp(liste->next->arg, ">>") != 0 &&
			ft_strcmp(liste->next->arg, "<") != 0 &&
			ft_strcmp(liste->next->arg, "<<") != 0)))
			{
				ft_putendl("Invalid null command.");
				return (-1);
			}
		}
		liste = liste->next;
	}
	return (0);
}

int			check_redi(t_tk *liste)
{
	while (liste)
	{
		if (ft_strcmp(liste->arg, ">") == 0 || ft_strcmp(liste->arg, ">>") == 0 ||
			ft_strcmp(liste->arg, "<") == 0 || ft_strcmp(liste->arg, "<<") == 0)
		{
			if (liste->next == NULL || liste->next->tk > 1)
			{
				ft_putendl("Missing name for redirect.");
				return (-1);
			}
		}
		liste = liste->next;
	}
	return (0);
}

void			add_digit_aggr(t_tk *liste)
{
	char		*str;

	while (liste != NULL)
	{
		if (liste->tk == 1 && ft_isdigit(liste->arg[0]) == 0)
		{
			str = ft_strjoin("1", liste->arg);
			ft_strdel(&liste->arg);
			liste->arg = str;
		}
		liste = liste->next;
	}
}

int			check_list(t_tk *liste)
{
	if (check_pipe(liste) != 0)
		return (-1);
	if (check_redi(liste) != 0)
		return (-1);
	add_digit_aggr(liste);
	return (0);
}
