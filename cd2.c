/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 08:56:01 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/13 04:58:59 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char	*getpwd(void)
{
	char	*tmp;
	char	*dst;

	tmp = ft_memalloc(1024);
	if (getcwd(tmp, 1024) != NULL)
	{
		dst = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (dst);
	}
	return (NULL);
}

void	add_pwd(t_data *data, char *pwd)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (ft_strlentab(data->env) + 2));
	i = -1;
	while (data->env[++i])
		new[i] = ft_strdup(data->env[i]);
	new[i] = ft_strjoin("PWD=", pwd);
	new[++i] = NULL;
	freetab(data->env);
	data->env = new;
}

void	to_set_pwd(t_data *data)
{
	int		i;
	char	*str;
	char	**tabb;
	char	*pwd;

	str = getpwd();
	tabb = data->env;
	i = -1;
	pwd = NULL;
	while (tabb[++i])
	{
		if (!ft_strncmp(tabb[i], "PWD=", 4))
		{
			free(tabb[i]);
			tabb[i] = ft_strjoin("PWD=", str);
			if (data->pwd)
				free(data->pwd);
			data->pwd = str;
			return ;
		}
	}
	return (add_pwd(data, str));
}

void	add_opwd(t_data *data, char *opwd)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (ft_strlentab(data->env) + 2));
	i = -1;
	while (data->env[++i])
		new[i] = ft_strdup(data->env[i]);
	new[i] = ft_strjoin("OLDPWD=", opwd);
	data->voldpwd = opwd;
	new[++i] = NULL;
	freetab(data->env);
	data->env = new;
}


void	to_set_opwd(t_data *data)
{
	int		i;
	char	*str;
	char	**tabb;
	char	*pwd;

	str = getpwd();
	tabb = data->env;
	i = -1;
	pwd = NULL;
	while (tabb[++i])
	{
		if (!ft_strncmp(tabb[i], "OLDPWD=", 7))
		{
			free(tabb[i]);
			tabb[i] = ft_strjoin("OLDPWD=", str);
			return ;
		}
	}
	return (add_opwd(data, str));
}

void	gethome(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strstr(data->env[i], "HOME=") != NULL)
		{
			data->home = ft_strsub(data->env[i], 5, ft_strlen(data->env[i]));
			return ;
		}
		i++;
	}
	data->home = NULL;
}
