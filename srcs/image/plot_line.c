/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:04:37 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 07:26:05 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	ft_plot_line_low(t_image *image, t_pixel p0, t_pixel p1)
{
	t_pixel	d;
	t_pixel	p;
	int		diff;
	int		yi;

	d = (t_pixel){p1.x - p0.x, p1.y - p0.y, 0};
	yi = 1;
	if (d.y < 0)
		yi = -1;
	d.y = ft_abs(d.y);
	diff = d.y + d.y - d.x;
	p = p0;
	while (p.x <= p1.x)
	{
		ft_mlx_pixel_put(image, p.x, p.y, \
		ft_color_lerp(p.cd, p1.cd, (double)(p.x - p0.x) / (p1.x - p0.x)));
		if (diff > 0)
		{
			p.y += yi;
			diff -= d.x + d.x;
		}
		diff += d.y + d.y;
		++p.x;
	}
}

static void	ft_plot_line_high(t_image *image, t_pixel p0, t_pixel p1)
{
	t_pixel	d;
	t_pixel	p;
	int		diff;
	int		xi;

	d = (t_pixel){p1.x - p0.x, p1.y - p0.y, 0};
	xi = 1;
	if (d.x < 0)
		xi = -1;
	d.x = ft_abs(d.x);
	diff = d.x + d.x - d.y;
	p = p0;
	while (p.y <= p1.y)
	{
		ft_mlx_pixel_put(image, p.x, p.y, \
		ft_color_lerp(p.cd, p1.cd, (double)(p.y - p0.y) / (p1.y - p0.y)));
		if (diff > 0)
		{
			p.x += xi;
			diff -= d.y + d.y;
		}
		diff += d.x + d.x;
		++p.y;
	}
}

void	ft_plot_line(t_image *image, t_pixel p0, t_pixel p1)
{
	if (ft_abs(p1.y - p0.y) < ft_abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			ft_plot_line_low(image, p1, p0);
		else
			ft_plot_line_low(image, p0, p1);
	}
	else
	{
		if (p0.y > p1.y)
			ft_plot_line_high(image, p1, p0);
		else
			ft_plot_line_high(image, p0, p1);
	}
}
