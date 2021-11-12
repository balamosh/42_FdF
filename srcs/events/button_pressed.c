/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_pressed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:52:29 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/11 09:35:15 by sotherys         ###   ########.fr       */
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

static int	ft_zoom_in(int x, int y, t_camera *cam)
{
	double	len_horizontal;
	double	len_vertical;

	len_horizontal = cam->plane.right - cam->plane.left;
	len_vertical = cam->plane.up - cam->plane.down;
	cam->plane.left += len_horizontal * 0.1 * x / cam->res.width;
	cam->plane.right -= len_horizontal * 0.1 * \
						(cam->res.width - x) / cam->res.width;
	cam->plane.up -= len_vertical * 0.1 * y / cam->res.height;
	cam->plane.down += len_vertical * 0.1 * \
						(cam->res.height - y) / cam->res.height;
	return (0);
}

static int	ft_zoom_out(int x, int y, t_camera *cam)
{
	double	len_horizontal;
	double	len_vertical;

	len_horizontal = cam->plane.right - cam->plane.left;
	len_vertical = cam->plane.up - cam->plane.down;
	cam->plane.left -= len_horizontal * 0.1 * x / cam->res.width;
	cam->plane.right += len_horizontal * 0.1 * \
						(cam->res.width - x) / cam->res.width;
	cam->plane.up += len_vertical * 0.1 * y / cam->res.height;
	cam->plane.down -= len_vertical * 0.1 * \
						(cam->res.height - y) / cam->res.height;
	return (0);
}

int	ft_button_pressed(int keycode, int x, int y, t_fdf *tab)
{
	if (keycode == LMB)
		ft_lmb_pressed(x, y, tab);
	else if (keycode == MMB)
		ft_mmb_pressed(x, y, tab);
	else if (keycode == SCRL_UP)
		ft_zoom_in(x, y, &tab->camera);
	else if (keycode == SCRL_DOWN)
		ft_zoom_out(x, y, &tab->camera);
	return (0);
}
