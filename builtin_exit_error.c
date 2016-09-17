/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:24:05 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/13 05:19:21 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		ft_exit_error(t_data *data, int *out)
{
	unsigned char b;

	*out = 1;
	b = 0;
	if (data->exit_line)
	{
		if (ft_isnumber(data->exit_line))
			b = (unsigned char)ft_atoi(data->exit_line);
		else if (data->exit_line[0] == '-' && data->exit_line[1] && \
		ft_isnumber(&data->exit_line[1]))
			b = (unsigned char)ft_atoi(data->exit_line);
		else if (data->exit_line[0] == '-' && data->exit_line[1] == '-')
		{
			ft_putstr_fd("exit: Badly formed number.\n", 2);
			*out = 255;
		}
		else
		{
			ft_putstr_fd("exit: Expression Syntax.\n", 2);
			*out = 255;
		}
		ft_strdel(&data->exit_line);
	}
	return (b);
}

void	exit_no_pipe(t_data *data, char **tabb)
{
	if (tabb[0] && tabb[1] && tabb[2])
	{
		free_liste2(data->liste);
		ft_putendl_fd("exit : too many arguments", 2);
		return ;
	}
	if (!tabb[1])
	{
		free_liste2(data->liste);
		exit((data->binreturn = 0));
	}
	else if (tabb[0] && tabb[1])
	{
	if (ft_isnumber(tabb[1]) || 
			(tabb[1][0] == '-' && ft_isnumber(*(tabb + 1) + 1)))
		{
			data->binreturn = ft_atoi(tabb[1]);
			free_liste2(data->liste);
			exit(data->binreturn);
		}
	}
	ft_putendl_fd("exit: Expression Syntax.\n", 2);
	data->binreturn = ft_atoi(tabb[1]);
	free_liste2(data->liste);
	exit(data->binreturn);
}

void	exit_on_pipe(t_data *data, char **tabb)
{
	if (tabb[0] && tabb[1] && tabb[2])
		ft_putendl_fd("exit : too many arguments", 2);
	if (!tabb[1])
		exit((data->binreturn = 0));
	else if (tabb[0] && tabb[1])
	{
		if (ft_isnumber(tabb[1]) || 
			(tabb[1][0] == '-' && ft_isnumber(*(tabb + 1) + 1)))
				exit((data->binreturn = ft_atoi(tabb[1])));
			else
				ft_putendl_fd("exit: Expression Syntax.\n", 2);
	}
	exit((data->binreturn = 255));
}

int		ft_isnumber(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_tabdel(char ***tb)
{
	long	i;

	if (*tb && **tb)
	{
		i = 0;
		while ((*tb)[i] != NULL)
		{
			free((*tb)[i]);
			++i;
		}
		free(*tb);
		*tb = NULL;
	}
}
