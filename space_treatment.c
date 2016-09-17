/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_treatment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:36:13 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 13:34:04 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char			*erase_first_space(char *line)
{
	int			i;

	i = 0;
	while ((line[i] == ' ') || (line[i] == 9))
		line++;
	i = 0;
	while (line[i])
	{
		if (line[i] == 9)
			line[i] = ' ';
		i++;
	}
	return (line);
}

char			*replace_rest_of_space(char *str, int len)
{
	int			i;

	i = len;
	while (str[len - 1] && str[len - 1] == ' ')
		--len;
	if (i != len)
	{
		if (str[len - 1] == '\\')
		{
			if (str[len - 2] && str[len - 2] == '\\')
				str[len] = 0;
			else if (str[len + 1])
				str[len + 1] = 0;
			return (str);
		}
		else
			str[len] = 0;
		return (str);
	}
	return (str);
}

int				sub_find(char *cmd, char quote, int inib)
{
	if (*cmd == '\\' && quote + inib == 0)
		inib = 1;
	else
		inib = 0;
	return (inib);
}

t_tk			*find_space(char *cmd, t_tk *token, int inib, char quote)
{
	char		*ptr;
	char		*tmp;

	ptr = cmd;
	tmp = cmd;
	while (cmd && *cmd)
	{
		if (!(quote + inib) && is_a_spec2(cmd, *cmd))
		{
			token = analyse_and_stock(&ptr, &cmd, &token);
			ptr = cmd + 1;
		}
		if (quote && *cmd == quote && inib == 0)
			quote = 0;
		else if (!quote && (*cmd == '"' || *cmd == '\''))
			quote = *cmd;
		else
			inib = sub_find(cmd, quote, inib);
		cmd++;
	}
	if (ptr != cmd)
		token = analyse_and_stock(&ptr, &cmd, &token);
	return (token);
}

char			*free_space(char *str, int quote, int d, int i)
{
	int			inib;

	inib = 0;
	while (str[++i])
	{
		if (!quote && str[i] == ' ' && inib == 0)
		{
			if (i != 0)
				str[d++] = str[i];
			while (str[++i] && str[i] == ' ')
				;
		}
		if (quote && str[i] == quote && inib == 0)
			quote = 0;
		else if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		if (inib == 1)
			inib = 0;
		else if (str[i] == '\\' && quote == 0)
			inib = 1;
		str[d++] = str[i];
	}
	str[d] = '\0';
	return (replace_rest_of_space(str, ft_strlen(str)));
}
