/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:16:25 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/23 05:51:14 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	ft_image_pixel_put(t_image *img, t_pixel *p)
{
	char	*dst;

	if (p->x < 0 || p->x >= img->width || p->y < 0 || p->y >= img->height)
		return ;
	dst = img->data + (p->y * img->line_length + p->x * img->bytes_per_pixel);
	*(unsigned int *) dst = p->cd;
}
