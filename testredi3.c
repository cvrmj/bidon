/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:26:37 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 12:21:25 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"
/*
int		refredi(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (2);
	else if (ft_strcmp(str, "<") == 0)
		return (3);
	else if (ft_strcmp(str, "<<") == 0)
		return (4);
	else if (ft_strcmp(str, "|") == 0)
		return (5);
	else if (checkagred(str, 0, 0) == 1)
		return (6);
	else if (ft_strstr(str, ">") != NULL)
		return (7);
	return (0);
}

int		lastone(t_data *data)
{
	int	length;

	length = ft_strlentab(data->oldtbe);
	while (length > 0)
	{
		if (ft_strcmp(data->oldtbe[length], "|") == 0)
			return (length);
		length--;
	}
	return (-1);
}

int		pospipe(t_data *data, int i)
{
	while (data->oldtbe[i])
	{
		if ((ft_strcmp(data->oldtbe[i], "|") == 0) ||
				(ft_strcmp(data->oldtbe[i], "<") == 0))
		{
			ft_putnbr(i);
			data->posi = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	argliste(t_data *data)
{
	int			i;
	int			k;
	t_liste2	*tmp;

	tmp = data->liste;
	k = lastone(data);
	i = 0;
	data->posi = 0;
	while (data->posi != ft_strlentab(data->oldtbe))
	{
		if (i == 0)
		{
			tmp->tabich = createtab(data, 0);
			i = 1;
		}
		else
			tmp->tabich = createtab(data, data->posi + 1);
		if (data->oldtbe[data->posi])
			tmp->redi = refredi(data->oldtbe[data->posi]);
		else
			tmp->redi = 0;
		if (data->tmpagreg != NULL)
			tmp->agreg = ft_strdup(data->tmpagreg);
		else
			tmp->agreg = NULL;
		if (data->avredi != NULL)
			tmp->rediavan = ft_strdup(data->avredi);
		else
			tmp->rediavan = NULL;
		tmp->next = malloc(sizeof(t_liste2));
		tmp = tmp->next;
		tmp->next = NULL;
	}
}

void	freeliste(t_liste2 *liste)
{
	while (liste->next->next != NULL)
	{
		freetab(liste->tabich);
		liste = liste->next;
	}
	free(liste);
}
*/
