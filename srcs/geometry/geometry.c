/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:26:03 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 01:27:07 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_bool	ft_geometry(t_geometry *geo, size_t npts, size_t nedges)
{
	geo->npts = npts;
	geo->nedges = nedges;
	return (ft_malloc((void *) &geo->pts, npts * sizeof(t_point)) 
			&& ft_malloc((void *) &geo->edges, nedges * sizeof(t_edge)));
}
