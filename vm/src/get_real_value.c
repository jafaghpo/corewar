/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:00:26 by niragne           #+#    #+#             */
/*   Updated: 2017/12/01 16:40:23 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_int32                   get_void_value(t_int32 mdr, t_proc *p)
{
    (void)mdr;
    (void)p;
    return (0);
}

static t_int32     get_reg_value(t_int32 val, t_proc *p)
{
    return (p->reg[val - 1]);
}

static t_int32      get_dir_value(t_int32 dir, t_proc *p)
{
    (void)p;
    return (dir);
}

static t_int32 get_ind_value(t_int32 ind, t_proc *p, t_uint8 mod)
{
    t_int32 ret;

    ret = get_uint32_mem(p->pc + ind % (IDX_MOD * mod));
    return ((t_int32)ret);
}

t_int32     get_real_value(t_inst *args, t_proc *p, t_uint8 mod)
{
    static t_int32  (*f[4])() = {get_void_value, get_reg_value, get_dir_value,
    (t_int32 (*)())get_ind_value};
    
    return (f[args[0].type](args[0].value, p, mod));
}