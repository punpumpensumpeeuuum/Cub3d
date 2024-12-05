/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:43:19 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/08 15:33:59 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	int		j;
	char	*result;

	j = 0;
	if (start > ft_strlen(s))
		len = 0;
	else if ((start + len) > ft_strlen(s))
	{
		len = ft_strlen(s) - start;
	}
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (j < len)
	{
		result[j] = s[start];
		start++;
		j++;
	}
	result[j] = '\0';
	return (result); 
}
