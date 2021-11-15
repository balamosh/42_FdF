/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:03:34 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 08:26:12 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

static t_bool	ft_mlx_init(void **mlx)
{
	*mlx = mlx_init();
	if (!*mlx)
		return (false);
	return (true);
}

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

void	ft_fdf_geo_color(t_geometry *geo, double min, double max)
{
	size_t	i;
	int		cd;

	i = 0;
	while (i < geo->npts)
	{
		cd = 0x00FF0000 * (geo->pts[i].p.y - min) / (max - min) + 0x000000FF;
		geo->pts[i].cd = cd;
		++i;
	}
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
	return (true);
}

t_bool	ft_fdf_images_init(t_image *image, void *mlx, int width, int height)
{
	size_t	i;

	i = 0;
	while (i < FDF_TMP_IMG)
	{
		if (!ft_image(&image[i++], mlx, width, height))
			return (false);
	}
	return (true);
}

t_bool	ft_fdf_init(t_fdf *tab)
{
	if (!(ft_fdf_geo_init(&tab->geo, &tab->bbox, tab->filename) \
		&& ft_mlx_init(&tab->mlx) \
		&& ft_window(&tab->window, tab->mlx, \
						(t_res){FDF_WINDOW_WIDTH, FDF_WINDOW_HEIGHT}, "fdf") \
		&& ft_fdf_images_init(tab->image, tab->mlx, \
								FDF_WINDOW_WIDTH, FDF_WINDOW_HEIGHT)))
		return (false);
	ft_camera_isometric(&tab->camera, (t_res){FDF_WINDOW_WIDTH, \
											FDF_WINDOW_HEIGHT});
	tab->img_id = 0;
	tab->lmb = false;
	tab->mmb = false;
	return (true);
}
