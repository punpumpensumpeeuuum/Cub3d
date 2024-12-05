/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:18:27 by jomendes          #+#    #+#             */
/*   Updated: 2023/11/23 16:10:10 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*str;
	int			i;

	i = 0;
	if (read(fd, 0, 0) < 0 || FOPEN_MAX <= fd || BUFFER_SIZE <= 0)
	{
		if (fd > 0 && fd < FOPEN_MAX)
			while (buffer[fd][i])
				buffer[fd][i++] = '\0';
		return (NULL);
	}
	str = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		str = ft_strjoin(str, buffer[fd]);
		buffer_clean(buffer[fd]);
		if (str[ft_linelen(str) - 1] == '\n')
			return (str);
	}
	return (str);
}
