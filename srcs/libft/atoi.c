/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:39:12 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/12 15:39:13 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	return (0);
}

static int	ft_issign(char c)
{
	if (c == '+')
		return (1);
	if (c == '-')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nb;
	int		sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		++i;
	if (ft_issign(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while (ft_isdigit(str[i]))
		nb = nb * 10 + str[i++] - '0';
	return (sign * nb);
}
