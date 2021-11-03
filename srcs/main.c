/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/03 06:51:22 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <time.h>
#include "matrix3.h"

#define TEST 20

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

t_pixel	ft_point_to_pixel(t_fdf *tab, t_point pt)
{
	t_point	project_pt;
	t_pixel	pix;

	project_pt = ft_project_point(pt, ft_mult_matrix3(tab->projection, tab->rotation));
	pix = ft_pixel(tab->window->width / (108 / 2) * (project_pt.x + 108 / 4), \
					tab->window->height / (108 / 2) * (108 / 4 - project_pt.y));
	return (pix);
}

void	ft_plot_line_low(t_image *image, t_pixel p0, t_pixel p1, int color)
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
		ft_mlx_pixel_put(image, p.x, p.y, color);
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

void	ft_plot_line_high(t_image *image, t_pixel p0, t_pixel p1, int color)
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
		ft_mlx_pixel_put(image, p.x, p.y, color);
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

void	ft_plot_line(t_image *image, t_pixel p0, t_pixel p1, int color)
{
	if (ft_abs(p1.y - p0.y) < ft_abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			ft_plot_line_low(image, p1, p0, color);
		else
			ft_plot_line_low(image, p0, p1, color);
	}
	else
	{
		if (p0.y > p1.y)
			ft_plot_line_high(image, p1, p0, color);
		else
			ft_plot_line_high(image, p0, p1, color);
	}
}

int	ft_button_pressed(int keycode, int x, int y, t_fdf *tab)
{
	(void) keycode;
	tab->lmb = true;
	tab->cursor_old = ft_pixel(x, y);
	tab->cursor_new = tab->cursor_old;

	//printf("BUTTON PRESSED:%d\n", keycode);
	return (0);
}

int	ft_button_released(int keycode, int x, int y, t_fdf *tab)
{
	(void) keycode;
	(void) x;
	(void) y;
	tab->lmb = false;
	tab->projection = ft_mult_matrix3(tab->projection, tab->rotation);
	tab->rotation.matrix[0][0] = 1;
	tab->rotation.matrix[0][1] = 0;
	tab->rotation.matrix[0][2] = 0;
	tab->rotation.matrix[1][0] = 0;
	tab->rotation.matrix[1][1] = 1;
	tab->rotation.matrix[1][2] = 0;
	tab->rotation.matrix[2][0] = 0;
	tab->rotation.matrix[2][1] = 0;
	tab->rotation.matrix[2][2] = 1;

	//printf("BUTTON RELEASED:%d\n", keycode);
	return (0);
}

void	ft_clear_image(t_fdf *tab)
{
	int	px;
	int	py;

	px = 0;
	while (px <= tab->window->width)
	{
		py = 0;
		while (py <= tab->window->height)
		{
			ft_mlx_pixel_put(tab->image, px, py, 0xFF000000);
			++py;
		}
		++px;
	}
}

void	ft_test_line(t_fdf *tab)
{
	ft_clear_image(tab);
	ft_plot_line(tab->image, tab->cursor_old, tab->cursor_new, 0xFFFFFFFF);
	mlx_put_image_to_window(tab->mlx_ptr, \
							tab->window->ptr, tab->image->mlx_img, 0, 0);
}

void	ft_test_axis(t_fdf *tab)
{
	t_pixel	oo, ox, oy, oz;

	t_pixel	pixels[TEST][TEST][4];
	int		i, j;

	ft_clear_image(tab);

	i = 0;
	while (i < TEST)
	{
		j = 0;
		while (j < TEST)
		{
			pixels[i][j][0] = ft_point_to_pixel(tab, ft_point(i - TEST / 2, sin(i + j - TEST) / 5, j - TEST / 2));
			pixels[i][j][1] = ft_point_to_pixel(tab, ft_point(i - TEST / 2, sin(i + j - TEST - 1) / 5, j - 1 - TEST / 2));
			pixels[i][j][2] = ft_point_to_pixel(tab, ft_point(i - 1 - TEST / 2, sin(i + j - TEST - 1) / 5, j - TEST / 2));
			pixels[i][j][3] = ft_point_to_pixel(tab, ft_point(i - 1 - TEST / 2, sin(i + j - TEST - 2) / 5, j - 1 - TEST / 2));
			ft_plot_line(tab->image, pixels[i][j][0], pixels[i][j][1], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][0], pixels[i][j][2], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][2], pixels[i][j][3], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][3], pixels[i][j][1], 0xFFFFFFFF);
			++j;
		}
		++i;
	}

	oo = ft_point_to_pixel(tab, ft_point(0, 0, 0));
	ox = ft_point_to_pixel(tab, ft_point(10, 0, 0));
	oy = ft_point_to_pixel(tab, ft_point(0, 10, 0));
	oz = ft_point_to_pixel(tab, ft_point(0, 0, 10));
	ft_plot_line(tab->image, oo, ox, 0xFFFF0000);
	ft_plot_line(tab->image, oo, oy, 0xFF00FF00);
	ft_plot_line(tab->image, oo, oz, 0xFF0000FF);
	mlx_put_image_to_window(tab->mlx_ptr, \
							tab->window->ptr, tab->image->mlx_img, 0, 0);
}

int	ft_cursor_moved(int x, int y, t_fdf *tab)
{
	double	theta;

	if (tab->lmb)
	{
		tab->cursor_new = ft_pixel(x, y);
		theta = 2 * PI * (tab->cursor_old.x - tab->cursor_new.x) / tab->window->width;
		tab->rotation.matrix[0][0] = cos(theta);
		tab->rotation.matrix[0][1] = 0;
		tab->rotation.matrix[0][2] = sin(theta);
		tab->rotation.matrix[1][0] = 0;
		tab->rotation.matrix[1][1] = 1;
		tab->rotation.matrix[1][2] = 0;
		tab->rotation.matrix[2][0] = -sin(theta);
		tab->rotation.matrix[2][1] = 0;
		tab->rotation.matrix[2][2] = cos(theta);
		ft_test_axis(tab);
	}
	//printf("NEW CURSOR POS:%d %d\n", x, y);
	return (0);
}

int	ft_close(int keycode, t_fdf *tab)
{
	(void) keycode;
	(void) tab;

	exit(0);
}

void	ft_fdf(void)
{
	t_fdf	*tab;
	//t_pixel	pixels[TEST][TEST][4];
	//int		i, j;

	tab = ft_fdf_init();
	if (!tab)
		return ;
	/*
	i = 0;
	while (i < TEST)
	{
		j = 0;
		while (j < TEST)
		{
			pixels[i][j][0] = ft_point_to_pixel(tab, ft_point(i - TEST / 2, sin(i + j - TEST) / 5, j - TEST / 2));
			pixels[i][j][1] = ft_point_to_pixel(tab, ft_point(i - TEST / 2, sin(i + j - TEST - 1) / 5, j - 1 - TEST / 2));
			pixels[i][j][2] = ft_point_to_pixel(tab, ft_point(i - 1 - TEST / 2, sin(i + j - TEST - 1) / 5, j - TEST / 2));
			pixels[i][j][3] = ft_point_to_pixel(tab, ft_point(i - 1 - TEST / 2, sin(i + j - TEST - 2) / 5, j - 1 - TEST / 2));
			ft_plot_line(tab->image, pixels[i][j][0], pixels[i][j][1], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][0], pixels[i][j][2], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][2], pixels[i][j][3], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][3], pixels[i][j][1], 0xFFFFFFFF);
			++j;
		}
		++i;
	}
	*/
	
	mlx_hook(tab->window->ptr, 04, 1L<<2, ft_button_pressed, tab);
	mlx_hook(tab->window->ptr, 05, 1L<<3, ft_button_released, tab);
	mlx_hook(tab->window->ptr, 06, 1L<<6, ft_cursor_moved, tab);
	mlx_hook(tab->window->ptr, 17, 1L<<1, ft_close, tab);
	ft_test_axis(tab);
	/*mlx_put_image_to_window(tab->mlx_ptr, \
							tab->window->ptr, tab->image->mlx_img, 0, 0);
	*/
	mlx_loop(tab->mlx_ptr);
}

int	main(void)
{
	ft_fdf();
	return (0);
}
