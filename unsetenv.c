/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 17:11:03 by bde-maze          #+#    #+#             */
/*   Updated: 2016/05/19 17:24:00 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char	**ft_unsetenv(t_data *data, int a)
{
	int		i;
	int		o;
	char	**dst;
	char	*tmp;

	dst = (char **)malloc(sizeof(char *) * (ft_strlentab(data->env) + 1));
	o = 0;
	i = 0;
	tmp = ft_strjoin(data->args[a], "=");
	while (data->env[i])
	{
		if ((ft_strstr(data->env[i], tmp) != NULL)
				&& (data->env[i + 1]))
			i++;
		dst[o] = ft_strdup(data->env[i]);
		o++;
		i++;
	}
	dst[o] = NULL;
	ft_strdel(&tmp);
	if (data->turn == 1)
		freetab(data->env);
	return (dst);
}

void	callunsetenv(t_data *data)
{
	int	i;

	i = 1;
	while (data->args[i])
	{
		data->env = ft_unsetenv(data, i);
		i++;
		data->turn = 1;
	}
}
