/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:15:03 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/05 20:46:26 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	ft_pixel(int x, int y)
{
	t_pixel	pix;

	pix.x = x;
	pix.y = y;
	return (pix);
}

void	ft_mlx_image_swap(t_image **img1, t_image **img2)
{
	t_image	*tmp;

	tmp = *img1;
	*img1 = *img2;
	*img2 = tmp;
}

void	ft_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->ptr + (y * img->line_length + x * img->bytes_per_pixel);
	*(unsigned int *) dst = color;
}

void	ft_clear_image(t_image *img)
{
	int	px;
	int	py;

	px = 0;
	while (px <= img->width)
	{
		py = 0;
		while (py <= img->height)
		{
			ft_mlx_pixel_put(img, px, py, 0xFF000000);
			++py;
		}
		++px;
	}
}
