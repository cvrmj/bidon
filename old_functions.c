/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:10:12 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/03 16:12:49 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		**ft_tab_trim(char **s)
{
	int			i;
	char		*temp;

	i = 0;
	while (s[i])
	{
		temp = s[i];
		s[i] = ft_strtrim(s[i]);
		ft_strdel(&temp);
		i++;
	}
	return (s);
}

int			ft_nbrwrds(const char *s)
{
	int			i;
	int			words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (ft_isblanck(s[i]))
			i++;
		if (!ft_isblanck(s[i]) && s[i])
			words++;
		while (!ft_isblanck(s[i]) && s[i])
			i++;
	}
	return (words);
}

char		*ft_strsave(char const *s, size_t *i, size_t *len)
{
	while (ft_isblanck(s[*i]))
		(*i)++;
	while (!ft_isblanck(s[*i]) && s[*i])
	{
		(*i)++;
		(*len)++;
	}
	*i = *i - *len;
	return (ft_strsub(s, *i, *len));
}

char		**ft_strsplit2(char const *s)
{
	char		**res;
	size_t		i;
	size_t		j;
	size_t		words;
	size_t		len;

	words = 0;
	i = 0;
	j = 0;
	len = 0;
	words = ft_nbrwrds(s);
	res = (char **)malloc((words + 1) * sizeof(res));
	if (res == NULL)
		return (NULL);
	while (i < words)
	{
		res[i++] = ft_strsave(s, &j, &len);
		j = j + len;
		len = 0;
	}
	res[words] = NULL;
	return (res);
}

int			ft_isblanck(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}
