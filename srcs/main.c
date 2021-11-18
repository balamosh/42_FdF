/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/17 19:48:38 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

#include <sys/time.h>
#include <sys/resource.h>

void	ft_test_axis(t_fdf *tab)
{
	t_pixel	o[3];

	ft_clear_image(&tab->image[tab->img_id]);
	ft_render_geo(&tab->image[tab->img_id], &tab->geo, &tab->camera);
	ft_render_geo(&tab->image[tab->img_id], &tab->axis_geo, &tab->axis_cam);
	mlx_put_image_to_window(tab->mlx, \
	tab->window.ptr, tab->image[tab->img_id].img_ptr, 0, 0);
	tab->img_id = (tab->img_id + 1) % FDF_TMP_IMG;
	o[0] = ft_point_to_pixel(&tab->axis_cam, tab->axis_geo.pts[1]);
	o[1] = ft_point_to_pixel(&tab->axis_cam, tab->axis_geo.pts[3]);
	o[2] = ft_point_to_pixel(&tab->axis_cam, tab->axis_geo.pts[5]);
	mlx_string_put(tab->mlx, tab->window.ptr, o[0].x, o[0].y, 0xFFFF0000, "x");
	mlx_string_put(tab->mlx, tab->window.ptr, o[1].x, o[1].y, 0xFF00FF00, "y");
	mlx_string_put(tab->mlx, tab->window.ptr, o[2].x, o[2].y, 0xFF0000FF, "z");
}

void	ft_fdf(char *filename)
{
	t_fdf	tab;

	tab.filename = filename;
	if (!ft_fdf_init(&tab))
		ft_close(&tab);
	mlx_hook(tab.window.ptr, 4, 1L << 2, ft_button_pressed, &tab);
	mlx_hook(tab.window.ptr, 5, 1L << 3, ft_button_released, &tab);
	mlx_hook(tab.window.ptr, 6, 1L << 6, ft_cursor_moved, &tab);
	mlx_hook(tab.window.ptr, 17, 1L << 1, ft_close, &tab);
	ft_test_axis(&tab);
	mlx_loop(tab.mlx);
}

int	main(int ac, char **av)
{
	//struct rlimit	limit;

	//limit.rlim_cur = 1024 * 40000;
	//limit.rlim_max = 1024 * 40000;
	//setrlimit(RLIMIT_AS, &limit);
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
