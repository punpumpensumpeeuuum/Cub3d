/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:27:25 by dinda-si          #+#    #+#             */
/*   Updated: 2025/02/05 12:25:21 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	frente_movimento(t_vc *vc)
{
	if (vc->player.w == 1)
	{
		// Calculate the new potential positions
		float new_pos_x = vc->player.pos_x + vc->player.direction_x * MOVE_SPEED;
		float new_pos_y = vc->player.pos_y + vc->player.direction_y * MOVE_SPEED;
	
		// Debug: Print the current positions and directions
		printf("Current pos_x: %d, pos_y: %d\n", vc->player.pos_x, vc->player.pos_y);
		printf("Moving by direction_x: %f, direction_y: %f\n", vc->player.direction_x, vc->player.direction_y);
		printf("New potential pos_x: %f, pos_y: %f\n", new_pos_x, new_pos_y);
	
		// Check if the new Y position is valid (not a wall)
		if (vc->map.matrix[(int)(new_pos_y / 16)][(int)(vc->player.pos_x / 16)] != '1')
		{
			printf("New Y position is valid\n");
			vc->player.pos_y = new_pos_y;
		}
	
		// Check if the new X position is valid (not a wall)
		if (vc->map.matrix[(int)(vc->player.pos_y / 16)][(int)(new_pos_x / 16)] != '1')
		{
			printf("New X position is valid\n");
			vc->player.pos_x = new_pos_x;
		}
	}
	
	
	// else if (vc->player.s == 1)
	// {
	// 	if (map->map[(int)(player->pos.y - player->direction.y * MOVE_SPEED)]
	// 		[(int)(player->pos.x)] != '1')
	// 		player->pos.y -= player->direction.y * MOVE_SPEED;
	// 	if (map->map[(int)(player->pos.y)]
	// 		[(int)(player->pos.x - player->direction.x * MOVE_SPEED)] != '1')
	// 		player->pos.x -= player->direction.x * MOVE_SPEED;
	// }
}

// void	lado_movimento(t_vc *vc)
// {

// }

void	move_camera(t_vc *vc)
{
	double	old_camera_x;

	old_camera_x = vc->player.plane_x;
	if (vc->player.o == 1) // left
	{
		vc->player.direction_x = vc->player.direction_x * cos(-0.1)
			- vc->player.direction_y * sin(-0.1);
		vc->player.direction_y = vc->player.direction_x * sin(-0.1)
			+ vc->player.direction_y * cos(-0.1);
		vc->player.plane_x = vc->player.plane_x * cos(-0.1)
			- vc->player.plane_y * sin(-0.1);
		vc->player.plane_y = old_camera_x * sin(-0.1)
			+ vc->player.plane_y * cos(-0.1);
	}
	else if (vc->player.o == 2) // right
	{
		vc->player.direction_x = vc->player.direction_x * cos(0.1)
			- vc->player.direction_y * sin(0.1);
		vc->player.direction_y = vc->player.direction_x * sin(0.1)
			+ vc->player.direction_y * cos(0.1);
		vc->player.plane_x = vc->player.plane_x * cos(0.1)
			- vc->player.plane_y * sin(0.1);
		vc->player.plane_y = old_camera_x * sin(0.1)
			+ vc->player.plane_y * cos(0.1);
	}
}

void	movemnt(t_vc *vc)
{
	if (vc->player.w == 1 || vc->player.s == 1)
		frente_movimento(vc);
	// if (vc->player.a == 1 || vc->player.d == 1)
	// 	lado_movimento(vc);
	if (vc->player.o != 0)
	move_camera(vc);
}
