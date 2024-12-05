/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:17 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/02 23:34:56 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_name(char	*str)
{
	int	fd;
	int	i;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		error("Map file doesn't exist\n");
	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] != '.' || str[i + 1] != 'c' \
	|| str[i + 2] != 'u' || str[i + 3] != 'b' \
	|| str[i + 4] != '\0')
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ac == 1)
		error("Not enought arguments\n");
	if (ac == 2 && !check_name(av[1]))
		return (1);
	if (ac > 2)
		error("To many arguments\n");
	return (0);	
}

int	map_heigth(char *file)
{
	int		fd;
	char	*row;
	int		counter;

	counter = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	row = get_next_line(fd);
	while (row)
	{
		if (counter == 0)
			free(row);
		row = get_next_line(fd);
		free(row);
		counter++;
	}
	free(row);
	close(fd);
	return (counter);
}

char	**get_map(char *file, t_map *map)
{
	int		fd;
	char	**maping;
	char	*row;
	int		line;

	fd = open(file, O_RDONLY);
	map->y = map_heigth(file);
	maping = ft_calloc((map->y + 1), sizeof(char *));
	line = 0;
	if (fd < 3)
	{
		error("Map not found\n");
		return (NULL);
	}
	while (line < map->y)
	{
		row = get_next_line(fd);
		maping[line++] = row;
	}
	maping[line] = NULL;
	close(fd);
	return (maping);
}
