/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/05 05:01:52 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color(char c)
{
	if (c == '0')
		return (0x00FF00);
	if (c == '1')
		return (0xFFFFFF);
	if (c == 'P')
		return (0xFFFF00);
	return (0x00FF00);
}

void draw_rectangle(t_vc *vc, int h, int w, int color)
{
    int i = w * 10; // Fixed size for testing
    int j;

    while (i < (w * 10) + 10) // 10x10 rectangles
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

void drawminimap(t_vc *vc)
{
    int i = 0;
    int j;
    int color;

    if (!vc->map.matrix)
    {
        printf("Error: Map matrix is NULL!\n");
        return;
    }

    while (vc->map.matrix[i])
    {
        j = 0;
        while (vc->map.matrix[i][j])
        {
            color = get_color(vc->map.matrix[i][j]);
            draw_rectangle(vc, i, j, color);
			printf("Drawing minimap cell at (%d, %d) with color %d\n", i, j, color);
            j++;
        }
        i++;
    }
}
