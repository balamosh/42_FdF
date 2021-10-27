/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:21 by sotherys          #+#    #+#             */
/*   Updated: 2021/10/27 03:24:22 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_bool	ft_malloc(void **ptr, size_t n)
{
	*ptr = malloc(n);
	if (*ptr)
		return (true);
	return (false);
}
