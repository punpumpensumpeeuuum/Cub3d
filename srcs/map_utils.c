/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:40 by elemesmo          #+#    #+#             */
/*   Updated: 2025/02/04 15:52:34 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_width(t_map *map)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	width = 0;
	while (map->matrix[i])
	{
		j = 0;
		while (map->matrix[i][j] != '\0' && map->matrix[i][j] != '\n')
			j++;
		if (width < j)
			width = j;
		i++;
	}
	map->x = width;
}

char	*create_top_bottom(t_map *map)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(map->x + 3);
	if (!str)
		return (NULL);
	while (i < map->x + 2)
	{
		str[i] = 'w';
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}

void	second_map(t_map *map)
{
	int	y;
	int x;

	y = 0;
	map->matrix_ff = malloc((map->y + 3) * sizeof(char *));
	if (!map->matrix_ff)
		return ;
	map->matrix_ff[y++] = create_top_bottom(map);
	while (y <= map->y)
	{
		map->matrix_ff[y] = malloc(map->x + 3);
		if (!map->matrix_ff[y])
			return ;
		x = 0;
		map->matrix_ff[y][x] = 'w';
		while (x <= map->x)
		{
			while (map->matrix[y - 1][x] == ' ')
			{
				map->matrix_ff[y][x + 1] = 'w';
				x++;
			}
			map->matrix_ff[y][x + 1] = map->matrix[y - 1][x];
			x++;
		}
		x = ft_strlen(map->matrix_ff[y]) - 1;
		if (y == map->y && map->matrix_ff[y][x] != '\n')
			x++;
		while(x <= map->x + 1)
		{
			map->matrix_ff[y][x] = 'w';
			x++;
		}
		map->matrix_ff[y][x] = '\n';
		map->matrix_ff[y][x + 1] = '\0';
		y++;
	}
	map->matrix_ff[y] = create_top_bottom(map);
	map->matrix_ff[y + 1] = NULL;
}

int	check_map_x(t_map *map, int y)
{
	int	x;

	x = 0;
	while (map->matrix[y][x])
	{	
		if (!(map->matrix[y][x] == ' ' || map->matrix[y][x] == '1' ||
		map->matrix[y][x] == '\n'))
			return (1);
		x++;
	}
	return (0);
}

int	check_map_y(t_map *map)
{
	int	y;
	int	x;

	y = 2;
	x = 0;
	while (map->matrix_ff[y][x] && y < map->y)
	{
		x = 0;
		while (map->matrix_ff[y][x] == 'w')
			x++;
		if (map->matrix_ff[y][x] != '1')
			return (1);
		while (map->matrix_ff[y][x] != 'w')
			x++;
		if (map->matrix_ff[y][x - 1] != '1')
			return (1);
		y++;
	}
	return (0);
}

int	check_0(t_map *map)
{
	int	x;
	int	y;

	y = 2;
	while (map->matrix_ff[y] && y < map->y)
	{
		x = 0;
		while (map->matrix_ff[y][x])
		{
			if (map->matrix_ff[y][x] == '0')
			{
				if (map->matrix_ff[y + 1][x] == 'w'
				|| map->matrix_ff[y - 1][x] == 'w')
					return (1);	
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map(t_map *map)
{
	if (!map->matrix_ff)
		return (1);
	if (check_map_x(map, 0) == 0 && check_map_x(map, map->y - 1) == 0
	&& check_map_y(map) == 0 && check_0(map) == 0)
		return (0);
	return (1);
}

void	map_index(t_map *map)
{
	int	i;

	if (!map->file)
		return ;
	i = 0;
	while (i < map->file_heigth)
	{
		if (ft_strncmp(map->file[i], "1", 1) == 0)
		{
			map->index = i;
			while (map->file[i] != NULL)
				i++;
			map->y = i - map->index;
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
	if (map->file_heigth == -1)
	{
		error("Can't open the file\n");
		return (NULL);
	}
	all_file = ft_calloc((map->file_heigth + 1), sizeof(char *));
	if (!all_file)
		return (NULL);
	line = 0;
	if (fd < 3)
	{
		error("Map not found\n");
		return (NULL);
	}
	while (line < map->file_heigth)
	{
		row = get_next_line(fd);
		all_file[line++] = row;
	}
	all_file[line] = NULL;
	close(fd);
	return (all_file);
}