/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qrot_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:18:56 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 08:33:24 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qrot.h"

t_vector3	ft_qrot_rotate(t_vector3 pt, t_qrot q)
{
	if (ft_fabs(q.angle) < EPS)
		return (pt);
	return (\
	ft_vector3_sum3(\
		ft_vector3_scale(cos(q.angle), pt), \
		ft_vector3_scale(sin(q.angle), ft_vector3_cross(q.axis, pt)), \
		ft_vector3_scale((1 - cos(q.angle)) * ft_vector3_dot(q.axis, pt), \
							q.axis) \
	));
}
