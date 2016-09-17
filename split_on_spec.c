/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 13:24:32 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/10 14:47:44 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_tk			*add_end_list(t_tk *tk, t_tk **base)
{
	t_tk *tmp;

	if (!base || !*base)
		return (tk);
	tmp = *base;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tk;
	return (*base);
}

void			sub_sub_split_norm(char **cmd, t_tk *cur, int i)
{
	char		*tmp;

	tmp = *cmd;
	while (*cmd && ft_isdigit(**cmd))
	{
		cur->arg[++i] = **cmd;
		*cmd += 1;
	}
	if (*(*cmd) && (*(*cmd)) == '-')
	{
		cur->arg[++i] = *(*cmd);
		*cmd += 1;
	}
	if (!is_a_spec2(*cmd, **cmd) && **cmd != ' ' && **cmd != 0)
	{
		*cmd = tmp;
		tmp = ft_strchr(cur->arg, '&');
		*(tmp + 1) = 0;
	}
	cur->arg[++i] = 0;
	*cmd -= 1;
}

void			sub_split_norm(char **cmd, t_tk *cur, int i)
{
	if (ft_isdigit(**cmd))
	{
		*cmd += 1;
		while (*cmd && **cmd && ft_isdigit(**cmd))
		{
			cur->arg[++i] = **cmd;
			*cmd += 1;
		}
	}
	if ((**cmd == '>' || **cmd == '<') && *(*cmd + 1) != '&')
	{
		cur->arg[++i] = **cmd;
		if (*(*cmd + 1) == '>')
			cur->arg[++i] = *(*cmd + 1);
		return ;
	}
	if (!ft_strncmp(*cmd, ">&", 2))
	{
		if (ft_isdigit(cur->arg[0]))
			cur->arg[++i] = '>';
		cur->arg[++i] = '&';
		*cmd += 2;
	}
	else if (!ft_strncmp(*cmd, "<&", 2))
	{
		if (ft_isdigit(cur->arg[0]))
			cur->arg[++i] = '<';
		cur->arg[++i] = '&';
		*cmd += 2;
	}
	sub_sub_split_norm(cmd, cur, i);
}

t_tk			*split_norm(char **ptr, char **cmd, t_tk **base, t_tk *cur)
{
	int			i;

	i = 0;
	if ((**cmd == '<' || **cmd == '>') && ft_strncmp(*cmd, "<<", 2))
	{
		if (**cmd == '<')
			cur->arg[0] = '0';
		else
			cur->arg[0] = '1';
		cur->arg[++i] = **cmd;
	}
	else
		cur->arg[0] = **cmd;
	if ((ft_isdigit(**cmd)))
		sub_split_norm(cmd, cur, i);
	else if ((**cmd == '&' || **cmd == '>' || **cmd == '<' || **cmd == '|')
		&& *(*cmd + 1) == cur->arg[i])
	{
		cur->arg[++i] = *(*cmd + 1);
		*cmd += 1;
	}
	cur->tk = add_token(cur->arg);
	*base = add_end_list(cur, base);
	while (*cmd && *(*cmd + 1) && *(*cmd + 1) == ' ')
		*cmd += 1;
	*ptr = *cmd;
	return (*base);
}

t_tk			*split_on(char **ptr, char **cmd, t_tk **base, t_tk *cur)
{
	char		c;
	int			len;

	len = ft_strlen(*ptr);
	sub_split_on_spec(cmd, ptr);
	c = **cmd;
	if (!(cur = (t_tk *)malloc(sizeof(t_tk))))
		return (0);
	cur->next = NULL;
	cur->inib = 0;
	if (*ptr != *cmd)
	{
		**cmd = 0;
		cur->arg = replace_rest_of_space(ft_strdup(*ptr), ft_strlen(*ptr));
		*base = add_end_list(cur, base);
		**cmd = c;
		*ptr = *cmd;
		cur->tk = OTHER;
		return (split_on(ptr, cmd, base, NULL));
	}
	if (!(cur->arg = ft_memalloc(sizeof(char) * len + 1)))
		return (0);
	cur->arg = ft_memset(cur->arg, 0, len);
	return (split_norm(ptr, cmd, base, cur));
}
