/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:11:02 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 07:24:23 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "mlx.h"
# include "bool.h"

typedef struct s_color
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct s_pixel
{
	int	x;
	int	y;
	int	cd;
}				t_pixel;

typedef struct s_image
{
	void	*mlx;
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

t_pixel	ft_pixel(int x, int y);
t_bool	ft_image(t_image *image, \
							void *mlx, \
							int width, \
							int height);
void	ft_mlx_image_swap(t_image **img1, t_image **img2);
void	ft_clear_image(t_image *img);
void	ft_mlx_pixel_put(t_image *img, int x, int y, int color);
void	ft_plot_line(t_image *image, t_pixel p0, t_pixel p1);
int		ft_color_lerp(int color1, int color2, double t);

#endif
