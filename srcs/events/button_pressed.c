/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_pressed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:52:29 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/12 23:53:22 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

static void	ft_lmb_pressed(int x, int y, t_fdf *tab)
{
	if (tab->mmb)
		return ;
	tab->lmb = true;
	tab->cursor = (t_pixel){x, y};
}

static void	ft_mmb_pressed(int x, int y, t_fdf *tab)
{
	if (tab->lmb)
		return ;
	tab->mmb = true;
	tab->cursor = (t_pixel){x, y};
}

static int	ft_zoom(int x, int y, t_camera *camera, double scale)
{
	camera->plane.width = camera->plane.right - camera->plane.left;
	camera->plane.height = camera->plane.up - camera->plane.down;
	camera->plane.pixel_width = camera->res.width / camera->plane.width;
	camera->plane.pixel_height = camera->res.height / camera->plane.height;

	camera->plane.left += scale * x / camera->plane.pixel_width;
	camera->plane.right -= scale * (camera->res.width - x) / camera->plane.pixel_width;
	camera->plane.up -= scale * y / camera->plane.pixel_height;
	camera->plane.down += scale * (camera->res.height - y) / camera->plane.pixel_height;
	
	camera->plane.width = camera->plane.right - camera->plane.left;
	camera->plane.height = camera->plane.up - camera->plane.down;
	camera->plane.pixel_width = camera->res.width / camera->plane.width;
	camera->plane.pixel_height = camera->res.height / camera->plane.height;
	return (0);
}

int	ft_button_pressed(int keycode, int x, int y, t_fdf *tab)
{
	if (keycode == LMB)
		ft_lmb_pressed(x, y, tab);
	else if (keycode == MMB)
		ft_mmb_pressed(x, y, tab);
	else if (keycode == SCRL_UP)
		ft_zoom(x, y, &tab->camera, 0.1);
	else if (keycode == SCRL_DOWN)
		ft_zoom(x, y, &tab->camera, -0.1);
	return (0);
}
