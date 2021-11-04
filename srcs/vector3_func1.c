/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_func1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:18:38 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/04 13:57:56 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vector3	ft_vector3(double x, double y, double z)
{
	t_vector3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector3	ft_vector3_add(t_vector3 a, t_vector3 b)
{
	return (ft_vector3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vector3	ft_vector3_sub(t_vector3 a, t_vector3 b)
{
	return (ft_vector3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vector3	ft_vector3_scale(double r, t_vector3 a)
{
	return (ft_vector3(r * a.x, r * a.y, r * a.z));
}

double	ft_vector3_len(t_vector3 a)
{
	return (sqrt(ft_vector3_dot(a, a)));
}
