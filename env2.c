/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:47:46 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/17 12:49:28 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	callenvitools(t_data *data, char **tabb, int i)
{
	if (data->fona == 1)
		freetab(tabb);
	else
		free(tabb);
	data->envi = 1;
	argsifenv(data, i);
	forkall(data, 0);
}

void	callenvi(t_data *data)
{
	int		i;
	char	**tabb;

	i = 2;
	tabb = (char **)malloc(sizeof(char *) * ft_strlentab(data->args) + 1);
	data->fona = 0;
	while (data->args[i])
	{
		if (ft_strstr(data->args[i], "=") != NULL)
		{
			tabb[i - 2] = ft_strdup(data->args[i]);
			data->fona = 1;
		}
		else
		{
			tabb[i - 2] = NULL;
			callenvitools(data, tabb, i);
			return ;
		}
		i++;
	}
	tabb[i - 2] = NULL;
	printab(tabb);
	freetab(tabb);
	data->envi = 0;
}

int		env_var_exist(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strchr(env[i], '=');
		*tmp = 0;
		if (!ft_strcmp(str, env[i]))
		{
			*tmp = '=';
			return (i);
		}
		*tmp = '=';
	}
	return (-1);
}

char	**fill_env_var_norm(char **new, char **tabb, int j, int i)
{
	int		t;
	char	*tmp;

	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
	{
		*tmp = 0;
		if (env_var_exist(tabb[i], new) == -1)
		{
			*tmp = '=';
			new[++j] = ft_strdup(tabb[i]);
			new[j + 1] = NULL;
		}
		else if ((t = env_var_exist(tabb[i], new)) > -1)
		{
			free(new[t]);
			*tmp = '=';
			new[t] = ft_strdup(tabb[i]);
		}
		*tmp = '=';
		i++;
	}
	return (new);
}

char	**fill_env_var(char **new, char **env, char **tabb)
{
	int		i;
	int		j;
	int		t;
	char	*tmp;

	j = -1;
	i = 1;
	while (env[++j])
		new[j] = ft_strdup(env[j]);
	new[j] = NULL;
	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
	{
		*tmp = 0;
		if ((t = env_var_exist(tabb[i], new)) > -1)
		{
			free(new[t]);
			*tmp = '=';
			new[t] = ft_strdup(tabb[i]);
		}
		*tmp = '=';
		i++;
	}
	return (fill_env_var_norm(new, tabb, j - 1, 1));
}

char	**get_var(char **tabb)
{
	int		i;
	int		len;
	char	**new;

	i = 2;
	len = 0;
	while (tabb[i] && ft_strchr(tabb[i], '='))
	{
		len++;
		i++;
	}
	new = (char **)malloc(sizeof(char *) * (len + 1));
	i = 2;
	len = -1;
	new[0] = NULL;
	new = fill_env_var_norm(new, tabb, -1, 2);
/*	while (tabb[i] && ft_strchr(tabb[i], '='))
	{
		new[++len] = ft_strdup(tabb[i]);
		i++;
	}
	new[++len] = NULL;
*/	return (new);
}

char	**get_env_nd_var(char **tabb, char **env)
{
	int		i;
	int		len;
	char	*tmp;
	char	**new;

	len = 0;
	i = 1;
	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
	{
		*tmp = 0;
		if (env_var_exist(tabb[i], env) == -1)
			len++;
		*tmp = '=';
		i++;
	}
	len += ft_strlentab(env);
	new = (char **)malloc(sizeof(char *) * (len + 1));
	new = fill_env_var(new, env, tabb);
	return (new);
}

int		env_error(char **tabb)
{
	char	*tmp;
	int		i;

	i = 1;
	if (!ft_strcmp(tabb[i], "-i"))
		i++;
	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
	{
		if (tmp == tabb[i])
		{
			ft_putendl_fd("env : Invalid arguments", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_new_env(char **new)
{
	int i;

	i = -1;
	while (new[++i])
		ft_memdel((void **)&new[i]);
	free(new);
}

void	env_phase_2(t_data *data, int e, char **env)
{
	char **tmp;

	(void)tmp;
	(void)e;
	(void)env;
	if (env_error(data->liste->tabb))
	{
		(data->binreturn = 1);
		return ;
	}
	if (!ft_strcmp(data->liste->tabb[1], "-i"))
	{
		if (e)
			free_new_env(data->cur_env);
		data->cur_env = get_var(data->liste->tabb);
	}
	else
	{
		if (e)
		{
			tmp = newtab(data->cur_env);
			data->cur_env = get_env_nd_var(data->liste->tabb, tmp);
			free_new_env(tmp);
		}
		else
			data->cur_env = get_env_nd_var(data->liste->tabb, data->env);
	}
	data->binreturn = 0;
	print_or_exec(data);
}

void	exec_on_env(t_data *data)
{
	pid_t	t;
	int		status;

	status = -1;
//	if (data->args)
//	{
/*		while (data->args[++status])
			ft_memdel((void **)data->args[status]);
			free(data->args);
			}*/
	status = 0;
	data->args = newtab(data->liste->tabb);
	if ((t = fork()) == 0)
	{
		if (is_a_builtin(data->args[0]))
		{
			builtin_no_pipe(data);
			exit(1);
		}
		printab(data->args);
		write(1, "\0", 1);
		if (createthetab(data))
			execve(data->tabb[0], data->tabb, data->cur_env);
		int i;
		i = -1;
		while (data->args[++i])
			free(data->args[i]);
		ft_memdel((void **)&data->args);
		exit(1);
	}
	else
	{
		waitpid(t, &status, 0);
	}
//	free_new_env(data->args);
	data->args = NULL;
}

void	print_or_exec(t_data *data)
{
	char	*tmp;
	char	**tabb;
	int		i;
	int		p;

	p = -1;
	tabb = data->liste->tabb;
	i = 1;
	if (!ft_strcmp(tabb[i], "-i"))
		i++;
	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
		i++;
	if (!tabb[i])
	{
		printab(data->cur_env);
		free_new_env(data->cur_env);
		data->cur_env = NULL;
		return ;
	}
	else
	{
		while (tabb[i])
		{
			tabb[++p] = tabb[i];
			i++;
		}
		while (p < i)
			tabb[++p] = NULL;
		if (!ft_strcmp(tabb[0], "env"))
			env_phase_2(data, 1, data->cur_env);
		else
			exec_on_env(data);
		free_new_env(data->cur_env);
	}
}

void	callallenv(t_data *data)
{
	if (!data->liste->tabb[1])
		return (printab(data->env));
	env_phase_2(data, 0, NULL);
}
