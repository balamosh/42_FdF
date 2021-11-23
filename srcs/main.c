/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:28 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/23 06:38:19 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	if (ac == 2)
		ft_fdf(av[1]);
	else if (ac == 1)
	{
		ft_putstr_fd("Invalid agruments. Filename is missing.\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("Too many arguments.\n", 2);
		return (2);
	}
	return (0);
}
