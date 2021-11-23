/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:16:44 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/23 06:32:18 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	ft_image_clear(t_image *img)
{
	t_pixel	p;

	p.cd = 0xFF000000;
	p.x = 0;
	while (p.x < img->width)
	{
		p.y = 0;
		while (p.y < img->height)
		{
			ft_image_pixel_put(img, &p);
			++p.y;
		}
		++p.x;
	}
}
