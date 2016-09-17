/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandexc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:02 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/11 19:46:12 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		checkaccess(char *str)
{
	if (access(str, F_OK) == 0)
		return (1);
	return (0);
}

void	catchpath(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strstr(data->env[i], "PATH=") != NULL)
		{
			data->path = ft_strsub(data->env[i], 5, ft_strlen(data->env[i]));
			return ;
		}
		i++;
	}
}

void	changepathintab(t_data *data)
{
	catchpath(data);
	if (data->path)
	{
		data->allp = ft_strsplit(data->path, ':');
		ft_strdel(&data->path);
	}
}

int		createbinpath2(t_data *data, char *str)
{
	(void)str;
	if (!access(data->args[0], F_OK | X_OK))
	{
		data->bin = ft_strdup(data->args[0]);
		return (1);
	}
	else
	{
		ft_putstr_fd(data->args[0], 2);
		if (!access(data->args[0], F_OK))
			ft_putendl_fd(": Permission denied", 2);
		else
			ft_putendl_fd(": Command not found.", 2);
		exit(1);
	}
	return (0);
}

void	freedata(char *str, t_data *data)
{
	ft_strdel(&str);
	freetab(data->allp);
}
