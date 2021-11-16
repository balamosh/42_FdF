/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_lerp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 07:24:05 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 07:24:07 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int	ft_color_lerp(int color1, int color2, double t)
{
	t_color	cd1;
	t_color	cd2;

	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	cd1 = (t_color){(color1 >> 24) & 0xFF, \
					(color1 >> 16) & 0xFF, \
					(color1 >> 8) & 0xFF, \
					color1 & 0xFF};
	cd2 = (t_color){(color2 >> 24) & 0xFF, \
					(color2 >> 16) & 0xFF, \
					(color2 >> 8) & 0xFF, \
					color2 & 0xFF};
	return ((int)((1 - t) * cd1.t + t * cd2.t) << 24 | \
			(int)((1 - t) * cd1.r + t * cd2.r) << 16 | \
			(int)((1 - t) * cd1.g + t * cd2.g) << 8 | \
			(int)((1 - t) * cd1.b + t * cd2.b));
}
