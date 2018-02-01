/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exec_proc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iburel <iburel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 16:04:48 by niragne           #+#    #+#             */
/*   Updated: 2018/02/02 00:15:41 by iburel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    exec_proc(t_proc **cycle, t_uint32 g_nb_cycle, t_proc *tmp)
{
    static void     (*f[17])() =
                    {NULL, op_live, op_ld, op_st, op_add, op_sub, op_and, op_or,
                    op_xor, op_zjmp, op_ldi, op_sti, op_fork, op_lld, op_lldi,
                    op_lfork, op_aff};
    t_uint8         op;
    t_int32         size;
    t_inst          args[4];
    char            str[CHAT_LINE_SIZE];

    op = tmp->op;
    if (op == 0 || op > 16)
    {
        tmp->pc = (tmp->pc + 1) % MEM_SIZE;
        insert_proc(cycle, tmp, (g_nb_cycle + 1) % NB_CYCLE_MAX);
        return ;
    }
    size = get_args(tmp->pc, args, op);
    if (size <= 0)
    {
        tmp->pc = (tmp->pc + -size + 1 + op_tab[op].octal) % MEM_SIZE;
        tmp->op = g_mem[tmp->pc];
        if (g_mem[tmp->pc] == 0 || g_mem[tmp->pc] > 16)
            insert_proc(cycle, tmp, (g_nb_cycle + 1) % NB_CYCLE_MAX);
        else
            insert_proc(cycle, tmp, (g_nb_cycle + op_tab[g_mem[tmp->pc]].cycles) % NB_CYCLE_MAX);
        return ;
    }

    f[op](tmp, args, cycle);
    tmp->pc = (tmp->pc + size + 1 + op_tab[op].octal) % MEM_SIZE;
    if (g_step)
    {
        ft_sprintf(str, "c %d p %d %s", g_nb_cycle, tmp->id, op_tab[op].inst);
        add_line_chat(str);
        g_pause = 1;
        g_step = 0;
    }
    tmp->op = g_mem[tmp->pc];
    if (g_mem[tmp->pc] == 0 || g_mem[tmp->pc] > 16)
        insert_proc(cycle, tmp, (g_nb_cycle + 1) % NB_CYCLE_MAX);
    else
        insert_proc(cycle, tmp, (g_nb_cycle + op_tab[g_mem[tmp->pc]].cycles) % NB_CYCLE_MAX);

}
