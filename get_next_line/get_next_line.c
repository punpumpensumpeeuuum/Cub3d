/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:03:40 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/18 17:22:04 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	int			i;

	i = 0;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		while (i <= BUFFER_SIZE)
		{
			buffer[i] = '\0';
			i++;
		}
		return (NULL);
	}
	str = NULL;
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		str = ft_strjoin(str, buffer);
		buffer_clean(buffer);
		if (str[ft_linelen(str) - 1] == '\n')
			return (str);
	}
	return (str);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	char	*line;

// 	fd1 = open("output.txt", O_RDONLY);
// 	fd2 = open("text.txt", O_RDONLY);
// 	line = get_next_line(fd1);
// 	if (line != NULL)
// 	{
// 		printf("Linha lida 1: %s\n", line);
// 		free(line);
// 	}
// 	line = get_next_line(fd2);
// 	if (line != NULL)
// 	{
// 		printf("Linha lida 2: %s\n", line);
// 		free(line);
// 	}
// 	close(fd2);
// 	close(fd1);
// 	return (0);
// }
