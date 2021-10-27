/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:03:34 by sotherys          #+#    #+#             */
/*   Updated: 2021/10/27 03:26:09 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_bool	ft_mlx_init(t_fdf *tab)
{
	tab->mlx_ptr = mlx_init();
	if (!tab->mlx_ptr)
		return (false);
	return (true);
}

static t_bool	ft_window_init(void *mlx, t_window *window)
{
	if (!ft_malloc(&window, sizeof(t_window)))
		return (false);
	window->width = 1920;
	window->height = 1080;
	window->ptr = mlx_new_window(mlx, window->width, window->height, "fdf");
	return (true);
}

static t_bool	ft_image_init(t_fdf *tab)
{
	if (!ft_malloc(&tab->image, sizeof(t_image)))
		return (false);
	tab->image->mlx_img = mlx_new_image(tab->mlx_ptr, \
										tab->window->width, \
										tab->window->height);
	tab->image->ptr = mlx_get_data_addr(tab->image->mlx_img, \
										&tab->image->bits_per_pixel, \
										&tab->image->line_length, \
										&tab->image->endian);
	return (true);
}

t_bool	ft_fdf_init(t_fdf *tab)
{
	if (!ft_malloc(&tab, sizeof(t_fdf)))
		return (false);
	if (!(ft_mlx_init(tab)
			&& ft_window_init(tab->mlx_ptr, tab->window)
			&& ft_image_init(tab)))
		return (false);
	return (true);
}
