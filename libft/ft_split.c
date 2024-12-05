/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes < jomendes@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:56:16 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/16 16:51:08 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	n_words;
	int	check;

	n_words = 0;
	check = 0;
	while (*s)
	{
		if (check == 0 && *s != c)
		{
			check = 1;
			n_words++;
		}
		else if (check == 1 && *s == c)
			check = 0;
		s++;
	}
	return (n_words);
}

static int	ft_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		words;
	int		i;

	if (!s)
		return (0);
	words = ft_countwords(s, c);
	ptr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (words--)
	{
		while (*s == c && *s)
			s++;
		ptr[i] = ft_substr(s, 0, ft_len(s, c));
		if (!ptr[i])
			return (0);
		s += ft_len(s, c);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
