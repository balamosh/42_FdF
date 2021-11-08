/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:19:20 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/08 12:12:16 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>

# include "libft.h"
# include "image.h"
# include "mlx.h"
# include "qrot.h"

# define PI 3.14159265359

typedef struct s_window
{
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
}				t_plane;

typedef struct s_fdf
{
	void		*mlx_ptr;
	t_window	*window;
	t_image		*image;
	t_image		*image_tmp;
	t_qrot		qfull;
	t_qrot		qproj;
	t_qrot		up;
	t_qrot		right;
	t_plane		plane;
	t_pixel		cursor_old;
	t_pixel		cursor_new;
	t_bool		lmb;
}				t_fdf;

t_fdf	*ft_fdf_init(void);

/*
** EVENTS
*/

int	ft_button_pressed(int keycode, int x, int y, t_fdf *tab);

#endif
