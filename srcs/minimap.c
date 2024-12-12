/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:27:25 by dinda-si          #+#    #+#             */
/*   Updated: 2024/12/12 15:38:00 by dinda-si         ###   ########.fr       */
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
				draw_player(vc);
			}
			j++;
		}
		draw_player(vc);
		i++;
	}
}
