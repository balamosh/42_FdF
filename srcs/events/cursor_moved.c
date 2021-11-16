/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moved.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 05:19:24 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 10:59:52 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_cursor_moved(int x, int y, t_fdf *tab)
{
	if (tab->lmb)
	{
		ft_camera_rotate(&tab->camera, x - tab->cursor.x, y - tab->cursor.y);
		ft_camera_rotate(&tab->axis_cam, (x - tab->cursor.x) / 10, \
											(y - tab->cursor.y) / 10);
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
