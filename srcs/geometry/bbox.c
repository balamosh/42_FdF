/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 05:58:05 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 06:36:46 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

static t_bool	ft_bbox_from_corners(t_geometry *bbox, \
										t_vector3 pt1, t_vector3 pt2)
{
	if (!ft_geometry(bbox, 8, 12))
		return (false);
	ft_geometry_add_point(bbox, (t_point){pt1, 0});
	ft_geometry_add_point(bbox, (t_point){(t_vector3){pt2.x, pt1.y, pt1.z}, 0});
	ft_geometry_add_point(bbox, (t_point){(t_vector3){pt1.x, pt2.y, pt1.z}, 0});
	ft_geometry_add_point(bbox, (t_point){(t_vector3){pt1.x, pt1.y, pt2.z}, 0});
	ft_geometry_add_point(bbox, (t_point){(t_vector3){pt1.x, pt2.y, pt2.z}, 0});
	ft_geometry_add_point(bbox, (t_point){(t_vector3){pt2.x, pt1.y, pt2.z}, 0});
	ft_geometry_add_point(bbox, (t_point){(t_vector3){pt2.x, pt2.y, pt1.z}, 0});
	ft_geometry_add_point(bbox, (t_point){pt2, 0});
	ft_geometry_add_edge(bbox, 0, 1);
	ft_geometry_add_edge(bbox, 0, 3);
	ft_geometry_add_edge(bbox, 5, 1);
	ft_geometry_add_edge(bbox, 5, 3);
	ft_geometry_add_edge(bbox, 7, 4);
	ft_geometry_add_edge(bbox, 7, 6);
	ft_geometry_add_edge(bbox, 2, 4);
	ft_geometry_add_edge(bbox, 2, 6);
	ft_geometry_add_edge(bbox, 0, 2);
	ft_geometry_add_edge(bbox, 1, 6);
	ft_geometry_add_edge(bbox, 7, 5);
	ft_geometry_add_edge(bbox, 3, 4);
	return (true);
}

t_bool	ft_geometry_bbox(t_geometry *bbox, t_geometry *geo)
{
	t_vector3	pt_min;
	t_vector3	pt_max;
	size_t		i;

	pt_min = geo->pts[0].p;
	pt_max = geo->pts[0].p;
	i = 1;
	while (i < geo->npts)
	{
		pt_min = (t_vector3){ft_fmin(pt_min.x, geo->pts[i].p.x), \
							ft_fmin(pt_min.y, geo->pts[i].p.y), \
							ft_fmin(pt_min.z, geo->pts[i].p.z)};
		pt_max = (t_vector3){ft_fmax(pt_max.x, geo->pts[i].p.x), \
							ft_fmax(pt_max.y, geo->pts[i].p.y), \
							ft_fmax(pt_max.z, geo->pts[i].p.z)};
		++i;
	}
	return (ft_bbox_from_corners(bbox, pt_min, pt_max));
}
