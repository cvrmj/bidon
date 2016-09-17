/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 17:16:42 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/27 17:25:10 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		**init_fill_tab(char **tabhash, char *path, int res)
{
	struct dirent	*ent;
	DIR				*dir;
	char			*tmp;

	if ((dir = opendir(path)) == NULL)
		return (0);
	while ((ent = readdir(dir)))
	{
		if (ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, ".."))
		{
			tmp = ft_str2join(path, "/", ent->d_name);
			if (!access(tmp, F_OK | X_OK) || !access(tmp, F_OK | W_OK))
			{
				if (tabhash[(res = hash_bin(ent->d_name))] != NULL)
					set_open_adressing(tabhash, res, tmp);
				else
					tabhash[res] = tmp;
			}
			else
				ft_strdel(&tmp);
		}
	}
	closedir(dir);
	return (tabhash);
}

char		**ft_create_bin_path(void)
{
	char **path;
	char *tmp;

	tmp = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki";
	path = ft_strsplit(tmp, ':');
	return (path);
}

void		init_hashtab(char **env, int i)
{
	char		**path;
	char		**tabhash;

	path = NULL;
	if (!(tabhash = (char **)malloc(sizeof(char *) * 4096)))
		return ;
	while (++i < 4096)
		tabhash[i] = NULL;
	i = 0;
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5))
		++i;
	if (env[i])
		path = ft_strsplit((env[i] + 5), ':');
	else
		path = ft_create_bin_path();
	i = -1;
	while (path && path[++i])
	{
		if (!access(path[i], F_OK | X_OK) || !access(path[i], F_OK | W_OK))
			tabhash = init_fill_tab(tabhash, path[i], 0);
		ft_strdel(&path[i]);
	}
	free(path);
	get_tabhash(tabhash, 0);
}

char		*get_openaddr(char **tabhash, int hash, char *bin)
{
	char	*tmp;
	int		i;

	i = 0;
	while (1)
	{
		if ((tmp = ft_chrbin(tabhash[hash])))
			if (tmp == NULL || !ft_strcmp(tmp, bin))
				break ;
		if (tmp == NULL)
			return (NULL);
		hash++;
		if (hash > 2048)
			hash /= 7 + (++i);
	}
	return (tabhash[hash]);
}

char		*get_bin(char *bin)
{
	int		hash;
	char	**tabhash;

	hash = 0;
	if (!(tabhash = get_tabhash(NULL, 0)))
		return (NULL);
	hash = hash_bin(bin);
	if (hash > 4096 || !tabhash[hash])
		return (NULL);
	return (get_openaddr(tabhash, hash, bin));
}
