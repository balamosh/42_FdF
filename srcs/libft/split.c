/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:57:30 by sotherys          #+#    #+#             */
/*   Updated: 2021/11/18 10:41:03 by sotherys         ###   ########.fr       */
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

static char	**ft_split_populate(char **out, const char *str, char c)
{
	size_t	wi;
	size_t	i;

	wi = 0;
	while (*str != '\0')
	{
		if (*str == c)
		{
			++str;
			continue ;
		}
		i = 0;
		while (str[i] != '\0' && str[i] != c)
			++i;
		out[wi] = ft_substr(str, 0, i);
		str += i;
		if (!out[wi])
		{
			ft_split_free(out);
			return (NULL);
		}
		++wi;
	}
	out[wi] = NULL;
	return (out);
}

void	ft_split_free(char **out)
{
	size_t	i;

	i = 0;
	while (out[i])
		free(out[i++]);
	free(out);
}

char	**ft_split(const char *str, char c)
{
	char	**out;

	if (!str)
		return (NULL);
	out = (char **) malloc(sizeof(char *) * (ft_split_word_count(str, c) + 1));
	if (!out)
		return (NULL);
	return (ft_split_populate(out, str, c));
}
