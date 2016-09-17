/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 17:01:40 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/27 13:53:25 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_liste		*del_last_null_arg(t_liste *liste)
{
	t_liste *tmp;
	t_liste *t;
	t_liste *b;

	tmp = liste;
	b = liste;
	while (liste)
	{
		if (liste->next && !liste->next->arg)
		{
			tmp = liste->next;
			liste->next = NULL;
			while (tmp)
			{
				t = tmp->next;
				if (tmp->arg)
					ft_strdel(&tmp->arg);
				free(tmp);
				tmp = t;
			}
		}
		liste = liste->next;
	}
	return (b);
}

char		*ft_str_f_join(char *b, char *d)
{
	char *tmp;

	if (!b && !d)
		return (NULL);
	if (!b && d)
		return (ft_strdup(d));
	if (!d)
		return (b);
	tmp = b;
	b = ft_strjoin(b, " ");
	ft_strdel(&tmp);
	tmp = b;
	b = ft_strjoin(b, d);
	ft_strdel(&tmp);
	tmp = NULL;
	return (b);
}

char		*get_arg_nodes(t_tree *tree)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (tree)
	{
		if (tree->left)
		{
			tmp = get_arg_nodes(tree->left);
			str = ft_str_f_join(str, tmp);
			ft_memdel((void **)&tmp);
		}
		str = ft_str_f_join(str, tree->arg);
		tree = tree->right;
	}
	return (str);
}

void		sub_arg_to_list(t_liste *cur, t_tree *tree)
{
	if (tree)
	{
		if (cur->arg != NULL)
		{
			cur->next = create_list();
			cur = cur->next;
		}
		cur->arg = get_arg_nodes(tree);
	}
}

void		arg_to_list(t_liste *liste, t_tree *tree)
{
	t_liste *cur;

	cur = liste;
	while (tree && tree->tk > 3)
	{
		if (tree->left)
		{
			if (cur->arg != NULL)
			{
				cur->next = create_list();
				cur = cur->next;
			}
			cur->arg = get_arg_nodes(tree->left);
		}
		if (cur->arg != NULL)
		{
			cur->next = create_list();
			cur = cur->next;
		}
		cur->arg = ft_strdup(tree->arg);
		tree = tree->right;
	}
	sub_arg_to_list(cur, tree);
}
