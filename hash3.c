/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 15:14:01 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 15:14:17 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		set_bin(char *path)
{
	char	**tabhash;
	int		hash;
	char	*bin;

	if (!access(path, F_OK | X_OK) || !access(path, F_OK | W_OK))
	{
		bin = ft_chrbin(path);
		hash = hash_bin(bin);
		tabhash = get_tabhash(NULL, 0);
		if (tabhash[hash] != NULL)
			set_open_adressing(tabhash, hash, path);
	}
}
