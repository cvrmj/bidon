/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 11:02:55 by bde-maze          #+#    #+#             */
/*   Updated: 2016/05/23 10:00:18 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		rognagestring(char *str, char *str2)
{
	char	*dst;

	dst = ft_strsub(str2, 0, ft_strlenremix(str2));
	str = ft_strsub(str, 0, ft_strlenremix(str));
	if (ft_strcmp(dst, str) == 0)
	{
		ft_strdel(&str);
		ft_strdel(&dst);
		return (1);
	}
	ft_strdel(&str);
	ft_strdel(&dst);
	return (0);
}

char	**setenvifdontexist(t_data *data, int a)
{
	char	**dst;
	int		i;
	int		o;
	char	*tmp;

	dst = NULL;
	i = 0;
	o = 0;
	tmp = ft_strdup(data->env[ft_strlentab(data->env) - 1]);
	dst = (char **)malloc(sizeof(char *) * (ft_strlentab(data->env) + 2));
	while (data->env[i])
	{
		dst[o] = ft_strdup(data->env[i]);
		o++;
		i++;
	}
	ft_strdel(&dst[o - 1]);
	dst[o - 1] = ft_strdup(data->args[a]);
	dst[o] = ft_strdup(tmp);
	ft_strdel(&tmp);
	dst[o + 1] = NULL;
	if (data->turn == 1)
		freetab2(data);
	return (dst);
}

char	**setenvifexistool(t_data *data, char **dst, int a, int o)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		if (rognagestring(data->args[a], data->env[i]) == 1)
		{
			dst[o] = ft_strdup(data->args[a]);
			o++;
			if (data->env[i + 1])
				i++;
			else
			{
				dst[o] = NULL;
				return (dst);
			}
		}
		dst[o] = ft_strdup(data->env[i]);
		o++;
		i++;
	}
	dst[o] = NULL;
	return (dst);
}

char	**setenvifexist(t_data *data, int a)
{
	char	**dst;
	int		i;
	int		o;

	i = 0;
	o = 0;
	dst = (char **)malloc(sizeof(char *) * ft_strlentab(data->env) + 1);
	dst = setenvifexistool(data, dst, a, o);
	if (data->turn == 1)
		freetab2(data);
	return (dst);
}

void	callsetenv(t_data *data)
{
	int	i;

	i = 1;
	if (ft_strcmp(data->line, "setenv") == 0)
	{
		printab(data->env);
		return ;
	}
	while (data->args[i])
	{
		if (ft_strstr(data->args[i], "=") != NULL)
		{
			if (alreadyexist(data->env, data->args[i]) == 1)
				data->env = setenvifexist(data, i);
			else
				data->env = setenvifdontexist(data, i);
			data->turn = 1;
		}
		i++;
	}
}
