/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:27:25 by dinda-si          #+#    #+#             */
/*   Updated: 2025/02/05 12:25:21 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_rectangle(t_vc *vc, char c, int i, int j)
{
	if (c == '1')
		mlx_put_image_to_window(vc->mlx.mlx, vc->mlx.window, vc->minimap.wall, j * 16, i * 16);
	else
		mlx_put_image_to_window(vc->mlx.mlx, vc->mlx.window, vc->minimap.floor,j * 16, i * 16);
}

void	drawminimap(t_vc *vc)
{
	int	i;
	int	j;

	i = 0;
	while (vc->map.matrix_ff[i])
	{
		j = 0;
		while (vc->map.matrix_ff[i][j])
		{
			if (vc->map.matrix_ff[i][j])
			{
				draw_rectangle(vc, vc->map.matrix_ff[i][j], i, j);
				mlx_put_image_to_window(vc->mlx.mlx, vc->mlx.window, vc->minimap.player, vc->player.pos_x , vc->player.pos_y);
			}
			j++;
		}
		i++;
	}
}

