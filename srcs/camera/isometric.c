/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:28:06 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 01:33:07 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	ft_camera_isometric(t_camera *camera, t_res res)
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
	camera->plane.width = camera->plane.right - camera->plane.left;
	camera->plane.height = camera->plane.up - camera->plane.down;
	camera->plane.pixel_width = camera->res.width / camera->plane.width;
	camera->plane.pixel_height = camera->res.height / camera->plane.height;
}
