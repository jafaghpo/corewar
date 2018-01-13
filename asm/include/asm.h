/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jafaghpo <jafaghpo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:38:13 by iburel            #+#    #+#             */
/*   Updated: 2018/01/13 01:13:30 by jafaghpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
**	-- Includes --
*/
# include <ncurses.h>
# include <errno.h>
# include "libft.h"
# include "op.h"
# include "eval_expr.h"
/*
**	-- Error messages --
*/
# define NO_PARAMETER			"missing parameters\n%s"	
# define USAGE					"usage: ./asm [-wv] file ..."
# define EXTENSION				"invalid file extension: \033[31m%s"
# define OPTION					"illegal option -- \033[31m%c\033[0m\n%s"
# define UNKNOWN_FILE			"\033[31m%s: \033[0m%s"
# define NO_NAME				"missing champion name"
# define NO_COMMENT				"missing champion comment"
# define SYNTAX					"invalid syntax: \033[31m%s\033[0m"
# define HEADER_LINE			"invalid line in champion header: \033[31m%s\033[0m"
# define LABEL_SYNTAX			"invalid label syntax: \033[31m%s\033[0m"
# define UNKNOWN_INST			"unknown instruction: \033[31m%s\033[0m"
/*
**	-- Option masks --
*/
# define VISUAL_FLAG			0x01
# define SIZE_FLAG				0x02
/*
**	-- Length macros --
*/
# define TAB_SIZE				1000
# define NAME_LEN				PROG_NAME_LENGTH
# define COM_LEN				COMMENT_LENGTH
# define HEADER_LEN				(NAME_LEN + COM_LEN + 16)
/*
**	-- Typedefs --
*/
typedef uint8_t			t_uint8;
typedef struct s_tab	t_tab;
typedef struct s_buf	t_buf;
typedef struct s_tmplb	t_tmplb;
typedef struct s_lstlb	t_lstlb;
typedef struct s_label	t_label;
/*
**	-- Structures --
*/
struct		s_tab
{
	char	*line;
	t_uint8	*ptr;
	int		size;
	int		new_line;
};

struct		s_buf
{
	t_uint8	*data;
	int		size;
	int		i;
};

struct		s_tmplb
{
	char	*name;
	int		cursor;
	int		size;
	int		rel;
	t_tmplb	*next;
};

struct		s_lstlb
{
	char	*name;
	int		addr;
	t_lstlb	*next;
};

struct		s_label
{
	t_tmplb	*tmp;
	t_lstlb	*lst;
};
/*
**	-- Global variables --
*/
extern	int		g_lines;
extern	int		g_option;
extern	t_buf	g_bin;
extern	t_op	g_op[17];
/*
**	-- General --
*/
int			print_error(const char *msg, ...);
char		*get_name(char *file);
int			fill_binary(char *name);
int			word_equal(char *s1, char *s2);
int			word_len(char *str);
int			get_opcode(char *line, int *op);
void		add_instruction(char *inst, int len);
/*
**	-- Parsing --
*/
int			parse_file(char *name);
int			get_header(t_tab *tab, int fd);
int			get_instructions(t_tab *tab, t_label *label, int fd);
int			store_line(t_tab *tab, t_tab *current);
int			parse_arguments(char *line, t_label *label, char *inst);
/*
**	-- Labels --
*/
int			valid_label(char *str);
int			check_labels(t_label *label);
t_lstlb		*add_label(t_lstlb *label, char *name, int size);
char		*duplicate_label(char *name, int size);
/*
**	-- Visual --
*/
void		run_visual(t_tab *tab);

#endif
