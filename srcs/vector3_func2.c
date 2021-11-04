/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:58:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/04 14:01:23 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

double		ft_vector3_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	ft_vector3_cross(t_vector3 a, t_vector3 b)
{
	return (ft_vector3(a.y * b.z - a.z * b.y, \
						a.z * b.x - a.x * b.z, \
						a.x * b.y - a.y * b.x));
}
