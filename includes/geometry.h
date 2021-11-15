/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:21:53 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 06:26:54 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "libft.h"
# include "vector3.h"

typedef struct s_point
{
	t_vector3	p;
	int			cd;
}				t_point;

typedef struct s_edge
{
	size_t	ptid[2];
}				t_edge;

typedef struct s_geometry
{
	t_point	*pts;
	size_t	npts;
	size_t	spts;
	t_edge	*edges;
	size_t	nedges;
	size_t	sedges;
}				t_geometry;

t_bool	ft_geometry(t_geometry *geo, size_t spts, size_t sedges);
void	ft_geometry_add_point(t_geometry *geo, t_point pt);
void	ft_geometry_add_edge(t_geometry *geo, size_t ptid1, size_t ptid2);
t_bool	ft_geometry_bbox(t_geometry *bbox, t_geometry *geo);

#endif
