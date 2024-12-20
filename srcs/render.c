/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/20 13:47:16 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color(char c)
{
	if (c == '0')
		return (0x000000);
	if (c == '1')
		return (0xFFFFFF);
	return (0x000000);
}

void draw_rectangle(t_vc *vc, int h, int w, int color)
{
	int i;
	int j;

	i = w * (X_SCREEN / 80);
	while (i < (w * (X_SCREEN / 80)) + (X_SCREEN / 80))
	{
		j = h * (Y_SCREEN / 45);
		while (j < (h * (Y_SCREEN / 45)) + (Y_SCREEN / 45))
		{
			mlx_pixel_put(vc->mlx.mlx, vc->mlx.window, i, j, color);
			j++;
		}
		i++;
	}
}

void	get_pos(t_vc *vc, int x, int y)
{
	vc->map.x = x;
	vc->map.y = y;
}

void	drawminimap(t_vc *vc)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (vc->map.matrix_ff[i])
	{
		j = 0;
		while (vc->map.matrix_ff[i][j])
		{
			draw_rectangle(vc, (vc->player.pos_x / (vc->mlx.x / 80)), (vc->player.pos_y / (vc->mlx.y / 45)), PLAYERCOLOR);
			color = get_color(vc->map.matrix_ff[i][j]);
			draw_rectangle(vc, i, j, color);
			j++;
		}
		i++;
	}
}

void	placeplayer(t_vc *vc)
{
	int	i;
	int	j;

	i = 0;
	while (vc->map.matrix[i])
	{
		j = 0;
		while (j < vc->map.matrix[i][j])
		{
			if (vc->map.matrix[i][j] == 'N' || vc->map.matrix[i][j] == 'O')
			{
				vc->player.facing = 270;
				vc->player.pos_x = j;
				vc->player.pos_y = i;
				vc->player.direction_x = 0.00;
				vc->player.direction_y = -1.00;
				//vc->player.pos_x = ((i + 1) * (vc->mlx.x / 80));
				//vc->player.pos_y = ((j + 1) * (vc->mlx.y / 45));
				draw_rectangle(vc, vc->player.pos_x, vc->player.pos_y, PLAYERCOLOR);
			}
			else if (vc->map.matrix[i][j] == 'S')
			{
				vc->player.pos_x = j;
				vc->player.pos_y = i;
				vc->player.direction_x = 0.00;
				vc->player.direction_y = 1.00;
				draw_rectangle(vc, vc->player.pos_x, vc->player.pos_y, PLAYERCOLOR);
			}
			j++;
		}
		i++;
	}
}
