/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 08:03:02 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 10:55:36 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_fdf_geo_color(t_geometry *geo, double min, double max)
{
	size_t	i;
	int		cd;

	i = 0;
	while (i < geo->npts)
	{
		if (ft_fabs(geo->pts[i].p.y) < EPS)
			cd = 0xFFFFFFFF;
		else if (geo->pts[i].p.y >= max / 2)
			cd = ft_color_lerp(0xFF00FF00, 0xFFFF0000, \
			(2 * geo->pts[i].p.y - max) / max);
		else if (geo->pts[i].p.y >= 0)
			cd = ft_color_lerp(0xFFFFFFFF, 0xFF00FF00, \
			(2 * geo->pts[i].p.y) / max);
		else
			cd = ft_color_lerp(0xFFFFFFFF, 0xFF0000FF, geo->pts[i].p.y / min);
		geo->pts[i].cd = cd;
		++i;
	}
}

static void	ft_fdf_geo_fit(t_geometry *geo, t_geometry *bbox)
{
	size_t		i;
	double		max;
	double		curr;
	t_vector3	offset;

	max = ft_fabs(geo->pts[geo->edges[0].ptid[0]].p.y - \
					geo->pts[geo->edges[0].ptid[1]].p.y);
	i = 1;
	while (i < geo->nedges)
	{
		curr = ft_fabs(geo->pts[geo->edges[i].ptid[0]].p.y - \
					geo->pts[geo->edges[i].ptid[1]].p.y);
		if (curr > max)
			max = curr;
		++i;
	}
	if (max > 1)
	{
		ft_geometry_scale(geo, (t_vector3){1, 1 / max, 1});
		ft_geometry_scale(bbox, (t_vector3){1, 1 / max, 1});
	}
	offset = (t_vector3){(bbox->pts[0].p.x - bbox->pts[7].p.x) / 2, 0, \
				(bbox->pts[0].p.z - bbox->pts[7].p.z) / 2};
	ft_geometry_translate(geo, offset);
	ft_geometry_translate(bbox, offset);
}

t_bool	ft_fdf_geo_init(t_geometry *geo, t_geometry *bbox, char *filename)
{
	if (!(ft_fdf_geo_read(geo, filename) && ft_geometry_bbox(bbox, geo)))
		return (false);
	ft_fdf_geo_color(geo, bbox->pts[0].p.y, bbox->pts[7].p.y);
	ft_fdf_geo_fit(geo, bbox);
	return (true);
}
