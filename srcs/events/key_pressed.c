/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:55:09 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 23:40:43 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

static t_bool	ft_key_camera_rotate(int keycode, t_fdf *tab)
{
	double	a_yaw;
	double	a_pitch;

	a_yaw = 0;
	a_pitch = 0;
	if (keycode == KEY_UP)
		a_pitch = -PI * 0.05;
	else if (keycode == KEY_DOWN)
		a_pitch = PI * 0.05;
	else if (keycode == KEY_LEFT)
		a_yaw = -PI * 0.05;
	else if (keycode == KEY_RIGHT)
		a_yaw = PI * 0.05;
	else
		return (false);
	ft_camera_rotate(&tab->camera, a_yaw, a_pitch);
	ft_camera_rotate(&tab->axis_cam, a_yaw, a_pitch);
	ft_camera_update_projection(&tab->camera);
	ft_camera_update_projection(&tab->axis_cam);
	return (true);
}

static t_bool	ft_key_camera_view(int keycode, t_fdf *tab)
{
	if (keycode == KEY_1)
		ft_camera_isometric(&tab->camera, tab->camera.res);
	else if (keycode == KEY_2)
		ft_camera_top(&tab->camera, tab->camera.res);
	else if (keycode == KEY_3)
		ft_camera_front(&tab->camera, tab->camera.res);
	else if (keycode == KEY_4)
		ft_camera_side(&tab->camera, tab->camera.res);
	else if (keycode == KEY_5)
		ft_camera_trimetric(&tab->camera, tab->camera.res);
	else
		return (false);
	ft_camera_copy_orient(&tab->camera, &tab->axis_cam);
	ft_camera_fit_geo(&tab->camera, &tab->geo);
	return (true);
}

int	ft_key_pressed(int keycode, t_fdf *tab)
{
	if (keycode == KEY_H)
		ft_camera_fit_geo(&tab->camera, &tab->geo);
	else if (keycode == KEY_B)
		tab->render_bbox = !tab->render_bbox;
	else if (keycode == KEY_W)
		ft_camera_move(&tab->camera, -FDF_WINDOW_HEIGHT * 0.025, 0);
	else if (keycode == KEY_S)
		ft_camera_move(&tab->camera, FDF_WINDOW_HEIGHT * 0.025, 0);
	else if (keycode == KEY_A)
		ft_camera_move(&tab->camera, 0, FDF_WINDOW_HEIGHT * 0.025);
	else if (keycode == KEY_D)
		ft_camera_move(&tab->camera, 0, -FDF_WINDOW_HEIGHT * 0.025);
	else if (ft_key_camera_rotate(keycode, tab))
		;
	else if (ft_key_camera_view(keycode, tab))
		;
	else if (keycode == KEY_ESC)
		ft_close(tab);
	else
		return (0);
	ft_test_axis(tab);
	return (0);
}
