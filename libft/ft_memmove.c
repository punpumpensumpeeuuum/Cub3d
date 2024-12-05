/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes < jomendes@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:52:17 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/16 10:38:41 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (s > d)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (s < d)
	{
		while (len-- > 0)
		{
			d[len] = s[len];
		}
	}
	return (dst);
}
