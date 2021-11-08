/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:58:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/08 12:58:23 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

double	ft_vector3_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	ft_vector3_cross(t_vector3 a, t_vector3 b)
{
	return (ft_vector3(a.y * b.z - a.z * b.y, \
						a.z * b.x - a.x * b.z, \
						a.x * b.y - a.y * b.x));
}

double	ft_vector3_len(t_vector3 a)
{
	return (sqrt(ft_vector3_dot(a, a)));
}

t_vector3	ft_vector3_normalize(t_vector3 a)
{
	return (ft_vector3_scale(1 / ft_vector3_len(a), a));
}
