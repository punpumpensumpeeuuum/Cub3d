/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/21 12:36:45 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	place_player_aux(t_vc *vc, int *i, int *j)
{
	if (vc->map.matrix[*i][*j] == 'N')
	{
		printf("valor do i = %d\n", *i);
		printf("valor do j = %d\n", *j);
		vc->player.grid_x = *j;
		vc->player.grid_y = *i;
		vc->player.facing = 270;
		vc->player.pos_x = *j + 0.5;
		vc->player.pos_y = *i + 0.5;
		vc->player.angle = 270 * (PI / 180);
		vc->player.direction_x = 0.00;
		vc->player.direction_y = -1.00;
		vc->player.plane_x = 0.66;
		vc->player.plane_y = 0.00;
	}
	else if (vc->map.matrix[*i][*j] == 'S')
		player_south(vc, *i, *j);
	else if (vc->map.matrix[*i][*j] == 'E')
		player_east(vc, *i, *j);
	else if (vc->map.matrix[*i][*j] == 'W')
		player_west(vc, *i, *j);
}

void	player_south(t_vc *vc, int i, int j)
{
	vc->player.grid_x = j;
	vc->player.grid_y = i;
	vc->player.pos_x = j + 0.5;
	vc->player.pos_y = i + 0.5;
	vc->player.angle = 90 * (PI / 180);
	vc->player.direction_x = 0.00;
	vc->player.direction_y = 1.00;
	vc->player.plane_x = -0.66;
	vc->player.plane_y = 0.00;
}

void	player_east(t_vc *vc, int i, int j)
{
	vc->player.grid_x = j;
	vc->player.grid_y = i;
	vc->player.pos_x = j + 0.5;
	vc->player.pos_y = i + 0.5;
	vc->player.angle = 0 * (PI / 180);
	vc->player.direction_x = 1.00;
	vc->player.direction_y = 0.00;
	vc->player.plane_x = 0.00;
	vc->player.plane_y = 0.66;
}

void	player_west(t_vc *vc, int i, int j)
{
	vc->player.grid_x = j;
	vc->player.grid_y = i;
	vc->player.pos_x = j + 0.5;
	vc->player.pos_y = i + 0.5;
	vc->player.angle = 180 * (PI / 180);
	vc->player.direction_x = -1.00;
	vc->player.direction_y = 0.00;
	vc->player.plane_x = 0.00;
	vc->player.plane_y = -0.66;
}

void	placeplayer(t_vc *vc)
{
	int	i;
	int	j;

	i = 0;
	while (vc->map.matrix[i])
	{
		j = 0;
		printf("valor do i antes = %d\n", i);
		printf("valor do j antes = %d\n", j);
		while (j < vc->map.matrix[i][j])
		{
			place_player_aux(vc, &i, &j);
			j++;
		}
		i++;
	}
}
