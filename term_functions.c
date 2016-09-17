/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 10:23:04 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/17 04:58:37 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			term_init(t_term *term)
{
	if (!isatty(0))
		return (-1);
	if ((term->term_name = "xterm-256color") == NULL)
		return (-1);
	if (tgetent(NULL, term->term_name) < 1)
		return (-1);
	tcgetattr(0, &(term->term));
	tcgetattr(0, &term->term_copy);
	term->term.c_lflag &= ~(ICANON);
	term->term.c_lflag &= ~(ECHO);
	term->term.c_cc[VMIN] = 1;
	term->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &(term->term));
	g_shell.term_reset = *term;
	return (1);
}

int			tputs_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int			ft_reset_term(struct termios term)
{
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	return (0);
}
