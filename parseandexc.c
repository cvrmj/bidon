/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandexc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:30:52 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/17 11:45:24 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		*createbinpathtools(t_data *data, char *str, int i)
{
	ft_strdel(&str);
	str = ft_strjoin(data->allp[i], "/");
	str = ft_joinfree(str, data->args[0], 1);
	return (str);
}

int			createbinpath(t_data *data, int n)
{
	int		i;
	char	*str;

	i = 0;
	(void)n;
	str = NULL;
	if (data->args && data->args[0] &&
		(!ft_strncmp(data->args[0], "./", 2) || data->args[0][0] == '/') &&
		createbinpath2(data, str) == 1)
		return (1);
	else if ((str = get_bin(data->args[0])))
	{
		data->bin = ft_strdup(str);
		return (1);
	}
	else
	{
		ft_putstr_fd(data->args[0], 2);
		ft_putendl_fd(": Command not found.", 2);
		data->binreturn = 255;		
		exit(1);
	}
	return (0);
}

int			createthetab(t_data *data)
{
	int		i;
	int		o;

	o = 0;
	if (createbinpath(data, 1) == 1)
	{
		data->tabb = (char **)malloc(sizeof(char *) *
			(ft_strlentab(data->args) + 1));
		data->tabb[o++] = ft_strdup(data->bin);
		i = 1;
		while (data->args[i] != NULL)
		{
			data->tabb[o] = ft_strdup(data->args[i]);
			o++;
			i++;
		}
		data->tabb[o] = NULL;
		ft_strdel(&data->bin);
		return (1);
	}
	else
	{
		return (-1);
	}
}

void		sub_forkall(t_data *data)
{
	if (access(data->tabb[0], F_OK) == 0)
	{
		ft_reset_term(g_shell.term_reset.term_copy);
		if (data->envi == 1)
			execve(data->tabb[0], data->tabb, NULL);
		else
			execve(data->tabb[0], data->tabb, data->env);
	}
}

void		forkall(t_data *data, int status)
{
	pid_t	father;

	if (createthetab(data) == 1)
	{
		father = fork();
		if (father > 0)
		{
			wait(&status);
			ft_reset_term(g_shell.term_reset.term);
		}
		else if (father == 0)
			sub_forkall(data);
		freetab(data->tabb);
		data->binreturn = status;
		// ft_putstr("valeur de retour: ");
		// ft_putnbr(data->binreturn);
		// ft_putstr("\n");
		return ;
	}
	else
	{
		ft_putstr(data->args[0]);
		ft_putendl(": Command not found.");
		data->binreturn = 255;
	}
	return ;
}
