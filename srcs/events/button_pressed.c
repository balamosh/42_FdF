/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_pressed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:52:29 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 14:21:52 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

static void	ft_lmb_pressed(int x, int y, t_fdf *tab)
{
	if (tab->mmb)
		return ;
	tab->lmb = true;
	tab->cursor = (t_pixel){x, y, 0};
}

static void	ft_mmb_pressed(int x, int y, t_fdf *tab)
{
	if (tab->lmb)
		return ;
	tab->mmb = true;
	tab->cursor = (t_pixel){x, y, 0};
}

int	ft_button_pressed(int keycode, int x, int y, t_fdf *tab)
{
	if (keycode == LMB)
		ft_lmb_pressed(x, y, tab);
	else if (keycode == MMB)
		ft_mmb_pressed(x, y, tab);
	else if (keycode == SCRL_UP)
		ft_camera_zoom(x, y, &tab->camera, 0.1);
	else if (keycode == SCRL_DOWN)
		ft_camera_zoom(x, y, &tab->camera, -0.1);
	return (0);
}
