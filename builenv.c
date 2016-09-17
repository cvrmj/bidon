/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 12:43:50 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/24 14:46:51 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		ft_strlequal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*firstpartequal(char *str)
{
	int		i;
	int		length;
	char	*dst;

	i = 0;
	length = ft_strlequal(str);
	dst = malloc(sizeof(char) * (length + 1));
	while (str[i] != '=' && str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*secondpartequal(char *str)
{
	int		i;
	int		o;
	char	*dst;

	o = 0;
	i = ft_strlequal(str) + 1;
	dst = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
	while (str[i])
	{
		dst[o] = str[i];
		i++;
		o++;
	}
	dst[o] = '\0';
	return (dst);
}

char	**freshnewtab2(char **tabb, int i, char *dst, char *dst2)
{
	tabb[i] = ft_strdup(dst);
	ft_strdel(&dst);
	tabb[i + 1] = ft_strdup("=");
	tabb[i + 2] = ft_strdup(dst2);
	ft_strdel(&dst2);
	tabb[i + 3] = NULL;
	return (tabb);
}

char	**freshnewtab(t_data *data, char *dst, char *dst2)
{
	int		i;
	char	**tabb;

	i = 0;
	tabb = malloc(sizeof(char *) * (ft_strlentab(data->builttab) + 4));
	if (data->builttab)
	{
		while (data->builttab[i])
		{
			tabb[i] = ft_strdup(data->builttab[i]);
			i++;
		}
		tabb = freshnewtab2(tabb, i, dst, dst2);
		freetab(data->builttab);
		return (tabb);
	}
	tabb = freshnewtab2(tabb, i, dst, dst2);
	return (tabb);
}
