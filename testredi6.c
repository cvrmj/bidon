/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 17:43:52 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 12:22:34 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"
/*
void	printlistechiche(t_liste2 *tmp)
{
	while (tmp->next != NULL)
	{
		printtab(tmp->tabich);
		ft_putnbr(tmp->redi);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

int		agreve(t_data *data, t_liste2 *liste)
{
	char	*dst;
	char	*str;
	int		a;
	int		b;

	str = decoupe1(data->oldtbe[ft_strlentab(data->oldtbe) - 1]);
	dst = decoupe2(data->oldtbe[ft_strlentab(data->oldtbe) - 1]);
	a = ft_atoi(dst);
	b = ft_atoi(str);
	if (ft_strcmp(dst, "-") == 0)
	{
		close(b);
		helpagreve2(data, liste);
	}
	if (!(isatty(a)))
	{
		ft_putstr("csh: ");
		ft_putstr(dst);
		ft_putendl(": bad file descriptor");
		exit(0);
	}
	ft_strdel(&str);
	ft_strdel(&dst);
	helpagreve(data, a, b, liste);
	exit(0);
}

void	rediboucle(t_liste2 *liste)
{
	t_history	*hist;
	int			out;
	pid_t		father;

	father = fork();
	if (father == 0)
	{
		hist = double_left(liste->next->tabich[0]);
		out = open(".file_for_ready", O_WRONLY | O_TRUNC |
		O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
		S_IRWXO);
		dup2(out, 1);
		while (hist->next)
		{
			ft_putendl(hist->str);
			hist = hist->next;
		}
		close(out);
		exit(0);
	}
	else
		wait(0);
}

int		godouble(t_data *data)
{
	t_liste2 *tmp;

	tmp = data->liste;
	rediboucle(tmp);
	return (1);
}

int		mainpipecond(t_data *data, t_liste2 *liste)
{
	if (liste->redi == 1)
	{
		helpall2(data, liste);
		return (1);
	}
	else if (liste->redi == 2)
	{
		doubleredichieh(data, liste, 0);
		return (5);
	}
	else if (liste->redi == 4)
	{
		godouble(data);
		liste->redi = 8;
		mainpipe(data, liste);
	}
	return (-1);
}
*/
