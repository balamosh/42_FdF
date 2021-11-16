/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 08:43:26 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 08:46:13 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	ft_geometry_translate(t_geometry *geo, t_vector3 v)
{
	size_t	i;

	i = 0;
	while (i < geo->npts)
	{
		geo->pts[i].p = ft_vector3_sum2(geo->pts[i].p, v);
		++i;
	}
}

void	ft_geometry_scale(t_geometry *geo, t_vector3 v)
{
	size_t	i;

	i = 0;
	while (i < geo->npts)
	{
		geo->pts[i].p = (t_vector3){geo->pts[i].p.x * v.x, \
									geo->pts[i].p.y * v.y, \
									geo->pts[i].p.z * v.z};
		++i;
	}
}
