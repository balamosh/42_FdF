/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 04:07:40 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/02 04:20:29 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix3.h"

t_matrix3	ft_mult_matrix3(t_matrix3 a, t_matrix3 b)
{
	t_matrix3	new;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			new.matrix[i][j] = 0;
			while (k < 3)
			{
				new.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
				++k;
			}
			++j;
		}
		++i;
	}
	return (new);
}

t_point	ft_project_point(t_point pt, t_matrix3 m)
{
	t_point	new;

	new.x = pt.x * m.matrix[0][0] + \
			pt.y * m.matrix[1][0] + \
			pt.z * m.matrix[2][0];
	new.y = pt.x * m.matrix[0][1] + \
			pt.y * m.matrix[1][1] + \
			pt.z * m.matrix[2][1];
	new.z = pt.x * m.matrix[0][2] + \
			pt.y * m.matrix[1][2] + \
			pt.z * m.matrix[2][2];
	return (new);
}
