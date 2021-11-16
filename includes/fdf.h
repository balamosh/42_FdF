/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:19:20 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 08:03:22 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "mlx.h"
# include "window.h"
# include "image.h"
# include "camera.h"
# include "geometry.h"

# define FDF_WINDOW_WIDTH 1080
# define FDF_WINDOW_HEIGHT 1080
# define FDF_TMP_IMG 5

typedef struct s_fdf
{
	char		*filename;
	void		*mlx;
	t_window	window;
	t_image		image[FDF_TMP_IMG];
	int			img_id;
	t_camera	camera;
	t_geometry	geo;
	t_geometry	bbox;
	t_pixel		cursor;
	t_bool		lmb;
	t_bool		mmb;
}				t_fdf;

t_bool	ft_fdf_geo_init(t_geometry *geo, t_geometry *bbox, char *filename);
t_bool	ft_fdf_init(t_fdf *tab);
void	ft_test_axis(t_fdf *tab);

/*
** EVENTS
*/

int		ft_button_pressed(int keycode, int x, int y, t_fdf *tab);
int		ft_button_released(int keycode, int x, int y, t_fdf *tab);
int		ft_cursor_moved(int x, int y, t_fdf *tab);
int		ft_close(t_fdf *tab);

#endif
