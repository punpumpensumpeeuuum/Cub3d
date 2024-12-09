/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/09 17:04:11 by dinda-si         ###   ########.fr       */
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

	i = w * (vc->mlx.x / 80);
	while (i < (w * (vc->mlx.x / 80)) + (vc->mlx.x / 80))
	{
		j = h * (vc->mlx.y / 45);
		while (j < (h * (vc->mlx.y / 45)) + (vc->mlx.y / 45))
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
			draw_rectangle(vc, (vc->play.x / (vc->mlx.x / 80)), (vc->play.y / (vc->mlx.y / 45)), PLAYERCOLOR);
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
			if (vc->map.matrix[i][j] == 'P')
			{
				vc->play.x = (i * (vc->mlx.x / 80));
				vc->play.y = (j * (vc->mlx.y / 45));
				draw_rectangle(vc, vc->play.x, vc->play.y, PLAYERCOLOR);
			}
			j++;
		}
		i++;
	}
}
