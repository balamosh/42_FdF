/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 05:39:17 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 12:15:00 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	ft_fdf_free(t_fdf *tab)
{
	size_t	i;

	ft_geometry_free(&tab->geo);
	ft_geometry_free(&tab->bbox);
	ft_geometry_free(&tab->axis_geo);
	if (!tab->mlx)
		return ;
	if (tab->window.ptr)
		mlx_destroy_window(tab->mlx, tab->window.ptr);
	i = 0;
	while (i < FDF_TMP_IMG)
	{
		if (tab->image[i].img_ptr)
			mlx_destroy_image(tab->mlx, tab->image[i++].img_ptr);
	}
	mlx_destroy_display(tab->mlx);
	free(tab->mlx);
}

int	ft_close(t_fdf *tab)
{
	ft_fdf_free(tab);
	if (tab->error)
		perror(NULL);
	exit(0);
}
