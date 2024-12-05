/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:49:42 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/11 19:57:19 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (str + i);
		i++;
	}
	if (str[i] == '\0' && (char)c == '\0')
		return (str + i);
	return (NULL);
}
