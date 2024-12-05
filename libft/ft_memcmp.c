/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:17:13 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/10 10:38:09 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)s1;
	s = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (i < n)
	{
		if (d[i] != s[i])
			return (d[i] - s[i]);
		i++;
	}
	return (0);
}
