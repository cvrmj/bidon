/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:03:07 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/23 17:02:25 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char			*get_pwd(void)
{
	char		*cwd;
	char		*tmp;
	int			len;

	len = 0;
	cwd = ft_memalloc(sizeof(char) * 1024);
	cwd = getcwd(cwd, 1024);
	if (cwd == NULL)
		return (NULL);
	len = ft_strlen(cwd);
	tmp = ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_strncpy(tmp, cwd, len);
	ft_strdel(&cwd);
	return (tmp);
}

char			*ntime(void)
{
	char		*tmp;
	int			len;
	int			i;
	char		*curtime;
	time_t		ntime;

	i = 0;
	len = 0;
	ntime = time(NULL);
	curtime = ctime(&ntime);
	while (i < 11)
	{
		curtime++;
		i++;
	}
	len = ft_strlen(curtime);
	len = len - 5;
	tmp = ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_strncpy(tmp, curtime, len);
	return (tmp);
}

char			*save_post(char *hostname)
{
	int			len;
	char		*tmp;

	len = ft_strlen(hostname);
	len = len - 6;
	tmp = ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_strncpy(tmp, hostname, len);
	ft_strdel(&hostname);
	return (tmp);
}

char			*get_user_name(char **env)
{
	int			i;
	char		*tmp;
	char		*str;

	i = 0;
	while (env[i + 1])
	{
		if (ft_strncmp(env[i], "USER=", 5) == 0)
		{
			tmp = ft_strdup(env[i] + 5);
			str = ft_strjoin(tmp, "@");
			ft_strdel(&tmp);
			return (str);
		}
		i++;
	}
	return (ft_strdup("Unknown@"));
	return (NULL);
}

void			prompt_line(char **env)
{
	char		*cwd;
	char		*hostname;
	char		*curtime;

	hostname = ft_memalloc(sizeof(char) * 1024);
	hostname[1023] = '\0';
	gethostname(hostname, 1000);
	hostname = save_post(hostname);
	hostname = ft_joinfree(get_user_name(env), hostname, 3);
	curtime = ntime();
	curtime = ft_joinfree(" ", curtime, 2);
	cwd = get_pwd();
	if (cwd == NULL)
		cwd = ft_strdup("#error#");
	ft_putstr("\033[35m");
	ft_putstr(hostname);
	ft_putstr(" \033[36m-");
	ft_putstr(curtime);
	ft_putstr("- \033[32m");
	ft_putendl(cwd);
	ft_putstr("\033[32m-> % \033[39m ");
	go_free(cwd, hostname, curtime);
}
