/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/04 14:21:49 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

#define TEST 20

t_pixel	ft_point_to_pixel(t_fdf *tab, t_vector3 pt)
{
	t_vector3	project_pt;
	t_pixel	pix;

	project_pt = ft_project_point(pt, ft_mult_matrix3(tab->projection, tab->rotation));
	pix = ft_pixel(tab->window->width / (108 / 2) * (project_pt.x + 108 / 4), \
					tab->window->height / (108 / 2) * (108 / 4 - project_pt.y));
	return (pix);
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
			pixels[i][j][0] = ft_point_to_pixel(tab, ft_vector3(i - TEST / 2, sin(i + j - TEST) / 5, j - TEST / 2));
			pixels[i][j][1] = ft_point_to_pixel(tab, ft_vector3(i - TEST / 2, sin(i + j - TEST - 1) / 5, j - 1 - TEST / 2));
			pixels[i][j][2] = ft_point_to_pixel(tab, ft_vector3(i - 1 - TEST / 2, sin(i + j - TEST - 1) / 5, j - TEST / 2));
			pixels[i][j][3] = ft_point_to_pixel(tab, ft_vector3(i - 1 - TEST / 2, sin(i + j - TEST - 2) / 5, j - 1 - TEST / 2));
			ft_plot_line(tab->image, pixels[i][j][0], pixels[i][j][1], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][0], pixels[i][j][2], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][2], pixels[i][j][3], 0xFFFFFFFF);
			ft_plot_line(tab->image, pixels[i][j][3], pixels[i][j][1], 0xFFFFFFFF);
			++j;
		}
		++i;
	}

	oo = ft_point_to_pixel(tab, ft_vector3(0, 0, 0));
	ox = ft_point_to_pixel(tab, ft_vector3(10, 0, 0));
	oy = ft_point_to_pixel(tab, ft_vector3(0, 10, 0));
	oz = ft_point_to_pixel(tab, ft_vector3(0, 0, 10));
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

	tab = ft_fdf_init();
	if (!tab)
		return ;
	
	mlx_hook(tab->window->ptr, 04, 1L<<2, ft_button_pressed, tab);
	mlx_hook(tab->window->ptr, 05, 1L<<3, ft_button_released, tab);
	mlx_hook(tab->window->ptr, 06, 1L<<6, ft_cursor_moved, tab);
	mlx_hook(tab->window->ptr, 17, 1L<<1, ft_close, tab);
	ft_test_axis(tab);
	mlx_loop(tab->mlx_ptr);
}

int	main(void)
{
	ft_fdf();
	return (0);
}
