9c9
/*   Updated: 2016/09/17 02:53:14 by cmichaud         ###   ########.fr       */
---
> /*   Updated: 2016/09/13 05:15:58 by cmichaud         ###   ########.fr       */
585d584
< 	pid_t tt;
589,597c588
< 	tt = fork();
< 	if (tt == 0)
< 	{
< 		execveremix(data);
< 		exit(0);
< 	}
< 	else
< 		wait(0);
< 	exit(0);
---
execveremix(data);
639,687d629
< 
< void   exec_loop(t_data *data, t_liste2 *liste)
< {
< 	pid_t f;
< 
< 	if (!liste->next)
< 	{
< 		main_fork_exec(data, liste, NULL, 2);
< 		exit(0);
< 	}
< 	pipe(liste->pfd);	
< 	f = fork();
< 	if (f == 0)
< 	{
< 		dup2(liste->pfd[1], 1);
< 		close(liste->pfd[0]);
< 		main_fork_exec(data, liste, NULL, 2);
< 		exit(0);
< 	}
< 	else
< 	{
< 		dup2(liste->pfd[0], 0);
< 		close(liste->pfd[1]);
< 		if (liste->next && liste->next)
< 			main_fork(data, liste->next);
< 			//	else
< 
< //			main_fork_exec
< 		exit(0);
< 	}
< 	exit(0);
< }
< 
< void   tmp_pipe(t_data *data, t_liste2 *liste)
< {
< 	pid_t f;
< 	int status;
< 
< 	status = 0;
< 	f = fork();
< 	if (f == -1)
< 		exit (-1);
< 	if (f == 0)
< 		exec_loop(data, liste);
< 	else
< 		wait4(f, &status, 0, 0);
< }
< 
< 
690,693c632,633
< 	tmp_pipe(data, liste);
< 	exit(0);
< //	pid_t father;
< //	int pfd[2];
---
> 	pid_t father;
> 	int pfd[2];
695,697c635,638
< //	ft_putstr("COMMANDE :     ");
< //	ft_putendl(liste->tabb[0]);
< //	ft_putstr("redi :     \n");
---
> 	pipe(pfd);
> 	ft_putstr("COMMANDE :     ");
> 	ft_putendl(liste->tabb[0]);
> 	ft_putstr("redi :     ");
705,737c646
< //	t_liste2 *b;
< //	b = liste;
< /*	while (liste)
< 	{
< 		
< 		liste->pid = 0;
< 		liste->pid = fork();
< 		father = fork();
< 		if (father == 0)
< 		{
< 		}
< 		else
< 		{
< 		}
< 		if (!liste->pid)
< 		{
< //			close(liste->pfd[0]);
< 			//		dup2(liste->pfd[1], 1);
< 			if (liste->next)
< 				main_fork_exec(data, liste, liste->pfd, 1);
< 			else
< 				main_fork_exec(data, liste, liste->pfd, 2);
< 			exit(0);
< 			break ;
< 		}
< 		else
< 		{
< 			close(liste->pfd[1]);
< 			dup2(liste->pfd[0], 0);
< 		}
< 		liste = liste->next;
< 	}
< 	while (b)
---
> 	if (liste->next == NULL)
739,747c648
< 		if (b->pid)
< 			waitpid(b->pid, NULL, 0);
< 		b = b->next;
< 	}
< 	exit(0);*/
< }
< /*	if (liste->next == NULL)
< 	{
< 		main_fork_exec(data, liste, NULL, 2);
---
> 		main_fork_exec(data, liste, pfd, 2);
750d650
< 	pipe(pfd);
757,774c657
< 		int iw = open("./.cacherin", O_RDWR | O_CREAT);
< 		int er;
< 		char *line;
< 		while ((er = get_next_line(0, &line)) > 0)
< 		{
< 			write(iw, line, ft_strlen(line));
< 			ft_memdel((void **)&line);
< 		}
< 		close(iw);
< 		int i = 0;
< 		while (i < 20000000)
< 			i++;
< 		i = 0;
< 		while (i < 20000000)
< 			i++;
< 		sleep(1);
< 		main_fork(data, liste->next);
< 		wait(0);
---
> 		return (main_fork(data, liste->next));
780c663
< }*/
---
> }
