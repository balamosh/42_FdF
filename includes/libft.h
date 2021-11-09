/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:06:54 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/10 02:38:23 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# include "bool.h"

t_bool	ft_malloc(void **ptr, size_t n);
int		ft_abs(int x);
double	ft_fabs(double x);
void	ft_swap(int *x, int *y);

# endif
