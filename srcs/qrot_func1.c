/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qrot_func1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 00:21:06 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/07 06:58:40 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qrot.h"

t_qrot	ft_qrot(t_vector3 axis, double angle)
{
	t_qrot	q;

	q.axis = axis;
	q.angle = angle;
	return (q);
}

/*
t_qrot	ft_qrot_mult(t_qrot a, t_qrot b)
{
	t_qrot	q;

	if (a.angle > -0.01 && a.angle < 0.01)
		return (b);
	if (b.angle > -0.01 && b.angle < 0.01)
		return (a);
	a.axis = ft_vector3_normalize(a.axis);
	b.axis = ft_vector3_normalize(b.axis);
	q.angle = 2 * acos(cos(b.angle / 2) * cos(a.angle / 2) - \
						sin(b.angle / 2) * sin(a.angle / 2) * \
						ft_vector3_dot(b.axis, a.axis));
	q.axis = ft_vector3_normalize(ft_vector3_sum3(\
	ft_vector3_scale(sin((b.angle + a.angle) / 2) + \
					sin((b.angle - a.angle) / 2), \
					a.axis), \
	ft_vector3_scale(sin((b.angle + a.angle) / 2) - \
					sin((b.angle - a.angle) / 2), \
					b.axis), \
	ft_vector3_scale(cos((b.angle - a.angle) / 2) - \
					cos((b.angle + a.angle) / 2), \
					ft_vector3_cross(b.axis, a.axis) \
	)));
	return (q);
}
*/


t_qrot	ft_qrot_mult(t_qrot a, t_qrot b)
{
	t_qrot	q;

	if (a.angle > -0.01 && a.angle < 0.01)
		return (b);
	if (b.angle > -0.01 && b.angle < 0.01)
		return (a);
	a.axis = ft_vector3_normalize(a.axis);
	b.axis = ft_vector3_normalize(b.axis);
	q.angle = 2 * acos(cos(b.angle / 2) * cos(a.angle / 2) - \
						sin(b.angle / 2) * sin(a.angle / 2) * \
						ft_vector3_dot(b.axis, a.axis));
	q.axis = ft_vector3_normalize(ft_vector3_sum3(\
	ft_vector3_scale(sin(a.angle / 2) * \
					cos(b.angle / 2), \
					a.axis), \
	ft_vector3_scale(sin(b.angle / 2) * \
					cos(a.angle / 2), \
					b.axis), \
	ft_vector3_scale(sin(b.angle / 2) * \
					sin(a.angle / 2), \
					ft_vector3_cross(b.axis, a.axis) \
	)));
	return (q);
}


/*
t_qrot	ft_qrot_mult(t_qrot a, t_qrot b)
{
	t_qrot	q;

	a.axis = ft_vector3_normalize(a.axis);
	b.axis = ft_vector3_normalize(b.axis);
	if (a.angle > -0.01 && a.angle < 0.01)
		return (b);
	if (b.angle > -0.01 && b.angle < 0.01)
		return (a);
	q.angle = acos(cos(a.angle) * cos(b.angle) - \
					ft_vector3_dot(ft_vector3_scale(sin(a.angle), a.axis), \
									ft_vector3_scale(sin(b.angle), b.axis)));
	q.axis = ft_vector3_normalize(ft_vector3_sum3(\
	ft_vector3_scale(cos(a.angle) * sin(b.angle), b.axis), \
	ft_vector3_scale(cos(b.angle) * sin(a.angle), a.axis), \
	ft_vector3_cross(ft_vector3_scale(sin(a.angle), a.axis), \
					ft_vector3_scale(sin(b.angle), b.axis))\
	));
	return (q);
}
*/

/*
t_vector3	ft_qrot_rotate(t_vector3 pt, t_qrot q)
{
	if (q.angle  > -0.01 && q.angle < 0.01)
		return (pt);
	q.axis = ft_vector3_normalize(q.axis);
	return (\
	ft_vector3_sum3(\
		ft_vector3_scale(cos(q.angle), \
			ft_vector3_diff(pt, \
				ft_vector3_scale(ft_vector3_dot(q.axis, pt), q.axis))), \
		ft_vector3_scale(sin(q.angle), \
			ft_vector3_cross(q.axis, pt)), \
		ft_vector3_scale(ft_vector3_dot(q.axis, pt), q.axis) \
	));
}
*/

t_vector3	ft_qrot_rotate(t_vector3 pt, t_qrot q)
{
	if (q.angle  > -0.01 && q.angle < 0.01)
		return (pt);
	q.axis = ft_vector3_normalize(q.axis);
	return (\
	ft_vector3_sum3(\
		ft_vector3_scale(cos(q.angle), pt), \
		ft_vector3_scale(sin(q.angle), ft_vector3_cross(q.axis, pt)), \
		ft_vector3_scale((1 - cos(q.angle)) * ft_vector3_dot(q.axis, pt), q.axis)\
	));
}
