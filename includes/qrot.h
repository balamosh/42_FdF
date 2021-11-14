/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qrot.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:16:44 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 01:28:46 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QROT_H
# define QROT_H

# include "libft.h"
# include "vector3.h"

# define PI 3.14159265359
# define QROT_EPS 0.001

typedef struct s_qrot
{
	t_vector3	axis;
	double		angle;
}				t_qrot;

t_qrot		ft_qrot(t_vector3 axis, double angle);
t_qrot		ft_qrot_mult(t_qrot a, t_qrot b);
t_vector3	ft_qrot_rotate(t_vector3 pt, t_qrot q);

#endif
