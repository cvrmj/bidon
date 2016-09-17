/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:25:49 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 12:22:59 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"
/*
int		mainpipehelp(t_data *data, t_liste2 *liste)
{
	if (mainpipecond(data, liste) != -1)
	{
		exit(0);
		return (6);
	}
	else if (mainpipehelp2(data, liste) != -1)
	{
		exit(45);
		return (2);
	}
	else if (liste->next->next == NULL)
	{
		if (createbinpath(data, 2) == 0)
			return (5);
		freetab(data->args);
		data->args = newtab(liste->tabich);
		execveremix(data);
		return (1);
	}
	return (0);
}

int		mainpipe(t_data *data, t_liste2 *liste)
{
	pid_t	father;
	int		pfd[2];

	pipe(pfd);
	// if (liste->redi == 6)
	// 	dup2(1, 2);
	if (mainpipehelp(data, liste) != 0)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
	if ((father = fork()) == 0)
		childhelp(data, liste, pfd);
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		if ((liste->redi == 3 || liste->redi == 8 || liste->redi == 6 || liste->redi == 7) && liste->next->next)
			return (mainpipe(data, liste->next->next));
		else
			return (mainpipe(data, liste->next));
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(father, NULL, 0);
	return (1);
}

int		initmainredi(t_data *data, int i)
{
	char	*str;

	// ft_putendl(g_shell.shell_line);
	data->liste = createliste();
	data->args = ft_strsplit(g_shell.shell_line, ' ');
	data->oldtbe = newtab(data->args);
	str = ft_strdup(data->args[(ft_strlentab(data->args) - 1)]);
	argliste(data);
	if (movecd(data) == 2)
		return (1);
	freetab(data->args);
	data->args = newtab(data->oldtbe);
	optchev2(data, i, str);
	ft_strdel(&str);
	return (0);
}

int		mainredi(t_data *data, int i)
{
	(void)data;
	(void)i;
	int		father;
	t_liste2 *tmp;

	if (initmainredi(data, i) == 1)
		return (1);
	tmp = data->liste;
	while (tmp->next)
	{
		ft_putendl(ft_itoa(tmp->redi));
		if (tmp->rediavan)
			ft_putendl(tmp->rediavan);
		// ft_putendl("__________");
		tmp = tmp->next;
	}
	if (ifitsredi(data) != 0)
	{
		father = fork();
		if (father == 0)
		{
			mainpipe(data, data->liste);
			exit(0);
		}
		else
		{
			wait(0);
			ft_reset_term(g_shell.term_reset.term);
		}
	}
	else
		return (1);
	return (1);
}
*/
