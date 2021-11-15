/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:00:37 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 05:11:08 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "qrot.h"
# include "res.h"

typedef struct s_plane
{
	double	left;
	double	right;
	double	up;
	double	down;
	double	width;
	double	height;
	double	pixel_width;
	double	pixel_height;
}				t_plane;

typedef struct s_camera
{
	t_qrot		orient;
	t_qrot		projection;
	t_qrot		yaw;
	t_qrot		pitch;
	t_plane		plane;
	t_res		res;
}				t_camera;

void	ft_camera_isometric(t_camera *camera, t_res res);
void	ft_camera_update_projection(t_camera *camera);
void	ft_camera_update_plane(t_camera *camera);
void	ft_camera_rotate(t_camera *camera, double a_yaw, double a_pitch);
void	ft_camera_move(t_camera *camera, double up, double right);

#endif
