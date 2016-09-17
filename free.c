/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:48:13 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 11:08:51 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			free_first_list(t_tk *ptr)
{
	t_tk		*tmp;

	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

void			free_list(t_liste *ptr)
{
	t_liste		*tmp;

	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	free(ptr);
}

void			free_list2(t_liste *ptr)
{
	t_liste		*tmp;

	while (ptr != NULL)
	{
		tmp = ptr->next;
		ft_strdel(&ptr->arg);
		free(ptr);
		ptr = tmp;
	}
	free(ptr);
}

void			free_tree(t_tree *tree)
{
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	if (tree)
	{
		ft_strdel(&tree->arg);
		free(tree);
	}
}

void			go_free(char *cwd, char *hostname, char *curtime)
{
	ft_strdel(&cwd);
	ft_strdel(&hostname);
	ft_strdel(&curtime);
}
