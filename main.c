/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:46:45 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/17 11:56:38 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			readgnl2(t_data *data, char *str, t_liste *liste)
{
	data->fona = 0;
	data->dspam = 0;
	data->oldpwd = getpwd();
	gethome(data);
	str = (transformtab(withoutspace(str)));
	data->line = ft_strdup(str);
	ft_strdel(&str);
	parsecommand(data, liste);
	if (data->dspam == 0 && data->args)
		ft_tabdel(&data->args);
	if (data->line != NULL)
		ft_strdel(&data->line);
	if (data->home)
		ft_strdel(&data->home);
	if (data->oldpwd)
		ft_strdel(&data->oldpwd);
}

int			main_init(t_term *term)
{
	if (term_init(term) == -1)
	{
		ft_putendl_fd("Error on init", 2);
		return (-1);
	}
	shell_init();
	return (0);
}


int				opbi(char *operator, t_data *data)
{
	if (ft_strcmp(operator, "&&") == 0)
	{
		if (data->binreturn == 0)
			return (0);
		else
			return (-1);
	}
	if (ft_strcmp(operator, "||") == 0)
	{
		if (data->binreturn != 0)
			return (0);
		else
			return (-1);
	}
	return (0);
}

void			sub_read(t_tree *tree, t_data *data)
{
	t_liste		*liste;
	t_liste		*tmp;

	liste = create_list();
	arg_to_list(liste, tree);
	liste = del_last_null_arg(liste);
	free_tree(tree);
	// if (check_list_2(liste))
	// {
		// free_list2(liste);
		// ft_strdel(&data->line);
		// return ;
	// }
	// else
	tmp = liste;
	while (tmp)
	{
		if (ft_strcmp(tmp->arg, ";") && ft_strcmp(tmp->arg, "||") &&
			ft_strcmp(tmp->arg, "&&"))
			readgnl2(data, tmp->arg, liste);
		else
		{
			if (ft_strcmp(tmp->arg, ";"))
			{
				if (opbi(tmp->arg, data))
				{
					while (tmp->next && ft_strcmp(tmp->arg, ";"))
					{
						ft_strdel(&tmp->arg);
						tmp = tmp->next;
					}
				}
			}
			ft_strdel(&tmp->arg);
		}
		tmp = tmp->next;
	}
	free_list(liste);
}

void			printt(t_tk *ptr)
{
	while (ptr)
	{
		ft_putstr("token: ");
		ft_putnbr(ptr->tk);
		ft_putstr(" arg: ");
		ft_putendl(ptr->arg);
		ptr = ptr->next;
	}
}

int				readgnl(t_data *data, char *str, int fd)
{
	t_tk		*ptr;
	t_tree		*tree;
	int			ret;

	ret = 0;
	if ((ptr = to_list(str, -1)))
	{
		ret = check_list(ptr);
		printt(ptr);
		ptr = good_order(ptr, ptr, ptr);
		tree = to_tree(NULL, ptr, 5, NULL);
		if (ret == 0)
			sub_read(tree, data);
		else
			free_tree(tree);
	}
	ret = 0;
	if (data->exit)
	{
		fd = ft_exit_error(data, &ret);
		data->exit = 0;
		if (ret == 1)
			exit(fd);
	}
	return (0);
}

char			**get_new_env(char **env)
{
	int		i;
	char	**new;

	i = -1;
	new = (char **)malloc(sizeof(char *) * (ft_strlentab(env) + 1));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			new[i] = ft_joinfree("SHLVL=", ft_itoa(ft_atoi(env[i] + 6) + 1), 2);
		else if (!ft_strncmp(env[i], "SHELL=", 6))
			new[i] = ft_joinfree("SHELL=", ft_joinfree(
									 ft_joinfree(getpwd(), "/", 1), "21sh", 1), 2);
		else
			new[i] = ft_strdup(env[i]);
	}
	new[i] = NULL;
	return (new);
}

t_data			*init_data(char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->okchev = 0;
	data->exit = 0;
	data->args = NULL;
	data->exit_line = NULL;
	data->path = NULL;
	data->allp = NULL;
	data->voldpwd = NULL;
	data->pwd = NULL;
	data->cur_env = NULL;
	if (!env || !env[0])
	{
		data->env = (char **)malloc(sizeof(char *) * 4);
		data->env[0] = ft_strdup("TERM=xterm-256color");
		data->env[1] = ft_joinfree("PWD=", getpwd(), 2);
		data->env[2] = ft_strdup("SHLVL=1");
		data->env[3] = NULL;
	}
	else
		data->env = get_new_env(env);
	data->envi = 0;
	data->turn = 0;
	return (data);
}

int				main(int ac, char **av, char **env)
{
	t_data		*data;
	t_term		first;

	(void)av;
	(void)ac;
	data = init_data(env);
	init_hashtab(env, -1);
	main_init(&first);
	shell_loop(&first, data, env);
	return (0);
}
