/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builenv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 14:39:48 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/17 06:39:43 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		alreadyintb(t_data *data, char *str, char *dst)
{
	int		i;
	char	**tabb;

	tabb = malloc(sizeof(char *) * (ft_strlentab(data->builttab) + 1));
	i = 0;
	if (data->builttab)
	{
		intb2(data, str, dst, tabb);
		ft_strdel(&str);
		ft_strdel(&dst);
		return (1);
	}
	return (-1);
}

int		checklineok(t_data *data, char **tabb)
{
	int		i;
	char	*dst;
	char	*dst2;

	i = 0;
	if (ft_strlentab(tabb) != 1)
		return (-1);
	if (ft_strstr(tabb[0], "=") != NULL)
	{
		dst = firstpartequal(tabb[0]);
		dst2 = secondpartequal(tabb[0]);
		if (alreadyin(data, dst) == 1)
			alreadyintb(data, dst, dst2);
		else
			data->builttab = freshnewtab(data, dst, dst2);
		return (1);
	}
	return (-1);
}

char	**modiftabafteruse2(t_data *data, char **tabb, int i, int o)
{
	while (data->builttab[i])
	{
		if (ft_strcmp(data->builttab[i], data->args[1]) == 0)
		{
			if (data->builttab[i + 3])
				i = i + 3;
			else
			{
				tabb[o] = NULL;
				freetab(data->builttab);
				return (tabb);
			}
		}
		tabb[o] = ft_strdup(data->builttab[i]);
		i++;
		o++;
	}
	tabb[o] = NULL;
	return (tabb);
}

char	**modiftabafteruse(t_data *data)
{
	int		i;
	char	**tabb;
	int		o;

	o = 0;
	tabb = malloc(sizeof(char *) * (ft_strlentab(data->builttab) - 2));
	i = 0;
	tabb = modiftabafteruse2(data, tabb, i, o);
	return (tabb);
}

int		insertthetmp(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	if (data->builttab)
	{
		while (data->builttab[i])
		{
			if (ft_strcmp(data->builttab[i], data->args[1]) == 0)
			{
				str = ft_strjoin(data->builttab[i], "=");
				str = ft_joinfree(str, data->builttab[i + 2], 1);
				str = ft_joinfree("setenv ", str, 2);
				data->builttab = modiftabafteruse(data);
				freetab(data->args);
				data->args = ft_strsplit(str, ' ');
				ft_strdel(&str);
				callsetenv(data);
				return (1);
			}
			i += 3;
		}
	}
	return (1);
}
