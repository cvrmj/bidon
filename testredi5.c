/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 16:04:05 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 12:22:21 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "includes/shell.h"

int		helpall2(t_data *data, t_liste2 *liste)
{
	int	out;

	out = open(liste->next->tabich[0], O_WRONLY | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND);
	freetab(data->args);
	data->args = newtab(liste->tabich);
	if (createbinpath(data, 2) == 0)
	{
	  data->binreturn = 255;
		ft_putstr(data->args[0]);
		ft_putendl(": Command not found");
		exit(0);
	}
	dup2(out, 1);
	close(out);
	execveremix(data);
	return (1);
}

void	printtab(char **tabb)
{
	int i;

	i = 0;
	ft_putendl("_______TAB________");
	while (tabb[i] != NULL)
	{
		ft_putendl(tabb[i]);
		i++;
	}
	ft_putendl("_______TAB________");
}

int		agregmid2(t_liste2 *liste, int pfd[2], int status)
{
	int b;
	b = ft_atoi(decoupe2(liste->agreg));
	if (status == 0)
	{
		if (b == 2)
			dup2(pfd[1], 2);
		else
			dup2(pfd[1], 1);
	}
	else
	{
		if (b == 1)
			dup2(pfd[1], 2);
		else
			dup2(pfd[1], 1);
	}
	// if (ft_strcmp(dst, "-") == 0)
	// 	close(pfd[1]);
	return (1);
}

int		agregmid(t_data *data, t_liste2 *liste, int pfd[2])
{
	pid_t father;
	int status;
	int a;
	char *dst;

	dst = decoupe2(liste->agreg);
	a = ft_atoi(decoupe1(liste->agreg));
	if (ft_strcmp(dst, "-") == 0)
	{
		close(a);
		// else
		dup2(pfd[1], 1);
		ft_strdel(&dst);
		if (execveremix(data) == -1)
			exit(0);
		dup2(pfd[1], 1);
		return (5);
	}
	ft_strdel(&dst);
	status = 0;
	father = fork();
	if (father == 0)
	{
		close(1);
		close(2);
		execveremix(data);
	}
	else
		wait(&status);
	agregmid2(liste, pfd, status);
	if (execveremix(data) == -1)
		exit(0);
	return(65);
}

int		hulppls(t_data *data, t_liste2 *liste, int pfd[2])
{
	freetab(data->args);
	data->args = newtab(liste->tabich);
	if (liste->redi == 7)
	{
		ft_putendl("CHIO");
		char **tabb;
		tabb = ft_strsplit(liste->rediavan, '>');
		int out;

		out = open(tabb[1], O_WRONLY | O_TRUNC |
		O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
		S_IRWXO);
		int k = ft_atoi(tabb[0]);
		if (isanum(tabb[0]))
		{
			dup2(out, k);
			// dup2(pfd[1], 1);
			// close(pfd[0]);
			if (execveremix(data) == -1)
				exit(0);
		}
		return(67);
	}
	if (liste->redi == 6)
	{
		agregmid(data, liste, pfd);
		return (50);
	}
	if (ft_strcmp(data->args[0], "exit") == 0)
		exit(0);
	if (createbinpath(data, 2) == 0)
	{
	  data->binreturn = 255;
		ft_putstr(data->args[0]);
		ft_putendl(": Command not found");
		exit(0);
	}
	dup2(pfd[1], 1);
	close(pfd[0]);
	if (execveremix(data) == -1)
		exit(0);
	return (1);
}

int		printerrred(t_liste2 *tmp)
{
	ft_putstr(tmp->tabich[0]);
	ft_putendl(": Command not found");
	return (1);
}

void	helpagreve(t_data *data, int a, int b, t_liste2 *liste)
{
	if (ft_strstr(data->oldtbe[ft_strlentab(data->oldtbe) - 1], "<") != NULL)
		dup2(a, b);
	else
		dup2(b, a);
	freetab(data->args);
	data->args = newtab(liste->tabich);
	execveremix(data);
}
*/
