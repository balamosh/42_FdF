/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 04:12:19 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 04:30:10 by sotherys         ###   ########.fr       */
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
