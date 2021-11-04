/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:21:22 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/04 14:23:57 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include <math.h>

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}				t_vector3;

t_vector3	ft_vector3(double x, double y, double z);
t_vector3	ft_vector3_add(t_vector3 a, t_vector3 b);
t_vector3	ft_vector3_sub(t_vector3 a, t_vector3 b);
t_vector3	ft_vector3_scale(double r, t_vector3 a);
double		ft_vector3_len(t_vector3 a);
double		ft_vector3_dot(t_vector3 a, t_vector3 b);
t_vector3	ft_vector3_cross(t_vector3 a, t_vector3 b);

#endif