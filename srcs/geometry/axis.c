/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:18:13 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 11:41:31 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_bool	ft_geometry_axis(t_geometry *axis)
{
	if (!ft_geometry(axis, 6, 3))
		return (false);
	ft_geometry_add_point(axis, (t_point){(t_vector3){0, 0, 0}, 0xFFFF0000});
	ft_geometry_add_point(axis, (t_point){(t_vector3){0.9, 0, 0}, 0xFFFF0000});
	ft_geometry_add_point(axis, (t_point){(t_vector3){0, 0, 0}, 0xFF00FF00});
	ft_geometry_add_point(axis, (t_point){(t_vector3){0, 0.9, 0}, 0xFF00FF00});
	ft_geometry_add_point(axis, (t_point){(t_vector3){0, 0, 0}, 0xFF0000FF});
	ft_geometry_add_point(axis, (t_point){(t_vector3){0, 0, 0.9}, 0xFF0000FF});
	ft_geometry_add_edge(axis, 0, 1);
	ft_geometry_add_edge(axis, 2, 3);
	ft_geometry_add_edge(axis, 4, 5);
	return (true);
}
