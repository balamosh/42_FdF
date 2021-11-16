/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 08:03:02 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 10:30:30 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

static t_bool	ft_fdf_geo_alloc(t_geometry *geo, int fd)
{
	char	*line;
	size_t	curr;
	size_t	prev;

	geo->spts = 0;
	geo->sedges = 0;
	prev = 0;
	line = get_next_line(fd);
	while (line)
	{
		curr = ft_split_word_count(line, ' ');
		geo->spts += curr;
		if (curr)
			geo->sedges += curr - 1 + ft_min(curr, prev);
		prev = curr;
		line = get_next_line(fd);
	}
	return (ft_geometry(geo, geo->spts, geo->sedges));
}

static t_bool	ft_fdf_geo_fill(t_geometry *geo, int fd)
{
	char		**nbrs;
	t_vector3	pt;
	int			prev;

	prev = 0;
	pt.z = 0;
	nbrs = ft_split(get_next_line(fd), ' ');
	while (nbrs)
	{
		pt.x = 0;
		while (nbrs[(int) pt.x])
		{
			pt.y = ft_atoi(nbrs[(int) pt.x]);
			ft_geometry_add_point(geo, (t_point){pt, 0});
			if (pt.x > 0)
				ft_geometry_add_edge(geo, geo->npts - 1, geo->npts - 2);
			if (pt.z > 0 && pt.x < prev)
				ft_geometry_add_edge(geo, geo->npts - 1, geo->npts - prev - 1);
			++pt.x;
		}
		prev = pt.x;
		++pt.z;
		nbrs = ft_split(get_next_line(fd), ' ');
	}
	return (geo->npts == geo->spts && geo->nedges == geo->sedges);
}

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
	int	fd;

	fd = open(filename, O_RDONLY);
	if (read(fd, NULL, 0) == -1 || !ft_fdf_geo_alloc(geo, fd))
		return (false);
	close (fd);
	fd = open(filename, O_RDONLY);
	if (read(fd, NULL, 0) == -1 || !ft_fdf_geo_fill(geo, fd))
		return (false);
	close (fd);
	if (!ft_geometry_bbox(bbox, geo))
		return (false);
	ft_fdf_geo_color(geo, bbox->pts[0].p.y, bbox->pts[7].p.y);
	ft_fdf_geo_fit(geo, bbox);
	return (true);
}
