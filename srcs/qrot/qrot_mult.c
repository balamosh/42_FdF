/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qrot_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:18:56 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 08:33:24 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qrot.h"

t_qrot	ft_qrot_mult(t_qrot a, t_qrot b)
{
	t_qrot	q;

	if (ft_fabs(a.angle) < EPS)
		return (b);
	if (ft_fabs(b.angle) < EPS)
		return (a);
	q.angle = 2 * acos(cos(b.angle / 2) * cos(a.angle / 2) - \
						sin(b.angle / 2) * sin(a.angle / 2) * \
						ft_vector3_dot(b.axis, a.axis));
	q.axis = ft_vector3_normalize(ft_vector3_sum3(\
	ft_vector3_scale(sin(a.angle / 2) * cos(b.angle / 2), a.axis), \
	ft_vector3_scale(sin(b.angle / 2) * cos(a.angle / 2), b.axis), \
	ft_vector3_scale(sin(b.angle / 2) * sin(a.angle / 2), \
						ft_vector3_cross(b.axis, a.axis) \
	)));
	return (q);
}
