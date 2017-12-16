/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jafaghpo <jafaghpo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:06:51 by jafaghpo          #+#    #+#             */
/*   Updated: 2017/12/16 23:31:51 by jafaghpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disas.h"

int			print_error(char *msg)
{
	if (!msg)
		ft_printf("%fd%s: %s\n", 2, EXEC_NAME, strerror(errno));
	else
		ft_printf("%fd%s: %s\n", 2, EXEC_NAME, msg);
	return (0);
}

int			main(int ac, char **av)
{
	t_file	file;
	int		i;

	if (ac < 2)
	{
		ft_printf(USAGE, av[0]);
		return (0);
	}
	i = 1;
	while (av[i])
	{
		if (!get_binary(&file, av[i]))
			continue ;
		if (!parse_file(&file))
			;
		free(file.path);
		free(file.prog);
		i++;
	}
	ft_strdel(&g_buf);
	return (0);
}
