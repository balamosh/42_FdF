/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:03:34 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/10 19:03:53 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_bool	ft_mlx_init(void **mlx)
{
	*mlx = mlx_init();
	if (!*mlx)
		return (false);
	return (true);
}

static t_bool	ft_window(void *mlx, \
							t_window *window, \
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

static t_bool	ft_image(void *mlx, \
							t_image *image, \
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
					ft_qrot(camera->yaw.axis, -camera->yaw.angle));
	camera->yaw.angle = 0;
	camera->pitch.angle = 0;
	camera->plane.left = -27;
	camera->plane.right = 27;
	camera->plane.down = -27;
	camera->plane.up = 27;
}

t_bool	ft_fdf_init(t_fdf *tab)
{
	if (!(ft_mlx_init(&tab->mlx)
			&& ft_window(tab->mlx, &tab->window, \
						(t_res){FDF_WINDOW_WIDTH, FDF_WINDOW_HEIGHT}, "fdf")
			&& ft_image(tab->mlx, &tab->image[0], \
						FDF_WINDOW_WIDTH, FDF_WINDOW_HEIGHT)
			&& ft_image(tab->mlx, &tab->image[1], \
						FDF_WINDOW_WIDTH, FDF_WINDOW_HEIGHT)))
		return (false);
	ft_camera_isometric(&tab->camera, (t_res){FDF_WINDOW_WIDTH, \
											FDF_WINDOW_HEIGHT});
	tab->img_id = 0;
	tab->lmb = false;
	return (true);
}
