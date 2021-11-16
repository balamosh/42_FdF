/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 10:55:09 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

void	ft_test_axis(t_fdf *tab)
{
	ft_clear_image(&tab->image[tab->img_id]);
	ft_render_geo(&tab->image[tab->img_id], &tab->geo, &tab->camera);
	ft_render_geo(&tab->image[tab->img_id], &tab->axis_geo, &tab->axis_cam);
	mlx_put_image_to_window(tab->mlx, \
							tab->window.ptr, tab->image[tab->img_id].img_ptr, 0, 0);
	tab->img_id = (tab->img_id + 1) % FDF_TMP_IMG;

	//mlx_string_put(tab->mlx, tab->window.ptr, ox.x, ox.y, 0xFFFFFFFF, "x");
	//mlx_string_put(tab->mlx, tab->window.ptr, oy.x, oy.y, 0xFFFFFFFF, "y");
	//mlx_string_put(tab->mlx, tab->window.ptr, oz.x, oz.y, 0xFFFFFFFF, "z");
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
