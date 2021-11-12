/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/11 09:51:23 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"
#include <stdio.h>

#define TEST 20

t_pixel	ft_point_to_pixel(t_camera *cam, t_vector3 pt)
{
	t_vector3	project_pt;
	t_pixel	pix;

	project_pt = ft_qrot_rotate(pt, cam->orient);	
	pix = ft_pixel(cam->res.width / (cam->plane.right - cam->plane.left) * \
					(project_pt.x - cam->plane.left), \
					cam->res.height / (cam->plane.up - cam->plane.down) * \
					(cam->plane.up - project_pt.y));
	return (pix);
}

void	ft_test_axis(t_fdf *tab)
{
	t_pixel	oo, ox, oy, oz;

	t_pixel	pixels[TEST][TEST][4];
	int		i, j;

	ft_clear_image(&tab->image[tab->img_id]);

	oo = ft_point_to_pixel(&tab->camera, ft_vector3(0, 0, 0));
	ox = ft_point_to_pixel(&tab->camera, ft_vector3(10, 0, 0));
	oy = ft_point_to_pixel(&tab->camera, ft_vector3(0, 10, 0));
	oz = ft_point_to_pixel(&tab->camera, ft_vector3(0, 0, 10));
	ft_plot_line(&tab->image[tab->img_id], oo, ox, 0xFFFF0000);
	ft_plot_line(&tab->image[tab->img_id], oo, oy, 0xFF00FF00);
	ft_plot_line(&tab->image[tab->img_id], oo, oz, 0xFF0000FF);
	ft_plot_line(&tab->image[tab->img_id], oo, ft_point_to_pixel(&tab->camera, tab->camera.yaw.axis), 0xFFFF00FF);
	ft_plot_line(&tab->image[tab->img_id], oo, ft_point_to_pixel(&tab->camera, tab->camera.pitch.axis), 0xFFFF00FF);
	
	i = 0;
	while (i < TEST)
	{
		j = 0;
		while (j < TEST)
		{
			pixels[i][j][0] = ft_point_to_pixel(&tab->camera, ft_vector3(i - TEST / 2, sin(i + j - TEST) / 5, j - TEST / 2));
			pixels[i][j][1] = ft_point_to_pixel(&tab->camera, ft_vector3(i - TEST / 2, sin(i + j - TEST - 1) / 5, j - 1 - TEST / 2));
			pixels[i][j][2] = ft_point_to_pixel(&tab->camera, ft_vector3(i - 1 - TEST / 2, sin(i + j - TEST - 1) / 5, j - TEST / 2));
			pixels[i][j][3] = ft_point_to_pixel(&tab->camera, ft_vector3(i - 1 - TEST / 2, sin(i + j - TEST - 2) / 5, j - 1 - TEST / 2));
			ft_plot_line(&tab->image[tab->img_id], pixels[i][j][0], pixels[i][j][1], 0xFFFFFFFF);
			ft_plot_line(&tab->image[tab->img_id], pixels[i][j][0], pixels[i][j][2], 0xFFFFFFFF);
			ft_plot_line(&tab->image[tab->img_id], pixels[i][j][2], pixels[i][j][3], 0xFFFFFFFF);
			ft_plot_line(&tab->image[tab->img_id], pixels[i][j][3], pixels[i][j][1], 0xFFFFFFFF);
			++j;
		}
		++i;
	}

	mlx_put_image_to_window(tab->mlx, \
							tab->window.ptr, tab->image[tab->img_id].img_ptr, 0, 0);
	tab->img_id = (tab->img_id + 1) % 2;

	mlx_string_put(tab->mlx, tab->window.ptr, ox.x, ox.y, 0xFFFFFFFF, "x");
	mlx_string_put(tab->mlx, tab->window.ptr, oy.x, oy.y, 0xFFFFFFFF, "y");
	mlx_string_put(tab->mlx, tab->window.ptr, oz.x, oz.y, 0xFFFFFFFF, "z");
}

int	ft_button_released(int keycode, int x, int y, t_fdf *tab)
{
	t_qrot	new_up;
	t_qrot	new_right;

	(void) x;
	(void) y;
	if (keycode == LMB)
	{
		tab->lmb = false;
		tab->camera.projection = tab->camera.orient;
		new_right.axis = ft_qrot_rotate(tab->camera.pitch.axis, \
		ft_qrot(tab->camera.yaw.axis, -tab->camera.yaw.angle));
		new_up.axis = ft_qrot_rotate(tab->camera.yaw.axis, \
		ft_qrot(tab->camera.pitch.axis, -tab->camera.pitch.angle));
		new_up.axis = tab->camera.yaw.axis;
		new_up.angle = 0;
		new_right.angle = 0;
		tab->camera.yaw = new_up;
		tab->camera.pitch = new_right;
	}
	if (keycode == MMB)
		tab->mmb = false;
	ft_test_axis(tab);
	//printf("BUTTON RELEASED:%d\n", keycode);
	return (0);
}

int	ft_cursor_moved(int x, int y, t_fdf *tab)
{
	double	theta_up;
	double	theta_right;
	double	offset_up;
	double	offset_right;

	if (tab->lmb)
	{
		theta_up = 2 * PI * (x - tab->cursor.x) / tab->window.width;
		theta_right = 2 * PI * (y - tab->cursor.y) / tab->window.height;
		tab->camera.yaw.angle = theta_up;
		tab->camera.pitch.angle = theta_right;
		tab->camera.orient = ft_qrot_mult(\
		ft_qrot_mult(tab->camera.yaw, tab->camera.pitch), tab->camera.projection);
		ft_test_axis(tab);
	}
	else if (tab->mmb)
	{
		offset_up = (tab->camera.plane.up - tab->camera.plane.down) * \
					(y - tab->cursor.y) / tab->window.width;
		offset_right = (tab->camera.plane.right - tab->camera.plane.left) * \
						(tab->cursor.x - x) / tab->window.height;
		tab->camera.plane.up += offset_up;
		tab->camera.plane.down += offset_up;
		tab->camera.plane.left += offset_right;
		tab->camera.plane.right += offset_right;
		tab->cursor = (t_pixel){x, y};
		ft_test_axis(tab);
	}
	//printf("NEW CURSOR POS:%d %d\n", x, y);
	return (0);
}

int	ft_close(t_fdf *tab)
{
	tab->lmb = false;
	exit(0);
}

void	ft_fdf(char *filename)
{
	t_fdf	tab;

	tab.filename = filename;
	if (!ft_fdf_init(&tab))
		ft_close(&tab);
	mlx_hook(tab.window.ptr, 04, 1L<<2, ft_button_pressed, &tab);
	mlx_hook(tab.window.ptr, 05, 1L<<3, ft_button_released, &tab);
	mlx_hook(tab.window.ptr, 06, 1L<<6, ft_cursor_moved, &tab);
	mlx_hook(tab.window.ptr, 17, 1L<<1, ft_close, &tab);
	ft_test_axis(&tab);
	mlx_loop(tab.mlx);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		ft_fdf(av[1]);
	else if (ac == 1)
	{
		ft_putstr_fd("Invalid agruments. Filename is missing.\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("Too many arguments.\n", 2);
		return (2);
	}
	return (0);
}
