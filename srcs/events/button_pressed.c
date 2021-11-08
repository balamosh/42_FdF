/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_pressed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:52:29 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/08 10:39:46 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

static void	ft_lmb_pressed(int x, int y, t_fdf *tab)
{
	tab->lmb = true;
	tab->cursor_old = ft_pixel(x, y);
	tab->cursor_new = tab->cursor_old;
}

static int	ft_zoom_in(int x, int y, t_fdf *tab)
{
	double	len_horizontal;
	double	len_vertical;

	len_horizontal = tab->plane.right - tab->plane.left;
	len_vertical = tab->plane.up - tab->plane.down;
	tab->plane.left += len_horizontal * 0.1 * x / tab->window->width;
	tab->plane.right -= len_horizontal * 0.1 * \
						(tab->window->width - x) / tab->window->width;
	tab->plane.up -= len_vertical * 0.1 * y / tab->window->height;
	tab->plane.down += len_vertical * 0.1 * \
						(tab->window->height - y) / tab->window->height;
	return (0);
}

static int	ft_zoom_out(int x, int y, t_fdf *tab)
{
	double	len_horizontal;
	double	len_vertical;

	len_horizontal = tab->plane.right - tab->plane.left;
	len_vertical = tab->plane.up - tab->plane.down;
	tab->plane.left -= len_horizontal * 0.1 * x / tab->window->width;
	tab->plane.right += len_horizontal * 0.1 * \
						(tab->window->width - x) / tab->window->width;
	tab->plane.up += len_vertical * 0.1 * y / tab->window->height;
	tab->plane.down -= len_vertical * 0.1 * \
						(tab->window->height - y) / tab->window->height;
	return (0);
}

int	ft_button_pressed(int keycode, int x, int y, t_fdf *tab)
{
	if (keycode == LMB)
		ft_lmb_pressed(x, y, tab);
	else if (keycode == SCRL_UP)
		ft_zoom_in(x, y, tab);
	else if (keycode == SCRL_DOWN)
		ft_zoom_out(x, y, tab);
	return (0);
}
