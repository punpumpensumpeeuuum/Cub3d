/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/11 16:30:39 by dinda-si         ###   ########.fr       */
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

	i = w * vc->mlx.pixelx;
	while (i < (w * vc->mlx.pixelx) + vc->mlx.pixelx)
	{
		j = h * (vc->mlx.pixely);
		while (j < (h * (vc->mlx.pixely)) + (vc->mlx.pixely))
		{
			mlx_pixel_put(vc->mlx.mlx, vc->mlx.window, i, j, color);
			j++;
		}
		i++;
	}
}

void draw_minimap_background(t_vc *vc, int x, int y, int color)
{
	int width;
	int height;
	int	i;
	int	j;

	i = 0;
	width = vc->mlx.pixelx * x;
	height = vc->mlx.pixely * y;
	while (i < height)
	{	
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(vc->mlx.mlx, vc->mlx.window, j, i, color);
			j++;
		}
		i++;
	}
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
			if (vc->map.matrix_ff[i][j])
			{
				color = get_color(vc->map.matrix_ff[i][j]);
				draw_rectangle(vc, i, j, color);
				draw_rectangle(vc, (vc->play.x / vc->mlx.pixelx), (vc->play.y / vc->mlx.pixely), PLAYERCOLOR);
			}
			j++;
		}
		i++;
		draw_rectangle(vc, (vc->play.x / vc->mlx.pixelx), (vc->play.y / vc->mlx.pixely), PLAYERCOLOR);
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
				vc->play.x = ((i + 1) * vc->mlx.pixelx);
				vc->play.y = ((j + 1) * (vc->mlx.pixely));
				draw_rectangle(vc, vc->play.x, vc->play.y, PLAYERCOLOR);
			}
			j++;
		}
		i++;
	}
}
