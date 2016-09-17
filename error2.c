/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 17:44:28 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 10:59:08 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				is_a_word2(int quote, int inib, char *str, int *p)
{
	int i;

	i = *p;
	if (!(is_a_word(quote, inib, str[i])) && str[i] != ' ')
		return (0);
	if (!quote + inib && ((str[i] == '|'  && !str[i + 1]) || str[i] == '<' || str[i] == '>'))
	{
		if ((str[i] == '>' && str[i + 1] == '>') ||
			(str[i] == '<' && str[i + 1] == '<'))
			*p += 1;
		return (2);
	}
	return (1);
}

int				find_error(char *str, int inib, int quote, int i)
{
	int t;
	int a;

	t = 0;
	while (str[++i])
	{
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			while (!quote + inib && str[i] == ' ')
				i++;
			a = is_a_word2(quote, inib, str, &i);
			if ((!t && a == 2) || (t == 2 && a == 2))
				return (1);
			t = a;
			inib = 0;
		}
	}
	return (0);
}

int				check_list_2(t_liste *liste)
{
	while (liste)
	{
		if (ft_strcmp(";", liste->arg) && find_error(liste->arg, 0, 0, -1))
		{
			ft_putendl("Invalid null command.");
			return (1);
		}
		liste = liste->next;
	}
	return (0);
}
