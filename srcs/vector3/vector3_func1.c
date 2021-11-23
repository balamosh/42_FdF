/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_func1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:18:38 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/23 06:07:03 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vector3	ft_vector3_sum2(t_vector3 a, t_vector3 b)
{
	return ((t_vector3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector3	ft_vector3_sum3(t_vector3 a, t_vector3 b, t_vector3 c)
{
	return ((t_vector3){a.x + b.x + c.x, a.y + b.y + c.y, a.z + b.z + c.z});
}

t_vector3	ft_vector3_diff(t_vector3 a, t_vector3 b)
{
	return ((t_vector3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vector3	ft_vector3_scale(double r, t_vector3 a)
{
	return ((t_vector3){r * a.x, r * a.y, r * a.z});
}
