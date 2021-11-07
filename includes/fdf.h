/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:19:20 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/07 06:06:14 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>

# include "libft.h"
# include "mlx.h"
# include "matrix3.h"
# include "qrot.h"

# define PI 3.14159265359

typedef struct s_pixel
{
	int	x;
	int	y;
}				t_pixel;

typedef struct s_image
{
	void	*mlx_img;
	char	*ptr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_window
{
	void	*ptr;
	int		width;
	int		height;

}				t_window;

typedef struct s_fdf
{
	void		*mlx_ptr;
	t_window	*window;
	t_image		*image;
	t_image		*image_tmp;
	t_matrix3	full;
	t_matrix3	projection;
	t_matrix3	rotation;
	t_qrot		qfull;
	t_qrot		qproj;
	t_qrot		up;
	t_qrot		right;
	t_pixel		cursor_old;
	t_pixel		cursor_new;
	t_bool		lmb;
}				t_fdf;

t_pixel	ft_pixel(int x, int y);
void	ft_mlx_image_swap(t_image **img1, t_image **img2);
void	ft_clear_image(t_image *img);
void	ft_mlx_pixel_put(t_image *img, int x, int y, int color);
void	ft_plot_line(t_image *image, t_pixel p0, t_pixel p1, int color);
t_fdf	*ft_fdf_init(void);

#endif
