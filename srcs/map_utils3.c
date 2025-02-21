/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:57:25 by dinda-si          #+#    #+#             */
/*   Updated: 2025/02/21 16:09:49 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	allocate_matrix(t_map *map)
{
	map->matrix_ff = malloc((map->y + 3) * sizeof(char *));
}

char	*fill_row(t_map *map, int y)
{
	int		x;
	char	*row;

	x = 0;
	row = malloc(map->x + 4);
	if (!row)
		return (NULL);
	row[x++] = 'w';
	while (x <= map->x && map->matrix[y][x - 1])
	{
		if (map->matrix[y - 1][x - 1] == ' ')
			row[x] = 'w';
		else
			row[x] = map->matrix[y - 1][x - 1];
		while (x <= map->x + 1)
			row[x++] = 'w';
	}
	row[x++] = '\n';
	row[x] = '\0';
	return (row);
}

void	second_map(t_map *map)
{
	int	y;

	y = 0;
	allocate_matrix(map);
	if (!map->matrix_ff)
		return ;
	map->matrix_ff[y++] = create_top_bottom(map);
	while (y <= map->y && map->matrix[y])
	{
		map->matrix_ff[y] = fill_row(map, y);
		if (!map->matrix_ff[y])
			return ;
		y++;
	}
	map->matrix_ff[y] = create_top_bottom(map);
	map->matrix_ff[y + 1] = NULL;
}

int	coma_counter(char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return (counter);
}
