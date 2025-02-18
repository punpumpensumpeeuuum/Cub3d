/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:27:25 by dinda-si          #+#    #+#             */
/*   Updated: 2025/02/18 16:42:26 by jomendes         ###   ########.fr       */
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
	while (vc->map.matrix[i])
	{
		j = 0;
		while (vc->map.matrix[i][j])
		{
			if (vc->map.matrix[i][j])
			{
				draw_rectangle(vc, vc->map.matrix[i][j], i, j);
				mlx_put_image_to_window(vc->mlx.mlx, vc->mlx.window, vc->minimap.player, (vc->player.pos_x - 0.5) * 16 , (vc->player.pos_y - 0.5) * 16 );
			}
			j++;
		}
		i++;
	}
}

