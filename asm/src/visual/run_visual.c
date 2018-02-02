/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_visual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jafaghpo <jafaghpo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 22:09:40 by jafaghpo          #+#    #+#             */
/*   Updated: 2018/02/02 19:07:01 by jafaghpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		wait_event(int delay)
{
	int			key;

	if (delay)
		usleep(delay);
	else
	{
		key = 0;
		while (key != ' ')
		{
			key = getch();
			if (key == 27)
			{
				endwin();
				exit(1);
			}
		}
	}
}

static void		set_attribute(t_visual *win, char *status)
{
	static int	color = 1;

	if (color > 4)
		color = 1;
	if (!ft_strcmp(status, "ON"))
		wattron(win->bin, COLOR_PAIR(color));
	else
	{
		wattroff(win->bin, COLOR_PAIR(color));
		color++;
	}
}

static void		display_bin(t_tab *tab, t_visual *win, int line)
{
	int				i;

	i = -1;
	set_attribute(win, "ON");
	while (++i < tab[line].size)
	{
		if (win->cur.x >= win->size.x)
		{
			wprintw(win->bin, "\n\t");
			win->cur.x = 0;
			win->cur.y++;
		}
		if (win->cur.y >= win->size.y)
		{
			werase(win->bin);
			wprintw(win->bin, "\n\n\n\t");
			win->cur.y = 0;
			win->cur.x = 0;
		}
		wprintw(win->bin, "%.2X ", tab[line].ptr[i]);
		win->cur.x += 3;
	}
	set_attribute(win, "OFF");
	box(win->bin, ACS_VLINE, ACS_HLINE);
}

static void		display_asm(t_tab *tab, t_visual *win, int line)
{
	int		i;

	i = 0;
	werase(win->as);
	wprintw(win->as, "\n\n\n\t");
	wattron(win->as, COLOR_PAIR(NC_BLACK) | A_BOLD);
	while (i < g_lines)
	{
		if (i == line)
		{
			wattron(win->as, COLOR_PAIR(NC_YELLOW));
			wprintw(win->as, "%s", tab[i].line);
			wattroff(win->as, COLOR_PAIR(NC_YELLOW));
		}
		else
			wprintw(win->as, "%s", tab[i].line);
		wprintw(win->as, "\n\t");
		i++;
	}
	box(win->as, ACS_VLINE, ACS_HLINE);
}

void			run_visual(t_tab *tab, t_visual *win)
{
	int		line;

	line = 0;
	while (line < g_lines)
	{
		wait_event(win->delay);
		display_asm(tab, win, line);
		display_bin(tab, win, line);
		wrefresh(win->as);
		wrefresh(win->bin);
		line++;
	}
	clear_tab(tab);
}
