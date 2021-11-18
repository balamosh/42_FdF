/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:20:03 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/17 01:06:57 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

t_bool	ft_image(t_image *image, \
							void *mlx, \
							int width, \
							int height)
{
	image->img_ptr = mlx_new_image(mlx, width, height);
	if (!image->img_ptr)
		return (false);
	image->data = mlx_get_data_addr(image->img_ptr, \
									&image->bits_per_pixel, \
									&image->line_length, \
									&image->endian);
	if (!image->data)
		return (false);
	image->bytes_per_pixel = image->bits_per_pixel / 8;
	image->width = width;
	image->height = height;
	return (true);
}
