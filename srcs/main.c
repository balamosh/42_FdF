/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/10/27 05:17:10 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	ft_pixel(int x, int y)
{
	t_pixel	p;

	p.x = x;
	p.y = y;
	return (p);
}

void	ft_draw_line(t_image *image, t_pixel p1, t_pixel p2)
{
	t_pixel	d;
	t_pixel	p;
	int		diff;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	diff = 2 * d.y - d.x;
	p = p1;
	while (p.x <= p2.x)
	{
		ft_mlx_pixel_put(image, p.x, p.y, 0xFFFFFFFF);
		if (diff > 0)
		{
			++p.y;
			diff -= 2 * d.x;
		}
		diff += 2 * d.y;
		++p.x;
	}
}

void	ft_fdf(void)
{
	t_fdf	*tab;

	tab = ft_fdf_init();
	if (!tab)
		return ;
	ft_draw_line(tab->image, ft_pixel(100, 100), ft_pixel(1900, 540));
	mlx_put_image_to_window(tab->mlx_ptr, \
							tab->window->ptr, tab->image->mlx_img, 0, 0);
	mlx_loop(tab->mlx_ptr);
}

int	main(void)
{
	ft_fdf();
	return (0);
}
