/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_geo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:41:04 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/23 06:30:41 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	ft_point_to_pixel(t_camera *cam, t_point *pt, t_pixel *pix)
{
	t_vector3	project_pt;

	project_pt = ft_qrot_rotate(pt->p, cam->orient);
	if (ft_fabs(project_pt.x) < EPS)
		project_pt.x = 0.0;
	if (ft_fabs(project_pt.y) < EPS)
		project_pt.y = 0.0;
	pix->x = cam->plane.pixel_width * (project_pt.x - cam->plane.left);
	pix->y = cam->plane.pixel_height * (cam->plane.up - project_pt.y);
	pix->cd = pt->cd;
}

void	ft_render_geo(t_image *img, t_geometry *geo, t_camera *cam)
{
	size_t	i;
	t_pixel	p1;
	t_pixel	p2;

	i = 0;
	while (i < geo->nedges)
	{
		ft_point_to_pixel(cam, &geo->pts[geo->edges[i].ptid[0]], &p1);
		ft_point_to_pixel(cam, &geo->pts[geo->edges[i].ptid[1]], &p2);
		++i;
		if ((p1.x >= img->width && p2.x >= img->width)
			|| (p1.x < 0 && p2.x < 0)
			|| (p1.y >= img->height && p2.y >= img->height)
			|| (p1.y < 0 && p2.y < 0))
			continue ;
		ft_plot_line(img, &p1, &p2);
	}
}

void	ft_camera_fit_geo(t_camera *cam, t_geometry *geo)
{
	t_vector3	min;
	t_vector3	max;
	t_vector3	curr;
	size_t		i;

	if (!geo->npts)
		return ;
	min = ft_qrot_rotate(geo->pts[0].p, cam->orient);
	max = min;
	i = 1;
	while (i < geo->npts)
	{
		curr = ft_qrot_rotate(geo->pts[i++].p, cam->orient);
		max = (t_vector3){ft_fmax(max.x, curr.x), ft_fmax(max.y, curr.y), 0};
		min = (t_vector3){ft_fmin(min.x, curr.x), ft_fmin(min.y, curr.y), 0};
	}
	cam->plane.left = min.x;
	cam->plane.right = max.x;
	cam->plane.up = max.y;
	cam->plane.down = min.y;
	ft_camera_update_plane(cam);
	ft_camera_update_plane_ratio(cam);
	ft_camera_zoom(cam->res.width / 2, cam->res.height / 2, cam, -0.1);
}
