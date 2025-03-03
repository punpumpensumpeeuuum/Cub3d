/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:54:04 by dinda-si          #+#    #+#             */
/*   Updated: 2025/03/03 13:52:30 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	one_player(t_map *map)
{
	int	x;
	int	y;
	int	counter;

	y = 0;
	counter = 0;
	while (map->matrix[y])
	{
		x = 0;
		while (map->matrix[y][x])
		{
			if (map->matrix[y][x] == 'N'
			|| map->matrix[y][x] == 'S'
			|| map->matrix[y][x] == 'E'
			|| map->matrix[y][x] == 'W')
				counter++;
			x++;
		}
		y++;
	}
	if (counter == 1)
		return (0);
	else
		return (1);
}

int	check_map(t_map *map, t_vc *vc)
{
	if (!map->matrix_ff)
	{
		free_game(vc);
		exit(1);
		return (1);
	}
	if (valid_chars(map) == 0 && check_map_x(map, 0) == 0 && \
		check_map_x(map, map->y - 1) == 0
		&& check_closed(map) == 0 && check_0(map) == 0 && \
		check_textures(map) == 0
		&& where_is_player(map) == 0 && one_player(map) == 0)
		return (0);
	free_game(vc);
	ft_putstr_fd("Error in map!\n", 2);
	exit(1);
	return (1);
}
