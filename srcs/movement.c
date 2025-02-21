/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:27:25 by dinda-si          #+#    #+#             */
/*   Updated: 2025/02/21 11:59:23 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	frente_movimento(t_vc *vc)
{
	if (vc->player.w == 1)
	{
		if (vc->map.matrix[(int)(vc->player.pos_y + \
			vc->player.direction_y * MOVE_SPEED)]
			[(int)(vc->player.pos_x)] != '1')
			vc->player.pos_y += vc->player.direction_y * MOVE_SPEED;
		if (vc->map.matrix[(int)(vc->player.pos_y)]
			[(int)(vc->player.pos_x + \
			vc->player.direction_x * MOVE_SPEED)] != '1')
			vc->player.pos_x += vc->player.direction_x * MOVE_SPEED;
	}
	else if (vc->player.s == 1)
	{
		if (vc->map.matrix[(int)(vc->player.pos_y - \
		vc->player.direction_y * MOVE_SPEED)]
			[(int)(vc->player.pos_x)] != '1')
			vc->player.pos_y -= vc->player.direction_y * MOVE_SPEED;
		if (vc->map.matrix[(int)(vc->player.pos_y)]
			[(int)(vc->player.pos_x - \
			vc->player.direction_x * MOVE_SPEED)] != '1')
			vc->player.pos_x -= vc->player.direction_x * MOVE_SPEED;
	}
}

void	lado_movimento(t_vc *vc)
{
	if (vc->player.d == 1)
	{
		if (vc->map.matrix[(int)(vc->player.pos_y + \
		vc->player.direction_x * MOVE_SPEED)]
			[(int)(vc->player.pos_x)] != '1')
			vc->player.pos_y += vc->player.direction_x * MOVE_SPEED;
		if (vc->map.matrix[(int)(vc->player.pos_y)]
			[(int)(vc->player.pos_x - \
			vc->player.direction_y * MOVE_SPEED)] != '1')
			vc->player.pos_x -= vc->player.direction_y * MOVE_SPEED;
	}
	else if (vc->player.a == 1)
	{
		if (vc->map.matrix[(int)(vc->player.pos_y - \
		vc->player.direction_x * MOVE_SPEED)]
			[(int)(vc->player.pos_x)] != '1')
			vc->player.pos_y -= vc->player.direction_x * MOVE_SPEED;
		if (vc->map.matrix[(int)(vc->player.pos_y)]
			[(int)(vc->player.pos_x + \
			vc->player.direction_y * MOVE_SPEED)] != '1')
			vc->player.pos_x += vc->player.direction_y * MOVE_SPEED;
	}
}

void	move_camera(t_vc *vc)
{
	double	old_camera_x;

	old_camera_x = vc->player.plane_x;
	if (vc->player.o == 1)
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
	else if (vc->player.o == 2)
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
	if (vc->player.a == 1 || vc->player.d == 1)
		lado_movimento(vc);
	if (vc->player.o != 0)
		move_camera(vc);
}
