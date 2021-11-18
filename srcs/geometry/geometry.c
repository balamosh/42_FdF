/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:26:03 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 12:33:44 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_bool	ft_geometry(t_geometry *geo, size_t spts, size_t sedges)
{
	geo->spts = spts;
	geo->sedges = sedges;
	geo->npts = 0;
	geo->nedges = 0;
	return (ft_malloc((void *) &geo->pts, spts * sizeof(t_point)) \
			&& ft_malloc((void *) &geo->edges, sedges * sizeof(t_edge)));
}
