/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:34:13 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 22:34:14 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	ft_camera_top(t_camera *camera, t_res res)
{
	camera->res = res;
	camera->yaw = (t_qrot){(t_vector3){0, 1, 0}, 0};
	camera->pitch = (t_qrot){(t_vector3){1, 0, 0}, PI / 2};
	camera->orient = ft_qrot_mult(camera->yaw, camera->pitch);
	ft_camera_update_projection(camera);
	camera->plane.left = -1.2;
	camera->plane.right = 1.2;
	camera->plane.down = -1.2;
	camera->plane.up = 1.2;
	ft_camera_update_plane(camera);
}

void	ft_camera_front(t_camera *camera, t_res res)
{
	camera->res = res;
	camera->yaw = (t_qrot){(t_vector3){0, 1, 0}, 0};
	camera->pitch = (t_qrot){(t_vector3){1, 0, 0}, 0};
	camera->orient = ft_qrot_mult(camera->yaw, camera->pitch);
	ft_camera_update_projection(camera);
	camera->plane.left = -1.2;
	camera->plane.right = 1.2;
	camera->plane.down = -1.2;
	camera->plane.up = 1.2;
	ft_camera_update_plane(camera);
}

void	ft_camera_side(t_camera *camera, t_res res)
{
	camera->res = res;
	camera->yaw = (t_qrot){(t_vector3){0, 1, 0}, -PI / 2};
	camera->pitch = (t_qrot){(t_vector3){1, 0, 0}, 0};
	camera->orient = ft_qrot_mult(camera->yaw, camera->pitch);
	ft_camera_update_projection(camera);
	camera->plane.left = -1.2;
	camera->plane.right = 1.2;
	camera->plane.down = -1.2;
	camera->plane.up = 1.2;
	ft_camera_update_plane(camera);
}
