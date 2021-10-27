/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:19:20 by sotherys          #+#    #+#             */
/*   Updated: 2021/10/27 03:13:52 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "mlx.h"

typedef enum s_bool
{
	false,
	true
}			t_bool;

typedef struct s_image
{
	void	*mlx_img;
	char	*ptr;
	int		bits_per_pixel;
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
}				t_fdf;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif
