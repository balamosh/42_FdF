/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:03:34 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/12 17:08:52 by sotherys         ###   ########.fr       */
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

static t_bool	ft_window(t_window *window, \
							void *mlx, \
							t_res res, \
							const char *name)
{
	window->mlx = mlx;
	window->width = res.width;
	window->height = res.height;
	window->ptr = mlx_new_window(mlx, res.width, res.height, (char *) name);
	if (!window->ptr)
		return (false);
	return (true);
}

static t_bool	ft_image(t_image *image, \
							void *mlx, \
							int width, \
							int height)
{
	image->mlx = mlx;
	image->img_ptr = mlx_new_image(mlx, width, height);
	if (!image->img_ptr)
		return (false);
	image->data = mlx_get_data_addr(image->img_ptr, \
									&image->bits_per_pixel, \
									&image->line_length, \
									&image->endian);
	if (!image->data)
		return (false);
	image->bytes_per_pixel = image->bits_per_pixel / 8;
	image->width = width;
	image->height = height;
	return (true);
}

static void	ft_camera_isometric(t_camera *camera, t_res res)
{
	camera->res = res;
	camera->yaw = (t_qrot){(t_vector3){0, 1, 0}, -PI / 4};
	camera->pitch = (t_qrot){(t_vector3){1, 0, 0}, asin(tan(PI / 6))};
	camera->projection = ft_qrot_mult(camera->yaw, camera->pitch);
	camera->orient = camera->projection;
	camera->pitch.axis = \
	ft_qrot_rotate(camera->pitch.axis, \
					(t_qrot){camera->yaw.axis, -camera->yaw.angle});
	camera->yaw.angle = 0;
	camera->pitch.angle = 0;
	camera->plane.left = -27;
	camera->plane.right = 27;
	camera->plane.down = -27;
	camera->plane.up = 27;
}

t_bool	ft_geometry(t_geometry *geo, size_t npts, size_t nedges)
{
	geo->npts = npts;
	geo->nedges = nedges;
	return (ft_malloc((void *) &geo->pts, npts * sizeof(t_point)) 
			&& ft_malloc((void *) &geo->edges, nedges * sizeof(t_edge)));
}

static t_bool	ft_fdf_geo_alloc(t_geometry *geo, char *filename)
{
	int		fd;
	char	*line;
	size_t	curr;
	size_t	prev;

	fd = open(filename, O_RDONLY);
	if (read(fd, NULL, 0) == -1)
		return (false);
	geo->npts = 0;
	geo->nedges = 0;
	prev = 0;
	line = get_next_line(fd);
	while (line)
	{
		curr = ft_split_word_count(line, ' ');
		geo->npts += curr;
		geo->nedges += curr - 1 + ft_min(curr, prev);
		prev = curr;
		line = get_next_line(fd);
	}
	close(fd);
	return (ft_geometry(geo, geo->npts, geo->nedges));
}

static t_bool	ft_fdf_geo_fill(t_geometry *geo, char *filename)
{
	int		fd;
	char	**nbrs;
	size_t	ipt;
	size_t	iedge;
	int		x_prev;
	int		x;
	int		z;

	fd = open(filename, O_RDONLY);
	if (read(fd, NULL, 0) == -1)
		return (false);
	ipt = 0;
	iedge = 0;
	x_prev = 0;
	z = 0;
	nbrs = ft_split(get_next_line(fd), ' ');
	while (nbrs)
	{
		x = 0;
		while (nbrs[x])
		{
			geo->pts[ipt] = (t_point){(t_vector3){x, ft_atoi(nbrs[x]), z}, 0};
			if (x)
				geo->edges[iedge++] = (t_edge){{ipt, ipt - 1}};
			if (z)
				geo->edges[iedge++] = (t_edge){{ipt, ipt - x_prev}};
			++x;
			++ipt;
		}
		x_prev = x;
		++z;
		nbrs = ft_split(get_next_line(fd), ' ');
	}
	close(fd);
	return (geo->npts == ipt && geo->nedges == iedge);
}

t_bool	ft_fdf_geo_init(t_geometry *geo, char *filename)
{
	return (ft_fdf_geo_alloc(geo, filename) && ft_fdf_geo_fill(geo, filename));
}

t_bool	ft_fdf_init(t_fdf *tab)
{
	if (!(ft_fdf_geo_init(&tab->geo, tab->filename)
			&& ft_mlx_init(&tab->mlx)
			&& ft_window(&tab->window, tab->mlx, \
						(t_res){FDF_WINDOW_WIDTH, FDF_WINDOW_HEIGHT}, "fdf")
			&& ft_image(&tab->image[0], tab->mlx, \
						FDF_WINDOW_WIDTH, FDF_WINDOW_HEIGHT)
			&& ft_image(&tab->image[1], tab->mlx, \
						FDF_WINDOW_WIDTH, FDF_WINDOW_HEIGHT)))
		return (false);
	ft_camera_isometric(&tab->camera, (t_res){FDF_WINDOW_WIDTH, \
											FDF_WINDOW_HEIGHT});
	tab->img_id = 0;
	tab->lmb = false;
	tab->mmb = false;
	return (true);
}
