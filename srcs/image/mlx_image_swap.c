/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:16:06 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/08 12:16:13 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	ft_mlx_image_swap(t_image **img1, t_image **img2)
{
	t_image	*tmp;

	tmp = *img1;
	*img1 = *img2;
	*img2 = tmp;
}
