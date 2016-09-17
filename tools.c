/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:45:14 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 04:18:00 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		ft_strlenremix(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		i++;
	}
	return (i);
}

void	freetab(char **tabb)
{
	int	i;

	i = 0;
	if (!tabb)
		return ;
	while (tabb[i] != NULL)
	{
		ft_strdel(&tabb[i]);
		i++;
	}
	free(tabb[i]);
	free(tabb);
	tabb = NULL;
}

void	freetab2(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		ft_strdel(&(data->env[i]));
		i++;
	}
	free(data->env);
	data->env = NULL;
}

int		ft_strlentab(char **tabb)
{
	int	i;

	i = 0;
	if (tabb == NULL)
		return (-1);
	while (tabb[i] != NULL)
		i++;
	return (i);
}

char	**newtab(char **tabb)
{
	char	**dst;
	int		i;

	dst = (char **)malloc(sizeof(char *) * (ft_strlentab(tabb) + 1));
	i = 0;
	while (tabb[i])
	{
		dst[i] = ft_strdup(tabb[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}
