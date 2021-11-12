/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:19:20 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/12 23:30:57 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>

# include "mlx.h"
# include "libft.h"
# include "image.h"
# include "qrot.h"
# include "geometry.h"

# define FDF_WINDOW_WIDTH 1080
# define FDF_WINDOW_HEIGHT 1080

# define PI 3.14159265359

typedef struct s_res
{
	int	width;
	int	height;
}				t_res;

typedef struct s_window
{
	void	*mlx;
	void	*ptr;
	int		width;
	int		height;
}				t_window;

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

typedef struct s_fdf
{
	char		*filename;
	void		*mlx;
	t_window	window;
	t_image		image[2];
	int			img_id;
	t_camera	camera;
	t_geometry	geo;
	t_pixel		cursor;
	t_bool		lmb;
	t_bool		mmb;
}				t_fdf;

t_bool	ft_fdf_init(t_fdf *tab);

/*
** EVENTS
*/

int	ft_button_pressed(int keycode, int x, int y, t_fdf *tab);

#endif
