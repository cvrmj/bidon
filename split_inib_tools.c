/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_inib_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:00:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 14:00:43 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				is_a_word(int quote, int inib, char c)
{
	if ((quote + inib) && c != quote)
		return (1);
	else if (c != ' ' && c != '"' && c != '\'')
		return (1);
	return (0);
}

char			quote_norm(int inib, char quote, char c)
{
	if (quote && c == quote)
		quote = 0;
	else if (!inib && !quote && (c == '\'' || c == '"'))
		quote = c;
	return (quote);
}

int				ft_strlen_inib(char *str, int quote, int inib, int wrd)
{
	int			i;
	int			len;

	i = -1;
	len = 0;
	while (str && str[++i])
	{
		if (!(inib + quote) && wrd == 1 && str[i] == ' ' && (++len))
			while (!(wrd = 0) && str[i] && (str[i] == ' ' || str[i] == '\t'))
				if (!str[++i])
					break ;
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (!wrd && is_a_word(quote, inib, str[i]))
				wrd = 1;
			inib = 0;
		}
	}
	wrd ? len += 1 : len;
	quote ? len = -1 : len;
	return (len);
}
