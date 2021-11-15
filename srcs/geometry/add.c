/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 03:42:55 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 03:44:10 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	ft_geometry_add_point(t_geometry *geo, t_point pt)
{
	geo->pts[geo->npts++] = pt;
}

void	ft_geometry_add_edge(t_geometry *geo, size_t ptid1, size_t ptid2)
{
	geo->edges[geo->nedges++] = (t_edge){{ptid1, ptid2}};
}
