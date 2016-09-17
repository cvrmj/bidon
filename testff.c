/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 05:01:52 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/16 05:08:50 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int main(void)
{
	pid_t father;

	father = fork();
	if (father == 0)
	{
		sleep(4);
		exit(0);
	}
	else
	{
		long i = 0;
		while (++i)
		{
			if (i > 200999999)
				break;
			ft_putnbr(father);
			write(0, "trololo\n", 15);
		}
		wait(0);
	}
	return (0);
}
