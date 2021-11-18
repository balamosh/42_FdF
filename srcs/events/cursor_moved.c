/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moved.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 05:19:24 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 13:52:19 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_cursor_moved(int x, int y, t_fdf *tab)
{
	if (tab->lmb)
	{
		ft_camera_rotate(&tab->camera, \
		2 * PI * (x - tab->cursor.x) / tab->window.width, \
		2 * PI * (y - tab->cursor.y) / tab->window.width);
		ft_camera_rotate(&tab->axis_cam, \
		2 * PI * (x - tab->cursor.x) / tab->window.width, \
		2 * PI * (y - tab->cursor.y) / tab->window.width);
		ft_camera_update_projection(&tab->camera);
		ft_camera_update_projection(&tab->axis_cam);
		tab->cursor = (t_pixel){x, y, 0};
		ft_test_axis(tab);
	}
	else if (tab->mmb)
	{
		ft_camera_move(&tab->camera, y - tab->cursor.y, tab->cursor.x - x);
		tab->cursor = (t_pixel){x, y, 0};
		ft_test_axis(tab);
	}
	return (0);
}
