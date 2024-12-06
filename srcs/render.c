/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/06 16:34:32 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color(char c)
{
	if (c == '0')
		return (0x000000);
	if (c == '1')
		return (0xFFFFFF);
	if (c == 'P')
		return (0xff0000);
	return (0x000000);
}

void draw_rectangle(t_vc *vc, int h, int w, int color)
{
	int i;
	int j;

	i = w * 10;
	while (i < (w * 10) + 10)
	{
		j = h * 10;
		while (j < (h * 10) + 10)
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
			color = get_color(vc->map.matrix_ff[i][j]);
			draw_rectangle(vc, i, j, color);
			j++;
		}
		i++;
	}
}
