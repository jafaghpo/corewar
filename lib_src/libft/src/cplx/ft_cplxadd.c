/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cplxadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:08:48 by iburel            #+#    #+#             */
/*   Updated: 2017/12/17 19:24:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cplx.h"

t_cplx	ft_cplxadd(t_cplx z1, t_cplx z2)
{
	t_cplx	ret;

	ret.re = z1.re + z2.re;
	ret.im = z1.im + z2.im;
	return (ret);
}
