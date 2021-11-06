/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:03:34 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/06 04:55:13 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_bool	ft_mlx_init(t_fdf *tab)
{
	tab->mlx_ptr = mlx_init();
	if (!tab->mlx_ptr)
		return (false);
	return (true);
}

static t_bool	ft_window_init(t_fdf *tab)
{
	if (!ft_malloc((void *) &tab->window, sizeof(t_window)))
		return (false);
	tab->window->width = 1080;
	tab->window->height = 1080;
	tab->window->ptr = mlx_new_window(tab->mlx_ptr, \
										tab->window->width, \
										tab->window->height, "fdf");
	return (true);
}

static t_bool	ft_image_init(t_fdf *tab)
{
	if (!ft_malloc((void *) &tab->image, sizeof(t_image)))
		return (false);
	tab->image->mlx_img = mlx_new_image(tab->mlx_ptr, \
										tab->window->width, \
										tab->window->height);
	tab->image->ptr = mlx_get_data_addr(tab->image->mlx_img, \
										&tab->image->bits_per_pixel, \
										&tab->image->line_length, \
										&tab->image->endian);
	tab->image->bytes_per_pixel = tab->image->bits_per_pixel / 8;
	tab->image->width = tab->window->width;
	tab->image->height = tab->window->height;
	return (true);
}

static t_bool	ft_projection_init(t_fdf *tab)
{
	tab->projection.matrix[0][0] = 1 / sqrt(2);
	tab->projection.matrix[0][1] = 0;
	tab->projection.matrix[0][2] = -1 / sqrt(2);
	tab->projection.matrix[1][0] = 1 / sqrt(6);
	tab->projection.matrix[1][1] = 2 / sqrt(6);
	tab->projection.matrix[1][2] = 1 / sqrt(6);
	tab->projection.matrix[2][0] = 1 / sqrt(3);
	tab->projection.matrix[2][1] = -1 / sqrt(3);
	tab->projection.matrix[2][2] = 1 / sqrt(3);
	tab->rotation.matrix[0][0] = 1;
	tab->rotation.matrix[0][1] = 0;
	tab->rotation.matrix[0][2] = 0;
	tab->rotation.matrix[1][0] = 0;
	tab->rotation.matrix[1][1] = 1;
	tab->rotation.matrix[1][2] = 0;
	tab->rotation.matrix[2][0] = 0;
	tab->rotation.matrix[2][1] = 0;
	tab->rotation.matrix[2][2] = 1;
	tab->full = tab->projection;
	tab->up = ft_qrot(ft_vector3(0, 1, 0), -asin(tan(PI / 6)));
	tab->right = ft_qrot(ft_vector3(1, 0, 0), -PI / 4);
	tab->qproj = ft_qrot_mult(tab->up, tab->right);
	//tab->up.axis = ft_qrot_rotate(tab->up.axis, tab->right);
	tab->right.axis = ft_qrot_rotate(tab->right.axis, ft_qrot(tab->up.axis, PI / 4));
	//tab->qproj = ft_qrot_mult(tab->qproj, tab->up);
	tab->qfull = tab->qproj;
	tab->up.angle = 0;
	tab->right.angle = 0;
	return (true);
}

t_fdf	*ft_fdf_init(void)
{
	t_fdf	*tab;

	if (!ft_malloc((void *) &tab, sizeof(t_fdf)))
		return (NULL);
	if (!(ft_mlx_init(tab)
			&& ft_window_init(tab)
			&& ft_image_init(tab)))
		return (NULL);
	ft_mlx_image_swap(&tab->image, &tab->image_tmp);
	if (!ft_image_init(tab))
		return (NULL);
	ft_projection_init(tab);
	tab->lmb = false;
	return (tab);
}
