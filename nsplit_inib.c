/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_inib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 13:51:02 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 14:27:35 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				ft_strlen_word_inib(char *str, int i, int inib, int quote)
{
	int			len;

	len = 0;
	while (str && str[++i])
	{
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (is_a_word(quote, inib, str[i]))
				len++;
			inib = 0;
		}
		if (!(inib + quote) && len && str[i] == ' ')
			return (len);
	}
	return (len);
}

char			*ft_strcpy_inib(char *dest, char *str, int i, int j)
{
	int			inib;
	int			quote;

	inib = 0;
	quote = 0;
	while (str && str[++i])
	{
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (is_a_word(quote, inib, str[i]))
				dest[++j] = str[i];
			inib = 0;
		}
		if (!(inib + quote) && j != -1 && str[i] == ' ')
			return (dest);
	}
	return (dest);
}

t_tk			*ft_nstrcpy_inib(t_tk *l, char *str, int i, int j)
{
	int			inib;
	int			quote;

	inib = 0;
	quote = 0;
	while (str && str[++i])
	{
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (is_a_word(quote, inib, str[i]))
			{
				l->arg[++j] = str[i];
				quote + inib ? l->tk = 1 : l->tk;
			}
			inib = 0;
		}
		if (!(inib + quote) && j != -1 && str[i] == ' ')
		{
			l->arg[++j] = 0;
			return (l);
		}
	}
	return (l);
}

int				search_next_pos(char *str, int i, int inib, int quote)
{
	int			word;

	word = 0;
	while (str && str[++i])
	{
		if (!(inib + quote) && word == 1 && str[i] == ' ')
		{
			while (!(word = 0) && str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			return (i);
		}
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (!word && is_a_word(quote, inib, str[i]))
				word = 1;
			inib = 0;
		}
	}
	return (0);
}

char			**ft_split_inib(char **argv, char *str, int len, int i)
{
	int			cur_len;
	int			cur_pos;

	cur_pos = 0;
	while (++i < len)
	{
		cur_len = ft_strlen_word_inib(str, cur_pos - 1, 0, 0);
		argv[i] = (char *)malloc(sizeof(char) * (cur_len + 1));
		argv[i] = ft_strcpy_inib(argv[i], str, cur_pos - 1, -1);
		argv[i][cur_len] = 0;
		cur_pos = search_next_pos(str, cur_pos - 1, 0, 0);
	}
	return (argv);
}

t_tk			*ft_nsplit_inib(t_tk *l, char *str, int len, int i)
{
	int			cur_len;
	int			cur_pos;
	t_tk		*b;

	cur_pos = 0;
	while (++i < len)
	{
		cur_len = ft_strlen_word_inib(str, cur_pos - 1, 0, 0);
		ft_putstr("len :  ");
		ft_putnbr(cur_len);
		ft_putendl("  each len;");
		if (l && (l->next = (t_tk *)malloc(sizeof(t_tk))))
			l = l->next;
		else
		{
			l = (t_tk *)malloc(sizeof(t_tk));
			b = l;
		}
		l->tk = 0;
		l->arg = (char *)malloc(sizeof(char) * (cur_len + 1));
		l = ft_nstrcpy_inib(l, str, cur_pos - 1, -1);
		l->arg[cur_len] = 0;
		ft_putstr("arg :  ");
		ft_putstr(l->arg);
		ft_putendl("  each arg;");
		cur_pos = search_next_pos(str, cur_pos - 1, 0, 0);
		l->next = NULL;
	}
	return (b);
}

char			**split_on_inib(char *str)
{
	int			len;
	char		**argv; // 
		
	len = ft_strlen_inib(str, 0, 0, 0);
	if (!len)
		ft_putendl(": Command not found.");
	if (len == -1)
		ft_putendl("Unmatched quote.");
	if (len <= 0)
	    return (NULL);
	argv = (char **)malloc(sizeof(char *) * (len + 1)); //
	argv = ft_split_inib(argv, str, len, -1);
	argv[len] = NULL;
	return (argv);
}

t_tk			*nsplit_on_inib(char *str)
{
	int			len;
	t_tk		*l;
		
	len = ft_strlen_inib(str, 0, 0, 0);
	ft_putstr("len :  ");
	ft_putnbr(len);
	ft_putendl("  total len;");
	if (!len)
		ft_putendl(": Command not found.");
	if (len == -1)
		ft_putendl("Unmatched quote.");
	if (len <= 0)
	    return (NULL);
	l = ft_nsplit_inib(NULL, str, len, -1);
	return (l);
}
