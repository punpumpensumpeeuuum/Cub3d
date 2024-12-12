/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/12 16:43:08 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_player(t_vc *vc)
{
	mlx_put_image_to_window(vc->mlx.mlx, vc->mlx.window, vc->play.sprite, vc->play.x , vc->play.y);
}

// void draw_player(t_vc *vc, int x, int y, int color)
// {
// 	int start_x;
// 	int start_y;
// 	int end_x;
// 	int end_y;
// 	int i;
// 	int j;

// 	start_x = x * vc->mlx.pixelx;
// 	start_y = y * vc->mlx.pixely;
// 	end_x = start_x + vc->mlx.pixelx;
// 	end_y = start_y + vc->mlx.pixely;
// 	i = start_y;
// 	while (i < end_y)
// 	{
// 		j = start_x;
// 		while (j < end_x)
// 		{
// 			mlx_pixel_put(vc->mlx.mlx, vc->mlx.window, j, i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

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
				vc->play.x = ((j + 1) * vc->mlx.pixelx);
				vc->play.y = ((i + 1) * (vc->mlx.pixely));
				return ;
			}
			j++;
		}
		i++;
	}
}
