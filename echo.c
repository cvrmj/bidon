/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 21:10:55 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/02 14:32:27 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		convert_nb(int nb, int b)
{
	int len;
	int n;

	n = 0;
	len = 1;
	while (nb)
	{
		n += (nb % 10) * len;
		nb /= 10;
		len *= b;
	}
	return (n);
}

int		ft_atoi_base(char *str, int b)
{
	char	*tmp;
	int		nb;
	int		len;

	nb = 0;
	if (!str)
		return (0);
	tmp = str;
	len = 0;
	while ((*str >= '0' && *str <= '9') && str && len < 3)
	{
		len++;
		nb += *str - '0';
		str++;
		if ((*str >= '0' && *str <= '9') && str)
			nb *= 10;
	}
	if (nb == 0)
		return (0);
	return (convert_nb(nb, b));
}

void	cond_spec_char(char *str)
{
	*str == 'a' ? write(1, "\a", 1) : *str;
	*str == 'b' ? write(1, "\b", 1) : *str;
	*str == 'f' ? write(1, "\f", 1) : *str;
	*str == 'n' ? write(1, "\n", 1) : *str;
	*str == 'r' ? write(1, "\r", 1) : *str;
	*str == 't' ? write(1, "\t", 1) : *str;
	*str == 'v' ? write(1, "\v", 1) : *str;
}

/*
If lex-pars change the syntax of \, remove the first if and the (++) of *(++str) != a
*/

char	*special_char_hndlr(char *str)
{
	int n;

	n = 0;
//	if (*str != '\\' || !(str + 1))
//		return (str);
	if (*(/*++*/str) != 'a' && *str != 'b' && *str != 'c' && *str != 'f' &&
		*str != 'n' && *str != 'r' && *str != 't' && *str != 'v' && *str != '0')
	{
		ft_putstr("\\");
		return (++str);
	}
	if (*str == 'c')
		return (NULL);
	if (*str == '0')
	{
		ft_putchar(ft_atoi_base(++str, 8));
		while (str++ && (*str >= '0' && *str <= '9') && n < 3)
			n++;
	}
	cond_spec_char(str);
	return (++str);
}

void	builtin_echo(char *str)
{
	while (str && *str)
	{
		if (*str != '\\')
			write(1, str++, 1);
		else if (++str)
			if (!(str = special_char_hndlr(str)))
				return ;
	}
}

void	callecho(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		builtin_echo(args[i]);
		if (args[i] + 1)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
