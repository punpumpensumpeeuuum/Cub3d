/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:06:12 by jomendes          #+#    #+#             */
/*   Updated: 2023/11/22 12:00:50 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_linelen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = malloc(ft_linelen(s1) + ft_linelen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && s2[j] != '\n')
	{
		str[i + j] = s2[j];
		j++;
	}
	if (s2[j] == '\n')
		str[i + j++] = '\n';
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

void	buffer_clean(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == '\n' && j == -1)
			j = 0;
		else if (j != -1)
			str[j++] = str[i];
		str[i++] = '\0';
	}
}
