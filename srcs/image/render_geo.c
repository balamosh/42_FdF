/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_geo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:41:04 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/16 11:36:10 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

#include <stdio.h>

static t_pixel	ft_point_to_pixel(t_camera *cam, t_point pt)
{
	t_vector3	project_pt;
	t_pixel		pix;

	project_pt = ft_qrot_rotate(pt.p, cam->orient);
	if (ft_fabs(project_pt.x) < EPS)
		project_pt.x = 0.0;
	if (ft_fabs(project_pt.y) < EPS)
		project_pt.y = 0.0;
	pix = (t_pixel){cam->plane.pixel_width * (project_pt.x - cam->plane.left), \
					cam->plane.pixel_height * (cam->plane.up - project_pt.y), \
					pt.cd};
	return (pix);
}

void	ft_render_geo(t_image *img, t_geometry *geo, t_camera *cam)
{
	size_t	i;
	t_pixel	p1;
	t_pixel	p2;
	
	i = 0;
	while (i < geo->nedges)
	{
		p1 = ft_point_to_pixel(cam, geo->pts[geo->edges[i].ptid[0]]);
		p2 = ft_point_to_pixel(cam, geo->pts[geo->edges[i].ptid[1]]);
		++i;
		if ((p1.x >= img->width && p2.x >= img->width)
			|| (p1.x < 0 && p2.x < 0)
			|| (p1.y >= img->height && p2.y >= img->height)
			|| (p1.y < 0 && p2.y < 0))
			continue ;
		ft_plot_line(img, p1, p2);
	}
}
