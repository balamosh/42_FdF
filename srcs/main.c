/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/08 11:33:58 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"
#include <stdio.h>

#define TEST 20

t_pixel	ft_point_to_pixel(t_fdf *tab, t_vector3 pt)
{
	t_vector3	project_pt;
	t_pixel	pix;

	project_pt = ft_qrot_rotate(pt, tab->qfull);	
	pix = ft_pixel(tab->window->width / (tab->plane.right - tab->plane.left) * \
					(project_pt.x - tab->plane.left), \
					tab->window->height / (tab->plane.up - tab->plane.down) * \
					(tab->plane.up - project_pt.y));
	return (pix);
}

void	ft_test_axis(t_fdf *tab)
{
	t_pixel	oo, ox, oy, oz;

	t_pixel	pixels[TEST][TEST][4];
	int		i, j;

	ft_clear_image(tab->image);

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
	ft_plot_line(tab->image, oo, ft_point_to_pixel(tab, tab->up.axis), 0xFFFF00FF);
	ft_plot_line(tab->image, oo, ft_point_to_pixel(tab, tab->right.axis), 0xFFFF00FF);
	mlx_put_image_to_window(tab->mlx_ptr, \
							tab->window->ptr, tab->image->mlx_img, 0, 0);
	ft_mlx_image_swap(&tab->image, &tab->image_tmp);
	
	mlx_string_put(tab->mlx_ptr, tab->window->ptr, ox.x, ox.y, 0xFFFFFFFF, "x");
	mlx_string_put(tab->mlx_ptr, tab->window->ptr, oy.x, oy.y, 0xFFFFFFFF, "y");
	mlx_string_put(tab->mlx_ptr, tab->window->ptr, oz.x, oz.y, 0xFFFFFFFF, "z");
}

int	ft_button_released(int keycode, int x, int y, t_fdf *tab)
{
	t_qrot	new_up;
	t_qrot	new_right;

	(void) keycode;
	(void) x;
	(void) y;
	tab->lmb = false;
	tab->qproj = tab->qfull;
	new_right.axis = ft_qrot_rotate(tab->right.axis, ft_qrot(tab->up.axis, -tab->up.angle));
	new_up.axis = ft_qrot_rotate(tab->up.axis, ft_qrot(tab->right.axis, -tab->right.angle));
	new_up.axis = tab->up.axis;
	new_up.angle = 0;
	new_right.angle = 0;
	tab->up = new_up;
	tab->right = new_right;

	ft_test_axis(tab);

	//printf("BUTTON RELEASED:%d\n", keycode);
	return (0);
}

int	ft_cursor_moved(int x, int y, t_fdf *tab)
{
	double	theta_up;
	double	theta_right;

	if (tab->lmb)
	{
		tab->cursor_new = ft_pixel(x, y);
		theta_up = 2 * PI * (tab->cursor_new.x - tab->cursor_old.x) / tab->window->width;
		theta_right = 2 * PI * (tab->cursor_new.y - tab->cursor_old.y) / tab->window->height;
		tab->up.angle = theta_up;
		tab->right.angle = theta_right;
		tab->qfull = ft_qrot_mult(ft_qrot_mult(tab->up, tab->right), tab->qproj);
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
