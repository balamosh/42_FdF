/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:57:30 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/12 15:01:48 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_split_word_count(const char *str, char c)
{
	size_t	wc;
	size_t	i;
	size_t	word_len;

	wc = 0;
	i = 0;
	word_len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			if (word_len != 0)
				++wc;
			word_len = 0;
		}
		else
			++word_len;
		++i;
	}
	if (word_len > 0)
		return (wc + 1);
	return (wc);
}

static int	ft_substr_to_sep(const char *str, char c, char **dup)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		++i;
	if (i == 0)
		return (0);
	*dup = ft_substr(str, 0, i);
	return (i);
}

char	**ft_split(const char *str, char c)
{
	size_t	wi;
	char	**out;

	if (!str)
		return (NULL);
	out = (char **) malloc(sizeof(char *) * (ft_split_word_count(str, c) + 1));
	if (NULL == out)
		return (NULL);
	wi = 0;
	while (*str != '\0')
	{
		if (*str == c)
		{
			++str;
			continue ;
		}
		str += ft_substr_to_sep(str, c, out + wi);
		++wi;
	}
	out[wi] = NULL;
	return (out);
}
