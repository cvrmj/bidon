/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 15:23:18 by bde-maze          #+#    #+#             */
/*   Updated: 2016/07/26 14:44:26 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		*in_out(char *str)
{
	int		i;
	int		quote;
	int		inib;

	inib = 0;
	quote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' && !(quote + inib))
		{
			if (str[i + 1] && str[i + 1] != ' ' && !(str[i] = 0))
				return (str + i + 1);
		}
		if (quote && str[i] == quote && inib == 0)
			quote = 0;
		else if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		else if (str[i] == '\\' && quote + inib == 0)
			inib = 1;
		else
			inib = 0;
	}
	return (0);
}

t_tk		*new_out(t_tk **ptr, t_tk **prev, t_tk **base, char *tmp)
{
	t_tk	*new;

	if (!(new = (t_tk *)malloc(sizeof(t_tk))))
		return (0);
	new->arg = ft_strdup(tmp);
	new->tk = OTHER;
	if (*prev == *ptr && *prev == *base)
	{
		new->next = (*base);
		(*base) = new;
	}
	else
	{
		new->next = *ptr;
		(*prev)->next = new;
	}
	return (new);
}

void		concat_out(t_tk **prev, char *str)
{
	char	*tmp;

	tmp = (*prev)->arg;
	(*prev)->arg = ft_strjoin((*prev)->arg, " ");
	ft_memdel((void *)&tmp);
	tmp = (*prev)->arg;
	(*prev)->arg = ft_strjoin((*prev)->arg, str);
	ft_memdel((void *)&tmp);
}

int			is_a_next_exec(t_tk *ptr)
{
	if (ptr->tk != 0 && ptr->tk != 1 && ptr->tk != 2 && ptr->tk != 3)
		return (1);
	else if (ptr->tk == 3 && !ft_strcmp("|", ptr->arg))
		return (1);
	return (0);
}

t_tk		*good_order(t_tk *ptr, t_tk *prev, t_tk *base)
{
	char	*tmp;
	t_tk	*in;

	in = NULL;
	while (ptr)
	{
		if (((ptr->tk == REDDIR && ft_strcmp(ptr->arg, "|")) ||
			ptr->tk == AGGR)
			&& ptr->next && ptr->next->tk == 0
			&& (tmp = in_out(ptr->next->arg)))
		{
			if (prev == ptr || prev->tk != 0)
				in = new_out(&ptr, &prev, &base, tmp);
			else
				concat_out(&in, tmp);
		}
		else if (!in && ptr->tk == 0)
			in = ptr;
		if (is_a_next_exec(ptr))
			in = NULL;
		prev = ptr;
		ptr = ptr->next;
	}
	return (base);
}
