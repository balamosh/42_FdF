/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_released.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 05:18:36 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 10:57:40 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

int	ft_button_released(int keycode, int x, int y, t_fdf *tab)
{
	(void) x;
	(void) y;
	if (keycode == LMB)
	{
		tab->lmb = false;
		ft_camera_update_projection(&tab->camera);
		ft_camera_update_projection(&tab->axis_cam);
	}
	else if (keycode == MMB)
		tab->mmb = false;
	else if (keycode == SCRL_UP || keycode == SCRL_DOWN)
		ft_test_axis(tab);
	return (0);
}
