/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 15:37:59 by hlouar            #+#    #+#             */
/*   Updated: 2016/09/17 12:12:34 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		check_if_its_agreg(char *str)
{
	int i;
	int o;

	o = ft_strlen(str);
	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '>')
				break ;
			i++;
		}
		if (i == o)
			return (-1);
		if (str[i + 1] == '&')
			return (1);
	}
	return (0);
}

/*t_larg		*ft_create_main_list(void)
{
	t_larg *liste;

	liste = malloc(sizeof(t_larg));
	liste->tabb = NULL;
	liste->redi = NULL;
	liste->next = NULL;
	return (liste);
}

void print(t_data *data)
{
	t_larg *liste;
	t_redi *tmp;
	liste = data->argli;
	while (liste)
	{
		if (liste->redi)
			tmp = liste->redi;
		printtab(liste->tabb);
		while (tmp)
		{
		ft_putendl("_____AGREG______");
		if (tmp->agreg)
			ft_putendl(tmp->agreg);
		if (tmp->redi)
			ft_putendl(ft_itoa(tmp->redi));
		ft_putendl("______AGREg_____");
		tmp = tmp->next;
		}
		liste = liste->next;
	}
}

int		redirection_or_not(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (2);
	else if (ft_strcmp(str, "<") == 0)
		return (3);
	else if (ft_strcmp(str, "<<") == 0)
		return (4);
	return (0);
}

int		ft_strlen_for_redi(char **tabb)
{
	int i;

	i = 0;
	while (tabb[i])
	{
		if (redirection_or_not(tabb[i]) > 0)
			return (i);
		i++;
	}
	return (ft_strlentab(tabb));
}

char	**ft_erase_redi_in_tab(char **tabb)
{
	char	**tmp;
	int i;
	int o;

	i = 0;
	o = 0;
	tmp = malloc(sizeof(char *) * (ft_strlen_for_redi(tabb) + 1));
	while (tabb[i])
	{
		if (redirection_or_not(tabb[i]) > 0)
		{
			tmp[o] = NULL;
			return (tmp);
		}
		tmp[o] = ft_strdup(tabb[i]);
		i++;
		o++;
	}
	tmp[o] = NULL;
	return (tmp);
}

void fill_the_main_liste(t_data *data)
{
	t_larg *liste;
	char **tabb;
	int i;

	i = 0;
	data->argli = ft_create_main_list();
	liste = data->argli;
	tabb = ft_strsplit(g_shell.shell_line, '|');
	while (tabb[i] != NULL)
	{
		char *tmp = withoutspace(tabb[i]);
		liste->tabb = ft_strsplit(tmp, ' ');
		if (tabb[i + 1])
		liste->next = malloc(sizeof(t_larg));
		else
		liste->next = NULL;
		liste = liste->next;
		i++;
	}
}

void fill_the_agreg_liste(t_data *data)
{
	t_larg *liste;
	int i;
	int o;
	t_redi *redi;

	liste = data->argli;
	i = 0;
	while (liste)
	{
		liste->redi = malloc(sizeof(t_redi));
		redi = liste->redi;
		o = 0;
		while (liste->tabb[i])
		{
			if (redirection_or_not(liste->tabb[i]) > 0)
			{
				if (o == 0)
				{
					redi->redi = redirection_or_not(liste->tabb[i]);
					redi->agreg = ft_strdup(liste->tabb[i + 1]);
					redi->next = NULL;
					o = 1;
				}
				else
				{
					redi->next = malloc(sizeof(t_redi));
					redi = redi->next;
					redi->agreg = ft_strdup(liste->tabb[i + 1]);
					redi->redi = redirection_or_not(liste->tabb[i]);
					redi->next = NULL;
				}
			}
			i++;
		}
		liste->tabb = ft_erase_redi_in_tab(liste->tabb);
		if (o == 0)
			liste->redi = NULL;
		i = 0;
		liste = liste->next;
	}
}
*/
void	stock_fd(t_lfd *l, int fd, int t)
{
	while (l->next)
	{
		if (fd == l->fd)
			break ;
		l = l->next;
	}
	if (fd != l->fd)
	{
		l->next = (t_lfd *)malloc(sizeof(t_lfd));
		l = l->next;
	}
	l->fd = fd;
	l->open = 1;
	if (t)
	{
		l->write = 1;
		l->read = 0;
	}
	else
	{
		l->read = 1;
		l->write = 0;
	}
	l->next = NULL;
}

void	search_close_fd(t_liste2 *l, int df)
{
	t_lfd *fd;

	fd = l->fd;
	while (fd)
	{
		if (fd->fd == df)
		{
			ft_putendl(ft_itoa(df));
			close(df);
			fd->open = 0;
			fd->read = 0;
			fd->write = 0;
		}
		fd = fd->next;
	}
}

int		main_fork_redirection(t_liste2 *l, t_lredi *liste)
{
	int 	out;
	t_lredi *tmp;

	out = 1;
	tmp = liste;
	while (tmp)
	{
		if (tmp->redi == 1 && tmp->next && tmp->next->str)
		{
			ft_putendl("titi");
			if ((out = open(tmp->next->str, O_WRONLY | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
							S_IRWXO)) == -1)
			{
				ft_putstr_fd(tmp->next->str, 2);
				ft_putendl_fd(": Open denied", 2);
				exit(0);
			}
			stock_fd(l->fd, out, 1);
			dup2(out, ft_atoi(tmp->str));
		}
		ft_putendl(tmp->str);
		tmp = tmp->next;
	}
	return (out);
}

int		main_fork_redirection_dbl(t_liste2 *l, t_lredi *liste)
{
	int 	out;
	t_lredi *tmp;
	char	*line;

	out = 1;
	tmp = liste;
	line = NULL;
	while (tmp)
	{
		if (tmp->redi == 3 && tmp->next && tmp->next->str)
		{
			ft_putendl("titi");
			if ((out = open(tmp->next->str, O_RDWR | O_APPEND)) == -1)
			{
				ft_putstr_fd(tmp->next->str, 2);
				ft_putendl_fd(": Open denied", 2);
				exit(0);
			}
			stock_fd(l->fd, out, 1);
			dup2(out, ft_atoi(tmp->str));
		}
		ft_putendl(tmp->str);
		tmp = tmp->next;
	}
	return (out);
}

int		main_fork_redirection2(t_liste2 *l, t_lredi *liste)
{
	t_lredi *tmp;
	int 	in;

	in = 0;
	tmp = liste;
	while (tmp)
	{
		if (tmp->redi == 3)
		{
			if ((in = open(tmp->next->str, O_RDONLY)) == -1)
			{
				ft_putstr_fd(tmp->next->str, 2);
				ft_putendl_fd(": No such file or directory", 2);
				exit(0);
			}
			stock_fd(l->fd, in, 0);
			dup2(in, ft_atoi(tmp->str));
		}
		tmp = tmp->next;
	}
	return (in);
}

int		handle_heredoc(t_liste2 *l, t_lredi *liste)
{
	t_lredi		*tmp;
	t_history	*hist;
	t_history	*t;
	int			out;

	(void)l;
	hist = NULL;
	tmp = liste;
	while (tmp)
	{
		if (tmp->redi == 4)
		{
			while (hist)
			{
				t = hist->next;
				ft_memdel((void **)&hist->str);
				ft_memdel((void **)&hist);
				hist = t;
			}
			hist = double_left(tmp->next->str);
		}
		tmp = tmp->next;
	}
	if (!hist)
		return (0);
	if ((out = open(".file_for_ready", O_RDWR | O_TRUNC |
					O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
					S_IRWXO)) == -1)
	{
		ft_putstr_fd(tmp->next->str, 2);
		ft_putendl_fd(": Open denied", 2);
		exit(0);
	}
	t = hist;
	while (hist->next)
	{
		ft_putendl_fd(hist->str, out);
		hist = hist->next;
	}
	close(out);
	if ((out = open(".file_for_ready", O_RDONLY)) == -1)
	{
		ft_putstr_fd("heredoc failed", 2);
		exit(0);
	}
	dup2(out, 0);
	return (0);
}

void		free_heredoc(t_history *hist)
{
	t_history *t;

	while (hist)
	{
		t = hist->next;
		ft_memdel((void **)&hist->str);
		ft_memdel((void **)&hist);
		hist = t;
	}
	return ;
}

void		heredoc_to_stdin(t_liste2 *l, t_history *hist, t_history *t)
{
	int out;

	if ((out = open(".file_for_ready", O_RDWR | O_TRUNC |
					O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
					S_IRWXO)) == -1)
	{
		ft_putendl_fd("heredoc failed", 2);
		exit(1);
	}
	while (hist->next)
	{
		ft_putendl_fd(hist->str, out);
		hist = hist->next;
	}
	close(out);
	if ((out = open(".file_for_ready", O_RDONLY)) == -1)
	{
		ft_putstr_fd("heredoc failed", 2);
		exit(1);
	}
	dup2(out, 0);
	stock_fd(l->fd, out, 0);
	return (free_heredoc(t));
}

void		to_handle_heredoc(t_liste2 *l, t_lredi *liste)
{
	t_lredi		*tmp;
	t_history	*hist;

	hist = NULL;
	tmp = liste;
	hist = double_left(tmp->next->str);
	while ((tmp = tmp->next))
		if (tmp->redi == 4)
			return (free_heredoc(hist));
	return (heredoc_to_stdin(l, hist, hist));
}

void		to_to_handle_heredoc(t_liste2 *l, t_lredi *liste, t_data *data)
{
	t_lredi		*tmp;
	t_history	*hist;
	t_hist_cont	*hc;

	hist = NULL;
	tmp = liste;
	hist = data->hist_cont->hist;
	hc = data->hist_cont->next;
	ft_memdel((void **)&data->hist_cont);
	data->hist_cont = hc;
	while ((tmp = tmp->next))
		if (tmp->redi == 4)
			return (free_heredoc(hist));
	return (heredoc_to_stdin(l, hist, hist));
}

void		to_handle_agreg(t_liste2 *l, t_lredi *liste)
{
	t_lredi *tmp;

	tmp = liste;
	ft_putstr(decoupe1(tmp->str));
	ft_putstr("      1 ----- 2      ");
	ft_putstr(decoupe2(tmp->str));
	write(1, "\n", 1);
	if (decoupe2(tmp->str)[0] == '-')
		search_close_fd(l, ft_atoi(decoupe1(tmp->str)));
	// close(ft_atoi(decoupe1(tmp->str)));
	//A REVOIR
	else if (ft_strchr(tmp->str, '>'))
		dup2(ft_atoi(decoupe2(tmp->str)), ft_atoi(decoupe1(tmp->str)));
	// else if (ft_strchr(tmp->str, '<'))
	// 	dup2(ft_atoi(decoupe2(tmp->str)), ft_atoi(decoupe1(tmp->str)));
}

void		to_main_fork_redirection(t_liste2 *l, t_lredi *liste)
{
	int 	out;
	t_lredi *tmp;

	out = 1;
	tmp = liste;
	if ((out = open(tmp->next->str, O_WRONLY | O_TRUNC |
					O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
					S_IRWXO)) == -1)
			{
				ft_putstr_fd(tmp->next->str, 2);
				ft_putendl_fd(": Open denied", 2);
				exit(1);
			}
	stock_fd(l->fd, out, 1);
	dup2(out, ft_atoi(tmp->str));
}

void		to_main_fork_redirection2(t_liste2 *l, t_lredi *liste)
{
	t_lredi *tmp;
	int 	in;

	in = 0;
	tmp = liste;
	if ((in = open(tmp->next->str, O_RDONLY)) == -1)
	{
		ft_putstr_fd(tmp->next->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(0);
	}
	stock_fd(l->fd, in, 0);
	dup2(in, ft_atoi(tmp->str));
}

void		to_main_fork_redirection_dbl(t_liste2 *l, t_lredi *liste)
{
	int 	out;
	t_lredi *tmp;

	out = 1;
	tmp = liste;
	if ((out = open(tmp->next->str, O_RDWR | O_APPEND)) == -1)
	{
		ft_putstr_fd(tmp->next->str, 2);
		ft_putendl_fd(": Open denied", 2);
		exit(0);
	}
	stock_fd(l->fd, out, 1);
	dup2(out, ft_atoi(tmp->str));
}

void		redi_loop(t_liste2 *l, t_lredi *liste, t_data *data)
{
	t_lredi *tmp;

	tmp = liste;
	while (tmp)
	{
		ft_putendl("redi loop");
		if (check_if_its_agreg(tmp->str) == 1)
			to_handle_agreg(l, tmp);
		if (tmp->redi == 4)
			to_to_handle_heredoc(l, tmp, data);
		if (tmp->redi == 1)
			to_main_fork_redirection(l, tmp);
		if (tmp->redi == 2)
			to_main_fork_redirection_dbl(l, tmp);
		if (tmp->redi == 3)
			to_main_fork_redirection2(l, tmp);
		tmp = tmp->next;
	}
}

int		handle_agreg(t_liste2 *l, t_lredi *liste)
{
	t_lredi *tmp;
	int 	in;

	(void)l;
	in = 0;
	tmp = liste;
	while (tmp)
	{
		if (check_if_its_agreg(tmp->str) == 1)
		{
			ft_putstr(decoupe1(tmp->str));
			ft_putstr("      1 ----- 2      ");
			ft_putstr(decoupe2(tmp->str));
			write(1, "\n", 1);
			if (decoupe2(tmp->str)[0] == '-')
				search_close_fd(l, ft_atoi(decoupe1(tmp->str)));
				// close(ft_atoi(decoupe1(tmp->str)));
			//A REVOIR
			else if (ft_strchr(tmp->str, '>'))
				dup2(ft_atoi(decoupe2(tmp->str)), ft_atoi(decoupe1(tmp->str)));
			// else if (ft_strchr(tmp->str, '<'))
			// 	dup2(ft_atoi(decoupe2(tmp->str)), ft_atoi(decoupe1(tmp->str)));
		}
		tmp = tmp->next;
	}
	return (in);
}

int		main_fork_exec_rediclose(t_data *data, t_liste2 *liste, int pfd[2], int i)
{
//	int out;
//	int in;

	(void)pfd;
	if (i == 1)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
	}
/*	handle_agreg(liste, liste->redir);
	out = main_fork_redirection(liste, liste->redir);
	in = main_fork_redirection2(liste, liste->redir);
	handle_heredoc(liste, liste->redir);
*/
	redi_loop(liste, liste->redir, data);
	freetab(data->args);
	data->args = newtab(liste->tabb);
	execveremix(data);
	return (1);
}

int		main_fork_exec(t_data *data, t_liste2 *liste, int pfd[2], int i)
{
	// ft_putendl(liste->tabb[0]);
	// ft_putendl(liste->tabb[1]);
//	freetab(data->args);
	//close(pfd[0]);
	data->args = newtab(liste->tabb);
	// ft_putnbr(out);
	t_lredi *tmp;
	tmp = liste->redir;
    main_fork_exec_rediclose(data, liste, pfd, i);
	//dup2(pfd[1], 1);
//	if (liste->redi)
	//	main_fork_exec_rediclose(data, liste);
	// dup2(pfd[1], out);
	// ft_putendl(data->args[0]);
	// ft_putendl(data->args[1]);
	// ft_putendl("____________");
	// dup2(pfd[1], 1);
	//close(pfd[0]);
//	execveremix(data);
	return (1);
}

/*
int		handle_redir(t_data *data, t_larg *liste)
{
	if (liste->redi->redi == 1)
		main_fork_exec_rediclose(data, liste);
	// else if (liste->redi->redi == 2)
	// 	ft_putendl("redirection 2");
	// else if (liste->redi->redi == 3)
	// 	ft_putendl("redirection 3");
	// else if (liste->redi->redi == 4)
	// 	ft_putendl("redirection 4");
	return (1);
}
*/
void	wait_all_pid(t_data *data)
{
	t_liste2	*liste;
	int			status;

	liste = data->liste;
	status = 0;
	while (liste)
	{
		if (liste->pid == 0)
		{
			ft_putstr_fd("NOP", 2);
			ft_putstr_fd("NOP", 2);
			ft_putstr_fd("NOP", 2);
			ft_putstr_fd("NOP\n", 2);
			exit(255);
		}
		else
			waitpid(liste->pid, &status, 0);
		liste = liste->next;
	}
//	ft_putendl_fd(ft_strjoin("END ---------------------", ft_itoa(status)), 2);
	if (status)
		exit(1);
	exit(0);
}

void 	main_fork(t_data *data, t_liste2 *liste)
{
	ft_putstr("COMMANDE :     ");
	ft_putendl(liste->tabb[0]);
	ft_putstr("redi :     \n");
//	if (liste->redir)
	//	ft_putendl(liste->redir->str);
	//if (liste->redir)
	//{
	//	main_fork_exec(data, liste, pfd);
	//	return (main_fork(data, liste->next));
	//}
	if ((liste->next == NULL) && ((liste->pid = fork()) == 0))
	{
		main_fork_exec(data, liste, NULL, 2);
	}
	else if (liste->next != NULL)
	{
		pipe(liste->pfd);
		if ((liste->pid = fork()) == 0)
			main_fork_exec(data, liste, liste->pfd, 1);
		close(liste->pfd[1]);
		dup2(liste->pfd[0], 0);
		main_fork(data, liste->next);
	}
	close(liste->pfd[1]);
	close(liste->pfd[0]);
	wait_all_pid(data);
}

void		free_liste2(t_liste2 *l)
{
	t_liste2 *ll;
	t_lredi *r;
	t_lfd *f;
	char **tt;
	int		i = -1;

	while (l)
	{
		ll = l->next;
		tt = l->tabb;
		while (tt[++i])
			ft_memdel((void **)&tt[i]);
		ft_memdel((void **)&l->tabb);
		while (l->redir)
		{
			r = l->redir->next;
			ft_memdel((void **)&l->redir->str);
			ft_memdel((void **)&l->redir);
			l->redir = r;
		}
		while (l->fd)
		{
			f = l->fd->next;
			if (l->fd->fd > 2)
				close(l->fd->fd);
			ft_memdel((void **)&l->fd);
			l->fd = f;
		}
		ft_memdel((void **)&l);
		l = ll;
	}
}

void		stock_heredoc(t_data *data, char *str)
{
	t_hist_cont *t;

	if (!data->hist_cont)
	{
		data->hist_cont = (t_hist_cont *)malloc(sizeof(t_hist_cont));
		data->hist_cont->next = NULL;
		data->hist_cont->hist = double_left(str);
		return ;
	}
	t = data->hist_cont;
	while (t->next)
	{
		t = t->next;
	}
	t->next = (t_hist_cont *)malloc(sizeof(t_hist_cont));
	t->next->next = NULL;
	t->next->hist = double_left(str);
}

void		stock_all_heredoc(t_data *data, t_liste2 *l)
{
	t_lredi *r;

	while (l)
	{
		r = l->redir;
		while (r)
		{
			if (r->redi == 4)
			{
				stock_heredoc(data, r->next->str);
			}
			r = r->next;
		}
		l = l->next;
	}
}

void	free_tabb(char **tabb)
{
	int i;

	i = -1;
	while (tabb[++i])
		ft_memdel((void **)&tabb[i]);
	free(tabb);
}


void	free_lfd(t_lfd *fd)
{
	t_lfd *tmp;

	while (fd)
	{
		tmp = fd->next;
		ft_memdel((void **)&fd);
		fd = tmp;
	}
}

void	free_lredir(t_lredi *redi)
{
	t_lredi	*tmp;

	while (redi)
	{
		tmp = redi->next;
		ft_memdel((void **)&redi->str);
		ft_memdel((void **)&redi);
		redi = tmp;
	}
}

void	free_all(t_data *data, t_liste2 *liste)
{
	t_liste2	*tmp;

	while (liste)
	{
		tmp = liste->next;
		free_tabb(liste->tabb);
		liste->tabb = NULL;
		free_lredir(liste->redir);
		liste->redir = NULL;
		free_lfd(liste->fd);
		liste->fd = NULL;
		ft_memdel((void **)&liste);
		liste = tmp;
	}
	data->liste = NULL;
	int i = -1;
	if (data->args)
		while (data->args[++i])
			ft_putendl(data->args[i]);
	i = -1;
	if (data->tabb)
		while (data->tabb[++i])
			ft_putendl(data->tabb[i]);
	if (data->l)
	{
		t_tk *tk = data->l;
		t_tk *tmp = tk;
		while (tk)
		{
			tmp = tk->next;
			ft_memdel((void **)&tk->arg);
			ft_memdel((void **)&tk);
			tk = tmp;
		}
	}
	if (data->hist_cont)
	{
		t_hist_cont *hc = data->hist_cont;
		t_hist_cont *tp = hc;
		t_history *mp;
		t_history *tm;
		while (hc)
		{
			tp = hc->next;
			mp = hc->hist;
			while (mp)
			{
				tm = mp->next;
				ft_memdel((void **)&mp->str);
				ft_memdel((void **)&mp);
				mp = tm;
			}
			ft_memdel((void **)&hc);
			hc = tp;
		}
	}
}

int		is_a_builtin(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "env") ||
		!ft_strcmp(str, "setenv") || !ft_strcmp(str, "unsetenv") || 
		!ft_strcmp(str, "echo") || !ft_strcmp(str, "exit") ||
		!ft_strcmp(str, "export") || !ft_strcmp(str, "unset") || 
		!ft_strcmp(str, "history"))
		return (1);
	return (0);
}

void	builtin_no_pipe(t_data *data)
{
	redi_loop(data->liste, data->liste->redir, data);
	if (!ft_strcmp(data->liste->tabb[0], "exit"))
		exit_no_pipe(data, data->liste->tabb);
	else if (!ft_strcmp(data->liste->tabb[0], "cd"))
		cdcall(data);
//    else if (ft_strcmp(data->tabb[0], "export") == 0 && (i = 1))
//       insertthetmp(data);
    else if (!ft_strcmp(data->liste->tabb[0], "env"))
        callallenv(data);
    else if (!ft_strcmp(data->liste->tabb[0], "setenv"))
        callsetenv(data);
    else if (!ft_strcmp(data->liste->tabb[0], "unsetenv"))
        callunsetenv(data);
    else if (!ft_strcmp(data->liste->tabb[0], "history"))
        history(data);
    return ;
}

void launch_main_fork(t_data *data)
{
	pid_t father;
	int status;

	status = 0;
	data->hist_cont = NULL;
	stock_all_heredoc(data, data->liste);
	if (!data->liste->next && is_a_builtin(data->liste->tabb[0]))
	{
		builtin_no_pipe(data);
		free_all(data, data->liste);
		return ;
	}
	else if ((father = fork()) == 0)
		main_fork(data, data->liste);
	else
		wait(&status);
	data->binreturn = status;
	free_all(data, data->liste);
}
