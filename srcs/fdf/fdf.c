/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 06:35:52 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/23 06:48:14 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

void	ft_fdf_render(t_fdf *tab)
{
	t_pixel	o[3];

	ft_image_clear(&tab->image[tab->img_id]);
	if (!tab->render_bbox)
		ft_render_geo(&tab->image[tab->img_id], &tab->geo, &tab->camera);
	else
		ft_render_geo(&tab->image[tab->img_id], &tab->bbox, &tab->camera);
	ft_render_geo(&tab->image[tab->img_id], &tab->axis_geo, &tab->axis_cam);
	mlx_put_image_to_window(tab->mlx, \
	tab->window.ptr, tab->image[tab->img_id].img_ptr, 0, 0);
	tab->img_id = (tab->img_id + 1) % FDF_TMP_IMG;
	ft_point_to_pixel(&tab->axis_cam, &tab->axis_geo.pts[1], &o[0]);
	ft_point_to_pixel(&tab->axis_cam, &tab->axis_geo.pts[3], &o[1]);
	ft_point_to_pixel(&tab->axis_cam, &tab->axis_geo.pts[5], &o[2]);
	mlx_string_put(tab->mlx, tab->window.ptr, o[0].x, o[0].y, 0xFFFF0000, "x");
	mlx_string_put(tab->mlx, tab->window.ptr, o[1].x, o[1].y, 0xFF00FF00, "y");
	mlx_string_put(tab->mlx, tab->window.ptr, o[2].x, o[2].y, 0xFF0000FF, "z");
}

void	ft_fdf(char *filename)
{
	t_fdf	tab;

	tab.filename = filename;
	if (!ft_fdf_init(&tab))
		ft_close(&tab);
	mlx_hook(tab.window.ptr, 2, 1L << 0, ft_key_pressed, &tab);
	mlx_hook(tab.window.ptr, 4, 1L << 2, ft_button_pressed, &tab);
	mlx_hook(tab.window.ptr, 5, 1L << 3, ft_button_released, &tab);
	mlx_hook(tab.window.ptr, 6, 1L << 6, ft_cursor_moved, &tab);
	mlx_hook(tab.window.ptr, 17, 1L << 1, ft_close, &tab);
	ft_fdf_render(&tab);
	mlx_loop(tab.mlx);
}
