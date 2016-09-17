/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allwrites.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:20:47 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/23 17:28:03 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		writeonwhile(void)
{
	ft_putstr("minishell $> ");
}

void		errorbinary(t_data *data, char *str)
{
	if (str)
		ft_strdel(&str);
	ft_putstr("zsh: command not found: ");
	data->binreturn = 255;
	ft_putendl(data->args[0]);
}

t_liste2	*createliste(void)
{
	t_liste2	*liste;

	liste = (t_liste2 *)malloc(sizeof(t_liste2));
	liste->next = NULL;
	return (liste);
}
