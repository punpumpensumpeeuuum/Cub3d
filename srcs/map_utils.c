/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:40 by elemesmo          #+#    #+#             */
/*   Updated: 2025/02/18 16:28:57 by jomendes         ###   ########.fr       */
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
	str = malloc(map->x + 4);
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
	map->matrix_ff[y] = create_top_bottom(map);
	y++;
	// printf("valor do map->y = %d\n", map->y);
	// while (y <= map->y)
	{
		map->matrix_ff[y] = malloc(map->x + 4);
		if (!map->matrix_ff[y])
			return ;
		x = 0;
		map->matrix_ff[y][x] = 'w';
		// printf("valor do x = %d\n", x);
		// printf("valor do map->x = %d\n", map->x);
		while (x <= map->x)
		{
			// printf("map->matrix[y - 1][x] = >%c<\n", map->matrix[y - 1][x]);
			while (map->matrix[y - 1][x] == ' ')
			{
				printf("ENTROU\n");
				map->matrix_ff[y][x + 1] = 'w';
				x++;
			}
			map->matrix_ff[y][x + 1] = map->matrix[y - 1][x];
			x++;
		}
		if (y == map->y)
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
		{
			printf("Error on check_map_x!\n");
			return (1);
		}
		x++;
	}
	return (0);
}

int	check_map_y(t_map *map)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < map->y)
	{
		while (map->matrix[y][x] == ' ')
			x++;
		if (map->matrix[y][x] == '0')
		{
			printf("%d\n", y);
			ft_putstr_fd("Errooor on check_mapeee_y\n", 2);
			return (1);
		}
		y++;
		x = 0;
	}
	y = 0;
	while (y < map->y)
	{
		printf("c = .%d.\n", map->matrix[y][ft_strlen(map->matrix[y]) - 2]);
		if ((map->matrix[y][0] != '1' && map->matrix[y][0] != ' ') 
		|| (map->matrix[y][ft_strlen(map->matrix[y]) - 2] != '1'
		&& map->matrix[y][ft_strlen(map->matrix[y]) - 2] != ' '))
		{
			ft_putstr_fd("Error on check_map_y\n", 2);
			return (1);
		}
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
				{
					printf("Error on check_0!\n");
					return (1);
				}
						
			}
			x++;
		}
		y++;
	}
	return (0);
}

int valid_chars(t_map *map)
{
	int x;
	int y;

	y = 0;
	while (map->matrix[y])
	{
		x = 0;
		while (map->matrix[y][x])
		{
			if (!(map->matrix[y][x] == '1' || map->matrix[y][x] == '0'
			|| map->matrix[y][x] == ' ' || map->matrix[y][x] == 'B'
			|| map->matrix[y][x] == 'N' || map->matrix[y][x] == 'S'
			|| map->matrix[y][x] == 'E' || map->matrix[y][x] == 'W'
			|| map->matrix[y][x] == '\n'))
			{
				ft_putstr_fd("Invalid character in the map\n", 2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_textures(t_map *map)
{
	int	y;
	int counter = 0;

	y = 0;
	counter = 0;
	while (map->file[y])
	{
		if (ft_strncmp(map->file[y], "NO", 2) == 0 || ft_strncmp(map->file[y], "SO", 2) == 0
		|| ft_strncmp(map->file[y], "EA", 2) == 0 || ft_strncmp(map->file[y], "WE", 2) == 0)
			counter++;
		y++;
	}
	if (counter != 4)
	{
		ft_putstr_fd("Error on textures!\n", 2);
		return (1);

	}
	return (0);
}

int	check_map(t_map *map)
{
	if (!map->matrix_ff)
		return (1);
	if (valid_chars(map) == 0 && check_map_x(map, 0) == 0 && check_map_x(map, map->y - 1) == 0
	&& check_map_y(map) == 0 && check_0(map) == 0 && check_textures(map) == 0)
		return (0);
	return (1);
}

void	map_index(t_map *map)
{
	int	i;
	int counter;

	if (!map->file)
		return ;
	i = 0;
	counter = 0;
	while (i < map->file_heigth)
	{
		if (map->file[i])
		{
			if (ft_strncmp(map->file[i], "\n" , 1) == 0)
				i++;
			if (ft_strncmp(map->file[i], "\n" , 1) != 0)
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