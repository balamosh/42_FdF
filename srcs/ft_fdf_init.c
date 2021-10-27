/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:03:34 by sotherys          #+#    #+#             */
/*   Updated: 2021/10/27 04:04:17 by sotherys         ###   ########.fr       */
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

static t_bool	ft_window_init(t_fdf *tab)
{
	if (!ft_malloc((void *) &tab->window, sizeof(t_window)))
		return (false);
	tab->window->width = 1920;
	tab->window->height = 1080;
	tab->window->ptr = mlx_new_window(tab->mlx_ptr, \
										tab->window->width, \
										tab->window->height, "fdf");
	return (true);
}

static t_bool	ft_image_init(t_fdf *tab)
{
	if (!ft_malloc((void *) &tab->image, sizeof(t_image)))
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

t_fdf	*ft_fdf_init(void)
{
	t_fdf	*tab;

	if (!ft_malloc((void *) &tab, sizeof(t_fdf)))
		return (NULL);
	if (!(ft_mlx_init(tab)
			&& ft_window_init(tab)
			&& ft_image_init(tab)))
		return (NULL);
	return (tab);
}
