/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:08:41 by dinda-si          #+#    #+#             */
/*   Updated: 2025/03/03 15:58:12 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	keypress(int keycode, t_vc *vc)
{
	if (keycode == 65307)
		closegame(vc);
	else if (keycode == 109)
	{
		if (vc->minimap.onoff == 1)
		{
			vc->minimap.onoff = 0;
			return (0);
		}
		vc->minimap.onoff = 1;
	}
	else if (keycode == 'w')
		vc->player.w = 1;
	else if (keycode == 'a')
		vc->player.a = 1;
	else if (keycode == 's')
		vc->player.s = 1;
	else if (keycode == 'd')
		vc->player.d = 1;
	else if (keycode == L_ARROW)
		vc->player.o = 1;
	else if (keycode == R_ARROW)
		vc->player.o = 2;
	return (0);
}

int	keyunpress(int keycode, t_vc *vc)
{
	if (keycode == 'w')
		vc->player.w = 0;
	else if (keycode == 'a')
		vc->player.a = 0;
	else if (keycode == 's')
		vc->player.s = 0;
	else if (keycode == 'd')
		vc->player.d = 0;
	else if (keycode == L_ARROW)
		vc->player.o = 0;
	else if (keycode == R_ARROW)
		vc->player.o = 0;
	return (0);
}

void	draw_floor_ceiling(t_vc *vc, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->wall_start)
	{
		my_mlx_pixel_put(vc->canva, ray->id, y, \
			get_ceiling_color(&vc->map_info));
		y++;
	}
	y = ray->wall_end + 1;
	while (y < Y_SCREEN)
	{
		my_mlx_pixel_put(vc->canva, ray->id, y, \
			get_floor_color(&vc->map_info));
		y++;
	}
}
