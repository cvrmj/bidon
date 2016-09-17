/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:03:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/24 10:57:09 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		get_next_word_after(char *str, int c)
{
	while (str[c])
	{
		if (str[c] == ' ')
		{
			while (str[c + 1] == ' ')
				c++;
			return (c);
		}
		c++;
	}
	return (-1);
}

int		get_next_word_before(char *str, int c)
{
	while (c > 0 && str[c])
	{
		if (str[c] != ' ')
		{
			while (c > 0 && str[c - 1] != ' ')
			{
				c--;
			}
			return (c);
		}
		c--;
	}
	return (-1);
}
