/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/20 17:49:04 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
				vc->player.grid_x = j;
				vc->player.grid_y = i;	
				vc->player.facing = 270;
				vc->player.pos_x = ((j + 1) * vc->mlx.pixelx);
				vc->player.pos_y = ((i + 1) * (vc->mlx.pixely));
				vc->player.direction_x = 0.00;
				vc->player.direction_y = -1.00;
			}
			if (vc->map.matrix[i][j] == 'S')
			{
				vc->player.grid_x = j;
				vc->player.grid_y = i;		
				vc->player.pos_x = ((j + 1) * vc->mlx.pixelx);
				vc->player.pos_y = ((i + 1) * (vc->mlx.pixely));
				vc->player.direction_x = 0.00;
				vc->player.direction_y = 1.00;
			}
			j++;
		}
		i++;
	}
}
