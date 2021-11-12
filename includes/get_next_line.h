/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:05:24 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/12 15:12:56 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# define FD_SIZE 12000

char	*get_next_line(int fd);

#endif
