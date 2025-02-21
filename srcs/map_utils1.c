/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:42:21 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/21 15:53:10 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_floor(t_map *map, t_map_info *info)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		if (ft_strncmp(map->file[i], "F ", 2) == 0)
		{
			info->floor = map->file[i];
			return (0);
		}
		i++;
	}
	ft_putstr_fd("Floor not found\n", 2);
	return (1);
}

int	get_ceiling(t_map *map, t_map_info *info)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		if (ft_strncmp(map->file[i], "C ", 2) == 0)
		{
			info->ceiling = map->file[i];
			return (0);
		}
		i++;
	}
	ft_putstr_fd("Celling not found\n", 2);
	return (1);
}

void	map_index(t_map *map)
{
	int	i;
	int	counter;

	if (!map->file)
		return ;
	i = 0;
	counter = 0;
	while (i < map->file_heigth)
	{
		if (map->file[i])
		{
			if (ft_strncmp(map->file[i], "\n", 1) == 0)
				i++;
			if (ft_strncmp(map->file[i], "\n", 1) != 0)
				counter++;
			if (counter == 7)
			{
				map->index = i;
				map->y = map->file_heigth - map->index;
				return ;
			}
		}
		i++;
	}
}

int	get_file_heigth(char *file)
{
	int		fd;
	char	*row;
	int		counter;

	counter = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	row = get_next_line(fd);
	while (row)
	{
		free(row);
		row = get_next_line(fd);
		counter++;
	}
	close(fd);
	return (counter);
}

char	**get_file(char *file, t_map *map)
{
	int		fd;
	char	**all_file;
	char	*row;
	int		line;

	fd = open(file, O_RDONLY);
	map->file_heigth = get_file_heigth(file);
	if (map->file_heigth == -1 || fd < 3)
	{
		error("Can't open the file\n");
		return (NULL);
	}
	all_file = ft_calloc((map->file_heigth + 1), sizeof(char *));
	if (!all_file)
		return (NULL);
	line = 0;
	while (line < map->file_heigth)
	{
		row = get_next_line(fd);
		all_file[line++] = row;
	}
	all_file[line] = NULL;
	close(fd);
	return (all_file);
}
