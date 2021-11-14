/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:06:54 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/15 01:21:45 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# include "bool.h"

t_bool	ft_malloc(void **ptr, size_t n);
int		ft_abs(int x);
double	ft_fabs(double x);
int		ft_min(int a, int b);
void	ft_swap(int *x, int *y);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);

char	**ft_split(const char *str, char c);
size_t	ft_split_word_count(const char *str, char c);

int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif
