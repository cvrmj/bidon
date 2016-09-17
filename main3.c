/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 12:25:20 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 12:27:53 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "includes/shell.h"

int				sub_parsecommand2(t_data *data)
{
	if ((ft_strlentab(data->args) == 1) &&
		(ft_strcmp(data->args[0], "$?") == 0))
	{
			ft_putnbr(data->binreturn);
			ft_putchar('\n');
			data->binreturn = 0;
			return (0);
	}
	else if (check_syntax_designator(data) == 0)
	{
		designator(data);
		return (0);
	}
	return (1);
}

void			sub_sub_parse(t_data *data)
{
	(void)data;
	mainredi(data, 0);
//	free_liste2(data->liste);
	freetab(data->oldtbe);
	if (data->okchev == 1)
	{
		data->okchev = 0;
		freetab(data->tabchev);
	 }
}

void			sub_parsecommand(t_data *data, int i)
{
	if (ifitsredi(data) != 0)
	{
		launch_main_fork(data);
	}
	else if (checklineok(data, data->args) != -1)
		return ;
	else if (ft_strcmp(data->args[0], "export") == 0 && (i = 1))
		insertthetmp(data);
	else if (ft_strcmp(data->args[0], "env") == 0 && (i = 1))
		callallenv(data);
	else if (ft_strcmp(data->args[0], "setenv") == 0 && (i = 1))
		callsetenv(data);
	else if (ft_strcmp(data->args[0], "unsetenv") == 0 && (i = 1))
		callunsetenv(data);
	else if (ft_strcmp(data->args[0], "cd") == 0 && (i = 1))
		cdcall(data);
	else if (sub_parsecommand2(data) == 0)
		return ;
	else if (ft_strcmp(data->args[0], "history") == 0 && (i = 1))
		history(data);
	else if (i == 0 && ft_strcmp(data->args[0], "exit") != 0)
		forkall(data, 0);
	return ;
}
*/
