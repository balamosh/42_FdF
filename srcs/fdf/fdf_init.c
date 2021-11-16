/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:03:34 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 08:12:45 by sotherys         ###   ########.fr       */
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
