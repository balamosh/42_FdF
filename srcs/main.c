/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 09:40:42 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

t_pixel	ft_point_to_pixel(t_camera *cam, t_point pt)
{
	t_vector3	project_pt;
	t_pixel	pix;

	project_pt = ft_qrot_rotate(pt.p, cam->orient);	
	pix = (t_pixel){cam->plane.pixel_width * (project_pt.x - cam->plane.left), \
					cam->plane.pixel_height * (cam->plane.up - project_pt.y), \
					pt.cd};
	return (pix);
}

void	ft_test_axis(t_fdf *tab)
{
	t_pixel	oo, ox, oy, oz;
	t_pixel	p1, p2;
	size_t	i;

	ft_clear_image(&tab->image[tab->img_id]);

	oo = ft_point_to_pixel(&tab->camera, \
	(t_point){(t_vector3){0, 0, 0}, 0xFFFFFFFF});
	ox = ft_point_to_pixel(&tab->camera, \
	(t_point){(t_vector3){10, 0, 0}, 0xFFFF0000});
	oy = ft_point_to_pixel(&tab->camera, \
	(t_point){(t_vector3){0, 10, 0}, 0xFF00FF00});
	oz = ft_point_to_pixel(&tab->camera, \
	(t_point){(t_vector3){0, 0, 10}, 0xFF0000FF});
	ft_plot_line(&tab->image[tab->img_id], oo, ox);
	ft_plot_line(&tab->image[tab->img_id], oo, oy);
	ft_plot_line(&tab->image[tab->img_id], oo, oz);
	
	
	i = 0;
	while (i < tab->geo.nedges)
	{
		p1 = ft_point_to_pixel(&tab->camera, tab->geo.pts[tab->geo.edges[i].ptid[0]]);
		p2 = ft_point_to_pixel(&tab->camera, tab->geo.pts[tab->geo.edges[i].ptid[1]]);
		++i;
		if ((p1.x >= tab->window.width && p2.x >= tab->window.width)
			|| (p1.x < 0 && p2.x < 0)
			|| (p1.y >= tab->window.height && p2.y >= tab->window.height)
			|| (p1.y < 0 && p2.y < 0))
			continue ;
		ft_plot_line(&tab->image[tab->img_id], p1, p2);
	}
	i = 0;
	while (i < tab->bbox.nedges)
	{
		p1 = ft_point_to_pixel(&tab->camera, tab->bbox.pts[tab->bbox.edges[i].ptid[0]]);
		p2 = ft_point_to_pixel(&tab->camera, tab->bbox.pts[tab->bbox.edges[i].ptid[1]]);
		++i;
		if ((p1.x >= tab->window.width && p2.x >= tab->window.width)
			|| (p1.x < 0 && p2.x < 0)
			|| (p1.y >= tab->window.height && p2.y >= tab->window.height)
			|| (p1.y < 0 && p2.y < 0))
			continue ;
		ft_plot_line(&tab->image[tab->img_id], p1, p2);
	}
	

	mlx_put_image_to_window(tab->mlx, \
							tab->window.ptr, tab->image[tab->img_id].img_ptr, 0, 0);
	tab->img_id = (tab->img_id + 1) % FDF_TMP_IMG;

	mlx_string_put(tab->mlx, tab->window.ptr, ox.x, ox.y, 0xFFFFFFFF, "x");
	mlx_string_put(tab->mlx, tab->window.ptr, oy.x, oy.y, 0xFFFFFFFF, "y");
	mlx_string_put(tab->mlx, tab->window.ptr, oz.x, oz.y, 0xFFFFFFFF, "z");
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
