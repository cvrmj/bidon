/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 14:04:12 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 12:22:46 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"
/*
int		optchev3(int fd, char *line)
{
	int i;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	return (i);
}

int		optchev4(t_data *data, int fd, char *line, char **tabich)
{
	int o;

	o = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tabich[o] = ft_strdup(line);
		ft_strdel(&line);
		o++;
	}
	ft_strdel(&line);
	close(fd);
	tabich[o] = NULL;
	data->tabchev = newtab(tabich);
	freetab(tabich);
	data->okchev = 1;
	return (1);
}

int		optchev2(t_data *data, int i, char *str)
{
	int		o;
	char	**tabich;
	char	*line;
	int		fd;

	o = 0;
	line = NULL;
	if (optchev(data) == 1)
	{
		fd = open(str, O_RDWR);
		i = optchev3(fd, line);
		close(fd);
		fd = open(str, O_RDWR);
		tabich = (char **)malloc(sizeof(char *) * (i + 1));
		optchev4(data, fd, line, tabich);
	}
	return (1);
}

int		thereisadoubleleft(t_data *data)
{
	int i;

	i = 0;
	while (data->oldtbe[i])
	{
		if (ft_strcmp(data->oldtbe[i], "<<") == 0)
			return (1);
		i++;
	}
	return (-1);
}

void	free_liste2(t_liste2 *ptr)
{
	t_liste2		*tmp;

	while (ptr->next != NULL)
	{
		tmp = ptr->next;
		freetab(ptr->tabich);
		free(ptr);
		ptr = tmp;
	}
	free(ptr);
}
*/
