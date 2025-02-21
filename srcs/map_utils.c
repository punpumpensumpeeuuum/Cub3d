/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:40 by elemesmo          #+#    #+#             */
/*   Updated: 2025/02/21 12:46:17 by jomendes         ###   ########.fr       */
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
	int	x;

	y = 0;
	map->matrix_ff = malloc((map->y + 3) * sizeof(char *));
	if (!map->matrix_ff)
		return ;
	map->matrix_ff[y] = create_top_bottom(map);
	y++;
	while (y <= map->y && map->matrix[y])
	{
		map->matrix_ff[y] = malloc(map->x + 4);
		if (!map->matrix_ff[y])
			return ;
		x = 0;
		map->matrix_ff[y][x] = 'w';
		while (x <= map->x && map->matrix[y][x])
		{
			while (map->matrix[y - 1][x] == ' ')
			{
				map->matrix_ff[y][x + 1] = 'w';
				x++;
			}
			map->matrix_ff[y][x + 1] = map->matrix[y - 1][x];
			x++;
		}
		if (y == map->y && map->matrix[y])
			x = ft_strlen(map->matrix_ff[y]) - 1;
		if (y == map->y && map->matrix_ff[y][x] != '\n')
			x++;
		while (x <= map->x + 1 && map->matrix[y][x])
		{
			map->matrix_ff[y][x] = 'w';
			x++;
		}
		map->matrix_ff[y][x] = '\n';
		map->matrix_ff[y][x + 1] = '\0';
		printf("valor do x = %d\n", x);
		printf("valor do y = %d\n", y);
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
			printf("str = %s\n", map->matrix[y]);
			printf("Error on check_map_x!\n");
			return (1);
		}
		x++;
	}
	return (0);
}

int	check_closed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y && map->matrix[y])
	{
		x = 0;
		while (x < map->x && map->matrix[y][x])
		{
			if (map->matrix[y][x] == ' ')
			{
				if (map->matrix[y][x + 1] == ' ')
					x++;
				else if (map->matrix[y][x + 1] != '1')
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_0(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y && map->matrix[y])
	{
		x = 0;
		while (x < map->x && map->matrix[y][x])
		{
			if (map->matrix[y][x] == '0')
			{
				if (map->matrix[y][x + 1] == ' '
				|| map->matrix[y][x + 1] == '\n'
				|| map->matrix[y][x + 1] == '\0')
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	valid_chars(t_map *map)
{
	int	x;
	int	y;

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
	int	counter;

	y = 0;
	counter = 0;
	while (map->file[y])
	{
		if (ft_strncmp(map->file[y], "NO", 2) == 0 || \
			ft_strncmp(map->file[y], "SO", 2) == 0
			|| ft_strncmp(map->file[y], "EA", 2) == 0 || \
			ft_strncmp(map->file[y], "WE", 2) == 0)
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

int	where_is_player(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->matrix[y])
	{
		x = 0;
		while (map->matrix[y][x])
		{
			if (map->matrix[y][x] == 'N'
			|| map->matrix[y][x] == 'S'
			|| map->matrix[y][x] == 'E'
			|| map->matrix[y][x] == 'W')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map(t_map *map)
{
	if (!map->matrix_ff)
		return (1);
	if (valid_chars(map) == 0 && check_map_x(map, 0) == 0 && \
		check_map_x(map, map->y - 1) == 0
		&& check_closed(map) == 0 && check_0(map) == 0 && \
		check_textures(map) == 0
		&& where_is_player(map) == 0)
		return (0);
	return (1);
}
