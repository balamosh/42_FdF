/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:51:02 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 10:56:21 by sotherys         ###   ########.fr       */
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

t_bool	ft_fdf_geo_read(t_geometry *geo, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (read(fd, NULL, 0) == -1 || !ft_fdf_geo_alloc(geo, fd))
	{
		close(fd);
		return (false);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (read(fd, NULL, 0) == -1 || !ft_fdf_geo_fill(geo, fd))
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
