/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 15:48:23 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/17 12:36:04 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"
/*
void		helpmainpipehelp2(t_data *data, t_liste2 *liste, int k)
{
	int in;

	in = -1;
	if (k == 1)
	{
		in = open(liste->next->tabich[0], O_RDONLY);
	}
	else if (k == 2)
		in = open(".file_for_ready", O_RDONLY);
	if (in == -1)
	{
		ft_putstr("21sh: no such file or directory: ");
		ft_putendl(liste->next->tabich[0]);
		exit(0);
	}
	if (in == -1)
		exit(1);
	dup2(in, 0);
	close(in);
	doubleredichieh(data, liste, 0);
	if (data->tabchev)
		freetab(data->tabchev);
	return ;
}

void		help_dbl(t_data *data, int i, t_liste2 *liste, int fd)
{
	if (fd == -1)
	{
		freetab(data->args);
		data->args = newtab(liste->tabich);
		execveremix(data);
	}
	else
	{
		while (data->tabchev[i])
		{
			ft_putendl(data->tabchev[i]);
			i++;
		}
		freetab(data->tabchev);
		data->args = newtab(liste->tabich);
		execveremix(data);
	}
}

int			optchev(t_data *data)
{
	int	i;

	i = 0;
	while (data->oldtbe[i])
	{
		if (ft_strcmp(data->oldtbe[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}
*/

void	cd_on_pipe(t_data *data)
{	char **tabb = data->args;
	struct stat sb;

	stat(tabb[1], &sb);
	if (!data->args[1])
		exit(0);
	if (data->args[1] && data->args[2] && data->args[3])
		ft_putendl_fd("cd: too many arguments", 2);
	else if (access(data->args[1], F_OK))
		ft_putendl_fd("cd: no such file or directory", 2);
	else if (access(tabb[1], F_OK | R_OK))
		ft_putendl_fd("cd: access denied", 2);
	else if ((S_ISREG(sb.st_mode)))
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(tabb[1], 2);
	}
	else
		exit(0);
	exit(255);
}

int		sub_exec(t_data *data)
{
	int ret;
	int ex;

	ret = 0;
	ex = 0;
	if (!ft_strcmp(data->args[0], "exit"))
		exit_on_pipe(data, data->args);
	if (!ft_strcmp(data->args[0], "cd"))
	{
		cd_on_pipe(data);
		exit(0);
	}
//		ex = ft_exit_error(data, &ret);
//		if (ret)
//			exit(ex);
//	}
	if (ft_strcmp(data->args[0], "env") == 0)
	{
		int i = -1;
		data->liste->tabb = newtab(data->args);
		while (data->args[++i])
			ft_memdel((void **)&data->args[i]);
		ft_memdel((void **)&data->args);
		callallenv(data);
		exit((data->binreturn = 0));
	}
	if (ft_strcmp(data->args[0], "echo") == 0)
	{
		callecho(data->args);
		exit((data->binreturn = 0));
	}
	else
		return (1);
	return (0);
}

int			execveremix(t_data *data)
{
	if (sub_exec(data) && createthetab(data) == 1)
	{
		if (access(data->tabb[0], F_OK) == 0)
		{
			// ft_reset_term(g_shell.term_reset.term_copy);
			if (data->envi == 1)
				execve(data->tabb[0], data->tabb, NULL);
			else
			{
				execve(data->tabb[0], data->tabb, data->env);
				// ft_reset_term(g_shell.term_reset.term);
				return (1);
			}
			// ft_reset_term(g_shell.term_reset.term);
		}
		freetab(data->tabb);
		freetab(data->args);
		return (-2);
	}
	exit(255);
}
