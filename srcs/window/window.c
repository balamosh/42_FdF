/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:08:02 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 01:10:08 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

t_bool	ft_window(t_window *window, \
							void *mlx, \
							t_res res, \
							const char *name)
{
	window->mlx = mlx;
	window->width = res.width;
	window->height = res.height;
	window->ptr = mlx_new_window(mlx, res.width, res.height, (char *) name);
	if (!window->ptr)
		return (false);
	return (true);
}
