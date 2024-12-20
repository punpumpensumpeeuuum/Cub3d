/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:42:21 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/20 13:16:36 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_floor(t_map *map, t_map_info *info)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		if (ft_strncmp(map->file[i], "F", 1) == 0)
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
		if (ft_strncmp(map->file[i], "C", 1) == 0)
		{
			info->ceiling = map->file[i];
			return (0);
		}
		i++;
	}
	ft_putstr_fd("Celling not found\n", 2);
	return (1);
}
