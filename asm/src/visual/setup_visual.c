/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_visual.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jafaghpo <jafaghpo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 18:44:08 by jafaghpo          #+#    #+#             */
/*   Updated: 2018/02/02 19:07:35 by jafaghpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		select_mode(void)
{
	int		key;

	key = 0;
	mvprintw(LINES / 2, (COLS - 33) / 2, AUTO_MODE);
	mvprintw(LINES / 2 + 1, (COLS - 34) / 2, STEP_MODE);
	while (!key)
		key = getch();
	erase();
	if (key == '\n')
		return (DELAY_USEC);
	return (0);
}

static void		setup_color(void)
{
	start_color();
	init_pair(NC_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(NC_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(NC_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(NC_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(NC_RED, COLOR_RED, COLOR_BLACK);
}

static t_size	get_win_size(void)
{
	t_size		size;

	getmaxyx(stdscr, size.y, size.x);
	size.y -= 8;
	size.x = (size.x / 2) - 16;
	if (size.y < 0)
		size.y = 1;
	if (size.x < 0)
		size.x = 1;
	return (size);
}

int				setup_visual(t_visual *win, t_tab **tab)
{
	initscr();
	noecho();
	curs_set(0);
	setup_color();
	keypad(stdscr, TRUE);
	win->size = get_win_size();
	win->cur.x = 0;
	win->cur.y = 0;
	win->as = subwin(stdscr, LINES - 2, (COLS / 2), 2, 0);
	win->bin = subwin(stdscr, LINES - 2, (COLS / 2), 2, (COLS / 2));
	attron(COLOR_PAIR(NC_GREEN));
	mvprintw(LINES / 2, (COLS - 33) / 2, AUTO_MODE);
	mvprintw(LINES / 2 + 1, (COLS - 34) / 2, STEP_MODE);
	win->delay = select_mode();
	mvprintw(1, ((COLS / 2) - 8) / 2, "Asm file");
	mvprintw(1, ((COLS / 2) - 11) / 2 + (COLS / 2), "Binary file");
	attroff(COLOR_PAIR(NC_GREEN));
	wprintw(win->bin, "\n\n\n\t");
	box(win->as, ACS_VLINE, ACS_HLINE);
	box(win->bin, ACS_VLINE, ACS_HLINE);
	refresh();
	if (!(*tab = ft_memalloc(sizeof(**tab) * win->size.y)))
		return (print_error(strerror(errno)));
	return (1);
}
