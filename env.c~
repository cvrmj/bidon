/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:40:39 by bde-maze          #+#    #+#             */
/*   Updated: 2016/05/23 09:25:30 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		existornah(char **tabb, char *str)
{
	int	i;

	i = 0;
	while (tabb[i] != NULL)
	{
		if (rognagestring(tabb[i], str) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	**printifenv2(char **tabb, char *str)
{
	int		i;
	int		o;
	char	**dst;

	dst = (char **)malloc(sizeof(char *) * (ft_strlentab(tabb) + 2));
	i = 0;
	o = 0;
	while (tabb[i] != NULL)
	{
		dst[o] = ft_strdup(tabb[i]);
		o++;
		i++;
	}
	dst[o] = ft_strdup(str);
	dst[o + 1] = NULL;
	freetab(tabb);
	return (dst);
}

char	**callenvtool2(char **tabb, t_data *data, int i)
{
	if (existornah(tabb, data->args[i]) == 1)
		tabb = printifenv(tabb, data->args[i]);
	else
		tabb = printifenv2(tabb, data->args[i]);
	return (tabb);
}

void	callenv(t_data *data)
{
	int		i;
	char	**tabb;

	i = 1;
	tabb = newtab(data->env);
	if (ft_strcmp(data->line, "env") == 0)
	{
		freetab(tabb);
		printab(data->env);
		return ;
	}
	while (data->args[i])
	{
		if (ft_strstr(data->args[i], "=") != NULL)
			tabb = callenvtool2(tabb, data, i);
		else
		{
			freetab(tabb);
			argsifenv(data, i);
			forkall(data, 0);
			return ;
		}
		i++;
	}
	callenvtool(data, tabb);
}
