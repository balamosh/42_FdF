/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:47:04 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/12 16:47:12 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	s_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		start = s_len;
	len = ft_min(len, s_len - start);
	new = (char *) malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			new[j++] = s[i];
		++i;
	}
	new[j] = '\0';
	return (new);
}
