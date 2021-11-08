/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:16:44 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/08 12:16:49 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	ft_clear_image(t_image *img)
{
	int	px;
	int	py;

	px = 0;
	while (px < img->width)
	{
		py = 0;
		while (py < img->height)
		{
			ft_mlx_pixel_put(img, px, py, 0xFF000000);
			++py;
		}
		++px;
	}
}
