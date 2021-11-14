/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:05:50 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 01:10:24 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"
# include "bool.h"
# include "res.h"

typedef struct s_window
{
	void	*mlx;
	void	*ptr;
	int		width;
	int		height;
}				t_window;

t_bool	ft_window(t_window *window, \
							void *mlx, \
							t_res res, \
							const char *name);

#endif
