/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:42:21 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/12 13:39:48 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_floor(t_map *map)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		if (ft_strncmp(map->file[i], "F", 1) == 0)
		{
			map->floor = map->file[i];
			return (0);
		}
		i++;
	}
	ft_putstr_fd("Floor not found\n", 2);
	return (1);
}

int	get_ceiling(t_map *map)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		if (ft_strncmp(map->file[i], "C", 1) == 0)
		{
			map->ceiling = map->file[i];
			return (0);
		}
		i++;
	}
	ft_putstr_fd("Celling not found\n", 2);
	return (1);
}

void	player_pos(t_map *map, t_player *player)
{
	int y;
	int x;

	y = 0;
	while (map->matrix[y])
	{	
		x = 0;
		while (map->matrix[y][x])
		{
			if (map->matrix[y][x] == 'N' ||
			map->matrix[y][x] == 'S' ||
			map->matrix[y][x] == 'E' ||
			map->matrix[y][x] == 'O')
			{
				player->pos_x = x;
				player->pos_y = y;
			}
			x++;
		}
		y++;
	}	
}