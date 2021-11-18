/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 04:52:50 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 14:42:55 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	ft_camera_rotate(t_camera *camera, double a_yaw, double a_pitch)
{
	camera->yaw.angle = a_yaw;
	camera->pitch.angle = a_pitch;
	camera->orient = ft_qrot_mult(\
	ft_qrot_mult(camera->yaw, camera->pitch), camera->projection);
}

void	ft_camera_move(t_camera *camera, double up, double right)
{
	up /= camera->plane.pixel_width;
	right /= camera->plane.pixel_height;
	camera->plane.up += up;
	camera->plane.down += up;
	camera->plane.left += right;
	camera->plane.right += right;
}

void	ft_camera_copy_orient(t_camera *from, t_camera *to)
{
	to->projection = from->projection;
	to->orient = from->orient;
	to->pitch = from->pitch;
	to->yaw = from->yaw;
}

void	ft_camera_zoom(int x, int y, t_camera *camera, double scale)
{
	camera->plane.left += scale * x / camera->plane.pixel_width;
	camera->plane.right -= scale * (camera->res.width - x) \
							/ camera->plane.pixel_width;
	camera->plane.up -= scale * y / camera->plane.pixel_height;
	camera->plane.down += scale * (camera->res.height - y) \
							/ camera->plane.pixel_height;
	ft_camera_update_plane(camera);
}
