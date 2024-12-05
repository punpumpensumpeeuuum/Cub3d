/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes < jomendes@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:49:46 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/10 22:05:21 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	y;
	size_t	dst_len;

	i = ft_strlen(dst);
	dst_len = i;
	y = 0;
	if (dstsize && dst_len <= dstsize)
	{
		while (src[y] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[y];
			i++;
			y++;
		}
		dst[i] = '\0';
	}
	if (dstsize <= dst_len)
		dst_len = dstsize;
	return (dst_len + ft_strlen(src));
}
