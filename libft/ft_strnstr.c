/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes < jomendes@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:06:29 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/04 11:37:39 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (s2[0] == '\0')
		return ((char *) s1);
	while (s1[i] != '\0' && i < len)
	{
		while (s1[i + j] == s2[j] && i + j < len)
		{
			if (s2[j + 1] == '\0')
			{
				return ((char *) & s1[i]);
			}
			j ++;
		}
		j = 0;
		i++;
	}
	return (0);
}
