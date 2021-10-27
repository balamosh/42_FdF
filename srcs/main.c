/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/10/27 03:24:36 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_fdf(void)
{
	t_fdf	*tab;

	if (!ft_fdf_init(tab))
		return ;
	mlx_loop(tab->mlx_ptr);
}

int	main(void)
{
	ft_fdf();
	return (0);
}
