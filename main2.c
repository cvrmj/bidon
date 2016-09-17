/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/17 06:18:50 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			exit_func(t_data *data, t_liste *liste)
{
	get_tabhash(NULL, 1);
	if (data->home)
		free(data->home);
	if (data->oldpwd)
		free(data->oldpwd);
	free(data->line);
//	freetab(data->args);
	free_list(liste);
	exit(0);
}

int				is_not_spec(char *str)
{
	int i;

	i = -1;
	if (!ft_strcmp(str, "||"))
		return (0);
	if (!ft_strcmp(str, "&&"))
		return (0);
	if (!ft_strcmp(str, "|"))
		return (0);
	if (!ft_strcmp(str, "<"))
		return (0);
	if (!ft_strcmp(str, "<<"))
		return (0);
	return (1);
}

void			find_exit(t_data *data, int i, char *tmp)
{
	while (data->args[i])
		++i;
	--i;
	while (i > 0 && is_not_spec(data->args[i - 1]))
		i--;
	if (!ft_strcmp(data->args[i], "exit"))
	{
		data->exit = 1;
		i++;
		if (data->exit_line != NULL)
			ft_memdel((void **)&data->exit_line);
		if (data->args[i] && is_not_spec(data->args[i]))
			data->exit_line = ft_strdup(data->args[i++]);
		while (data->args[i] && is_not_spec(data->args[i]))
		{
			tmp = data->exit_line;
			data->exit_line = ft_strjoin(data->exit_line, " ");
			free(tmp);
			tmp = data->exit_line;
			data->exit_line = ft_strjoin(data->exit_line, data->args[i]);
			free(tmp);
			i++;
		}
	}
}

int				search_nb_pipe(t_tk *tk)
{
	int nb;

	nb = 0;
	while (tk)
	{
		if (!tk->tk && !tk->arg[1] && tk->arg[0] == '|')
			++nb;
		tk = tk->next;
	}
	ft_putstr("\n\n\n\\n\nnbnbnbnnbbn    ");
	ft_putnbr(nb);
	return (nb);
}

int				is_a_sepp(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
	}
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		return (1);
	return (0);
}

char			**get_arg(t_tk **tk, char **tabb)
{
	t_tk *t;
	int	i;

	i = 0;
	t = *tk;
	while (t)
	{
		if ((++i) && !t->tk && is_a_sepp(t->arg))
			break ;
		t = t->next;
	}
	t = *tk;
	tabb = (char **)malloc(sizeof(char *) * (i + 1));
	tabb[i] = NULL;
	i = -1;
	while (t && !(!t->tk && is_a_sepp(t->arg)))
	{
		tabb[++i] = ft_strdup(t->arg);
		t = t->next;
	}
	tabb[++i] = NULL;
	*tk = t;
	return (tabb);
}

int				choose_redi(char *str, t_lfd *fd, t_lfd *b)
{
	int i;
	int nb;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i)
	{
		nb = ft_atoi(str);
		while (fd)
		{
			if (nb == fd->fd)
				nb = -1;
			if (!fd->next)
				break ;
			fd = fd->next;
		}
		if (nb != -1)
		{
			fd->next = (t_lfd *)malloc(sizeof(t_lfd));
			fd->next->next = NULL;
			fd->next->fd = nb;
			fd->next->open = 0;
			fd->next->read = 0;
			fd->next->write = 0;
		}
		fd = b;
	}
	if (*(str + i) == '>')
	{
		if (!*(str + i + 1))
			return (1);
		if (*(str + i + 1) == '>')
			return (2);
		if (*(str + i + 1) == '&')
		{
			if (*(str + i + 2) && ft_isdigit(*(str + i + 2)))
			{
				nb = ft_atoi(str + i + 2);
				ft_putnbr(nb);
				while (fd)
				{
					if (nb == fd->fd)
						nb = -1;
					if (!fd->next)
						break ;
					fd = fd->next;
				}
				if (nb != -1)
				{
					fd->next = (t_lfd *)malloc(sizeof(t_lfd));
					fd->next->next = NULL;
					fd->next->fd = nb;
					fd->next->open = 0;
					fd->next->read = 0;
					fd->next->write = 0;
				}
				fd = b;
			}
			return (5);
		}	
	}
	if (*(str + i) == '<' && !*(str + i + 1))
		return (3);
	if (*(str + i) == '<' && *(str + i + 1) == '<')
		return (4);
	return (0);
}

t_lredi			*get_redir(t_tk **tk, t_lredi *redi, t_lfd *fd)
{
	t_tk	*t;
	t_lredi	*b;

	t = *tk;
	redi = (t_lredi *)malloc(sizeof(t_lredi));
	b = redi;
	while (t && !(!t->tk && t->arg[0] == '|' && !t->arg[1]))
	{
		redi->str = ft_strdup(t->arg);
		if (t->tk)
			redi->redi = 0;
		else
			redi->redi = choose_redi(t->arg, fd, fd);
		t = t->next;
		if (!(t && !(!t->tk && t->arg[0] == '|' && !t->arg[1])))
			break ;
		redi->next = (t_lredi *)malloc(sizeof(t_lredi));
		redi = redi->next;
	}
	*tk = t;
	redi->next = NULL;
	return (b);
}

t_lfd			*init_fd(t_lfd *fd, t_lfd *base)
{
	fd = (t_lfd *)malloc(sizeof(t_lfd));
	base = fd;
	fd->fd = 0;
	fd->open = 1;
	fd->write = 1;
	fd->read = 0;
	fd->next = (t_lfd *)malloc(sizeof(t_lfd));
	fd = fd->next;
	fd->open = 1;
	fd->write = 0;
	fd->read = 1;
	fd->fd = 1;
	fd->next = (t_lfd *)malloc(sizeof(t_lfd));
	fd = fd->next;
	fd->fd = 2;
	fd->open = 1;
	fd->write = 1;
	fd->read = 0;
	fd->next = NULL;
	return (base);
}

t_liste2		*final_list(t_liste2 *dest, t_tk *tk)
{
	int nb_pipe;
	t_liste2 *base;

	dest = (t_liste2 *)malloc(sizeof(t_liste2));
	base = dest;
	nb_pipe = search_nb_pipe(tk) + 1;
	while (nb_pipe--)
	{
		dest->fd = init_fd(NULL, NULL);
		dest->tabb = get_arg(&tk, NULL);
		if (tk && !(!tk->tk && tk->arg[0] == '|' && !tk->arg[1]))
			dest->redir = get_redir(&tk, NULL, dest->fd);
		else
			dest->redir = NULL;
		if (tk)
			tk = tk->next;
		if (nb_pipe)
		{
			dest->next = (t_liste2 *)malloc(sizeof(t_liste2));
			dest = dest->next;
			dest->next = NULL;
		}
	}
	dest->next = NULL;
	return (base);
}

void			parsecommand(t_data *data, t_liste *liste)
{
	t_tk *t;
	t_lredi *r;
	t_lfd *f;
	t_liste2 *l;

	(void)liste;
	data->l = nsplit_on_inib(data->line);
	t = data->l;
    while (t)
    {
		ft_putnbr(t->tk);
		ft_putstr("   ");
		ft_putendl(t->arg);
		t = t->next;
	}
	t = data->l;
	data->liste = final_list(NULL, data->l);
	l = data->liste;
	int i = -1;
	while (l)
	{
		i = -1;
		ft_putendl("LINE :\n\n\n");
		while (l->tabb[++i])
		{
			ft_putstr("              ");
			ft_putendl(l->tabb[i]);
		}
		r = l->redir;
		while (r)
		{
			ft_putstr("REDI : ");
			ft_putnbr(r->redi);
			ft_putstr(" ARG : ");
			ft_putendl(r->str);
			r = r->next;
		}
		f = l->fd;
		while (f)
		{
			ft_putstr("FD : ");
			ft_putnbr(f->fd);
			ft_putstr(" open : ");
			ft_putnbr(f->open);
			ft_putstr(" write : ");
			ft_putnbr(f->write);
			ft_putstr(" read : ");
			ft_putnbr(f->read);
			ft_putendl("");
			f = f->next;
		}
		l = l->next;
	}
	launch_main_fork(data);}
/*	if (data->line[0] == '\0')
	{
		data->dspam = 1;
		return ;
	}
	if (!(data->args = split_on_inib(data->line)))
	{
	    data->binreturn = 255;
		return ;
	}
	int i = -1;
	ft_putendl("TAB OF ARGS :\n");
	while (data->args[++i])
	{
		ft_putstr("args : ");
		ft_putendl(data->args[i]);
	}
	data->l = nsplit_on_inib(data->line);
	t_tk *t = data->l;
	ft_putendl("LIST OF ARGS :\n");
	while (data->l)
	{
		ft_putstr("tk : ");
		ft_putnbr(data->l->tk);
		ft_putstr("  list : ");
		ft_putendl(data->l->arg);
		data->l = data->l->next;
	}
	data->l = t;
	find_exit(data, 0, NULL);
	sub_parsecommand(data, 0);
	// ft_putstr("valeur de retour: ");
	// ft_putnbr(data->binreturn);
	// ft_putstr("\n");

	}*/

int				switch_case(t_tk *ptr, int nb_redir, int nb_redir2)
{
	if (ptr->tk == 3 && ft_strncmp(ptr->arg, "|", 1) != 0 && ptr->next == NULL)
	{
		ft_putendl("Missing name for redirect.");
		return (-1);
	}
	else if (nb_redir > 1 || nb_redir2 > 1)
	{
		ft_putendl("Ambigous output redirect.");
		return (-1);
	}
	else if (ptr->tk == 3 && ft_strncmp(ptr->arg, "|", 1) == 0
	&& ptr->next == NULL)
	{
		ft_putendl("Invalid null command.");
		return (-1);
	}
	return (0);
}
