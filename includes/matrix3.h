/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:16:56 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/02 04:05:52 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX3_H
# define MATRIX3_H

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct s_matrix3
{
	double	matrix[3][3];
}				t_matrix3;

t_matrix3	ft_mult_matrix3(t_matrix3 a, t_matrix3 b);
t_point		ft_project_point(t_point pt, t_matrix3 m);

#endif
