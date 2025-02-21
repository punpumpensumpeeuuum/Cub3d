/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:40 by elemesmo          #+#    #+#             */
/*   Updated: 2025/02/21 16:00:52 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
