/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 04:52:50 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 05:10:47 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	ft_camera_rotate(t_camera *camera, double d_yaw, double d_pitch)
{
	camera->yaw.angle = 2 * PI * d_yaw / camera->res.width;
	camera->pitch.angle = 2 * PI * d_pitch / camera->res.height;
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
