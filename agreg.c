/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agreg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 18:34:05 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 16:07:02 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		isanum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (1);
}

int		secondpart(char *str)
{
	int		i;
	int		o;
	char	*dst;

	i = 0;
	o = 0;
	dst = malloc(sizeof(char) * (ft_strlen(str) - (i + 1)));
	i = countstr(str, i);
	if (i == -2)
		return (-2);
	i = i + 1;
	while (str[i])
	{
		dst[o] = str[i];
		o++;
		i++;
	}
	dst[o] = '\0';
	if (isanum(dst) == 1 || dst[o - 1] == '-')
	{
		ft_strdel(&dst);
		return (1);
	}
	return (-1);
}

int		checkagred(char *str, int i, int o)
{
	char	*dst;

	while (str[i] != '>' && str[i] != '<')
	{
		if (str[i] == '\0')
			return (-2);
		i++;
	}
	dst = malloc(sizeof(char) * (o + 1));
	while (o < i)
	{
		dst[o] = str[o];
		o++;
	}
	dst[o] = '\0';
	if (isanum(dst) == 1 && (secondpart(str) == 1))
	{
		ft_strdel(&dst);
		return (1);
	}
	ft_strdel(&dst);
	return (-1);
}

char	*decoupe1(char *str)
{
	int		i;
	char	*dst;

	i = 0;
	while ((str[i] != '>' && str[i] != '<') && str[i])
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	i = 0;
	while ((str[i] != '>' && str[i] != '<') && str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*decoupe2(char *str)
{
	int		i;
	char	*dst;
	int		o;

	o = 0;
	i = 0;
	while (str[i] != '&' && str[i])
		i++;
	dst = malloc(sizeof(char) * (ft_strlen(str) - (i + 1)));
	i++;
	while (str[i])
	{
		dst[o] = str[i];
		i++;
		o++;
	}
	dst[o] = '\0';
	return (dst);
}

