/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jafaghpo <jafaghpo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:54:00 by jafaghpo          #+#    #+#             */
/*   Updated: 2018/02/02 17:54:27 by jafaghpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		clear_tab(t_tab *tab)
{
	int		i;

	i = 0;
	while (i < g_lines)
	{
		free(tab[i].line);
		tab[i].line = 0;
		tab[i].ptr = 0;
		tab[i].size = 0;
		tab[i].new_line = 0;
		i++;
	}
	g_lines = 0;
}
