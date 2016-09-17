/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:55:32 by bde-maze          #+#    #+#             */
/*   Updated: 2016/05/23 09:55:37 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		alreadyexist(char **tabb, char *str)
{
	int	i;

	i = 0;
	while (tabb[i])
	{
		if (rognagestring(str, tabb[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
