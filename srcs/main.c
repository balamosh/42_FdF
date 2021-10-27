/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/10/27 21:03:14 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <time.h>

t_pixel	ft_pixel(int x, int y)
{
	t_pixel	pix;

	pix.x = x;
	pix.y = y;
	return (pix);
}

t_point	ft_point(double x, double y, double z)
{
	t_point	pt;

	pt.x = x;
	pt.y = y;
	pt.z = z;
	return (pt);
}

float	ft_abs(int x)
{
	if (x > 0)
		return (x);
	return (-x);
}

void	ft_swap(int *x, int *y)
{
	int	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

t_pixel	ft_point_to_pixel(t_window *window, t_point pt)
{
	t_point	project_pt;
	t_pixel	pix;

	(void) window;
	project_pt = ft_point((pt.x - pt.z) / sqrt(2), \
							(pt.x + 2 * pt.y + pt.z) / sqrt(6), 0);
	//printf("x = %f\ny = %f\n", project_pt.x, project_pt.y);
	pix = ft_pixel(window->width / (192 / 2) * (project_pt.x + 192 / 4), \
					window->height / (108 / 2) * (108 / 4 - project_pt.y));
	//printf("px = %d\npy = %d\n", pix.x, pix.y);
	return (pix);
}

void	ft_plot_line_low(t_image *image, t_pixel p0, t_pixel p1)
{
	t_pixel	d;
	t_pixel	p;
	int		diff;
	int		yi;

	d.x = p1.x - p0.x;
	d.y = p1.y - p0.y;
	yi = 1;
	if (d.y < 0)
	{
		yi = -1;
		d.y = -d.y;
	}
	diff = 2 * d.y - d.x;
	p = p0;
	while (p.x <= p1.x)
	{
		ft_mlx_pixel_put(image, p.x, p.y, 0xFFFFFFFF);
		if (diff > 0)
		{
			p.y += yi;
			diff += 2 * (d.y - d.x);
		}
		else
			diff += 2 * d.y;
		++p.x;
	}
}

void	ft_plot_line_high(t_image *image, t_pixel p0, t_pixel p1)
{
	t_pixel	d;
	t_pixel	p;
	int		diff;
	int		xi;

	d.x = p1.x - p0.x;
	d.y = p1.y - p0.y;
	xi = 1;
	if (d.x < 0)
	{
		xi = -1;
		d.x = -d.x;
	}
	diff = 2 * d.x - d.y;
	p = p0;
	while (p.y <= p1.y)
	{
		ft_mlx_pixel_put(image, p.x, p.y, 0xFFFFFFFF);
		if (diff > 0)
		{
			p.x += xi;
			diff += 2 * (d.x - d.y);
		}
		else
			diff += 2 * d.x;
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

#define TEST 50

void	ft_fdf(void)
{
	t_fdf	*tab;
	t_pixel	pixels[TEST][TEST][4];
	int		i, j;

	tab = ft_fdf_init();
	if (!tab)
		return ;
	/*
	pixels[0] = ft_point_to_pixel(tab->window, ft_point(0, 0, 0));
	pixels[1] = ft_point_to_pixel(tab->window, ft_point(0, 0, 1));
	pixels[2] = ft_point_to_pixel(tab->window, ft_point(1, 0, 0));
	pixels[3] = ft_point_to_pixel(tab->window, ft_point(1, 0, 1));
	
	ft_plot_line(tab->image, pixels[0], pixels[1]);
	ft_plot_line(tab->image, pixels[0], pixels[2]);
	ft_plot_line(tab->image, pixels[2], pixels[3]);
	ft_plot_line(tab->image, pixels[3], pixels[1]);
	*/
	i = 0;
	while (i < TEST)
	{
		j = 0;
		while (j < TEST)
		{
			pixels[i][j][0] = ft_point_to_pixel(tab->window, ft_point(i - TEST / 2, sin(i + j - TEST) / 5, j - TEST / 2));
			pixels[i][j][1] = ft_point_to_pixel(tab->window, ft_point(i - TEST / 2, sin(i + j - TEST - 1) / 5, j - 1 - TEST / 2));
			pixels[i][j][2] = ft_point_to_pixel(tab->window, ft_point(i - 1 - TEST / 2, sin(i + j - TEST - 1) / 5, j - TEST / 2));
			pixels[i][j][3] = ft_point_to_pixel(tab->window, ft_point(i - 1 - TEST / 2, sin(i + j - TEST - 2) / 5, j - 1 - TEST / 2));
			ft_plot_line(tab->image, pixels[i][j][0], pixels[i][j][1]);
			ft_plot_line(tab->image, pixels[i][j][0], pixels[i][j][2]);
			ft_plot_line(tab->image, pixels[i][j][2], pixels[i][j][3]);
			ft_plot_line(tab->image, pixels[i][j][3], pixels[i][j][1]);
			++j;
		}
		++i;
	}
	
	mlx_put_image_to_window(tab->mlx_ptr, \
							tab->window->ptr, tab->image->mlx_img, 0, 0);
	mlx_loop(tab->mlx_ptr);
}

int	main(void)
{
	ft_fdf();
	return (0);
}
