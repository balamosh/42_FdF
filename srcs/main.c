/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/10/27 04:12:26 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_line(t_image *image, t_pixel p1, t_pixel p2)

void	ft_fdf(void)
{
	t_fdf	*tab;

	tab = ft_fdf_init();
	if (!tab)
		return ;
	mlx_loop(tab->mlx_ptr);
}

int	main(void)
{
	ft_fdf();
	return (0);
}
