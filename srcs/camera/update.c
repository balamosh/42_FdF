/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 04:12:19 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 15:35:56 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	ft_camera_update_projection(t_camera *camera)
{
	camera->projection = camera->orient;
	camera->pitch.axis = ft_qrot_rotate(camera->pitch.axis, \
							(t_qrot){camera->yaw.axis, -camera->yaw.angle});
	camera->yaw.angle = 0;
	camera->pitch.angle = 0;
}

void	ft_camera_update_plane(t_camera *camera)
{
	camera->plane.width = camera->plane.right - camera->plane.left;
	camera->plane.height = camera->plane.up - camera->plane.down;
	camera->plane.pixel_width = camera->res.width / camera->plane.width;
	camera->plane.pixel_height = camera->res.height / camera->plane.height;
}

void	ft_camera_update_plane_ratio(t_camera *cam)
{
	double	ratio;
	double	offset;

	ratio = (double) cam->res.width / cam->res.height;
	if (ft_fabs(ratio - cam->plane.width / cam->plane.height) < EPS)
		return ;
	if (ratio > cam->plane.width / cam->plane.height)
	{
		offset = (ratio * cam->plane.height - cam->plane.width) / 2;
		cam->plane.left -= offset;
		cam->plane.right += offset;
	}
	else
	{
		offset = (cam->plane.width / ratio - cam->plane.height) / 2;
		cam->plane.down -= offset;
		cam->plane.up += offset;
	}
	ft_camera_update_plane(cam);
}
