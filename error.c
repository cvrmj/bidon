// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   error.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2016/07/20 18:14:12 by bde-maze          #+#    #+#             */
// /*   Updated: 2016/08/23 19:47:01 by bde-maze         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "includes/shell.h"

// int				set_redir_var(char *str, int nb_redir, int last)
// {
// 	if (ft_strncmp(str, ";", 1) == 0)
// 		nb_redir = 0;
// 	if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, "<<", 2) == 0)
// 	{
// 		if (last == 3)
// 		{
// 			ft_putendl("Missing name for redirect.");
// 			return (-1);
// 		}
// 		nb_redir++;
// 	}
// 	return (nb_redir);
// }

// int				set_redir_var2(char *str, int nb_redir2, int last)
// {
// 	if (ft_strncmp(str, ";", 1) == 0)
// 		nb_redir2 = 0;
// 	if (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, ">>", 2) == 0)
// 	{
// 		if (last == 3)
// 		{
// 			ft_putendl("Missing name for redirect.");
// 			return (-1);
// 		}
// 		nb_redir2++;
// 	}
// 	return (nb_redir2);
// }

// int				check_aggr(char *str, int tk)
// {
// 	if (tk == 1)
// 	{
// 		if (ft_strlen(str) < 3 || (ft_strlen(str) == 3 &&
// 		(ft_isdigit(str[2]) == 0 && str[2] != '-')))
// 		{
// 			ft_putendl("syntax error near unexpected token `\\n'");
// 			return (-1);
// 		}
// 		else if (ft_strlen(str) == 4 &&
// 			(ft_isdigit(str[3]) == 0 && str[3] != '-'))
// 		{
// 			ft_putchar(str[3]);
// 			ft_putendl(": ambigous redirect");
// 			return (-1);
// 		}
// 	}
// 	return (0);
// }

// void			add_digit_aggr(t_tk *liste)
// {
// 	char		*str;

// 	while (liste != NULL)
// 	{
// 		if (liste->tk == 1 && ft_isdigit(liste->arg[0]) == 0)
// 		{
// 			str = ft_strjoin("1", liste->arg);
// 			free(liste->arg);
// 			liste->arg = str;
// 		}
// 		liste = liste->next;
// 	}
// }

// int				check_list(t_tk *liste, t_tk *ptr, int ret, int nb_agg)
// {
// 	int			nb_redir;
// 	int			nb_redir2;
// 	int			under_cmd;
// 	int			last;

// 	under_cmd = 0;
// 	nb_redir = 0;
// 	nb_redir2 = 0;
// 	last = 0;
// 	while (ptr != NULL)
// 	{
// 		if (ptr->tk == 1)
// 			nb_agg++;
// 		nb_redir = set_redir_var(ptr->arg, nb_redir, last);
// 		nb_redir2 = set_redir_var2(ptr->arg, nb_redir2, last);
// 		if (nb_redir == -1 || nb_redir2 == -1 ||
// 			(ret = check_aggr(ptr->arg, ptr->tk)) == -1)
// 			return (-1);
// 		if ((ret = switch_case(ptr, nb_redir, nb_redir2)) == -1)
// 			return (-1);
// 		last = ptr->tk;
// 		ptr = ptr->next;
// 	}
// 	add_digit_aggr(liste);
// 	return (0);
// }
