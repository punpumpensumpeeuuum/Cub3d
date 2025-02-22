/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:03:05 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/21 15:48:54 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_pixel_get(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_walls(t_vc *vc, t_ray *ray, t_data *texture)
{
	double	step;
	double	texture_pos;
	int		texture_y;
	int		texture_x;
	int		color;
	int		y;
	double	wall_x;

	step = 1.0 * 64 / ray->line_height;
	texture_pos = (ray->wall_start - (Y_SCREEN / 2
				+ ray->line_height / 2)) * step;
	if (texture_pos < 0)
		texture_pos = 0;
	if (ray->side == 0)
		wall_x = vc->player.pos_y + ray->real_size * ray->direction_y;
	else
		wall_x = vc->player.pos_x + ray->real_size * ray->direction_x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * texture->img_size_x);
	if ((ray->side == 0 && ray->direction_x > 0) || (ray->side == 1 && ray->direction_y < 0))
		texture_x = texture->img_size_x - texture_x - 1;
	y = ray->wall_start;
	while (y < ray->wall_end)
	{
		texture_y = (int)texture_pos % texture->img_size_y;
		color = my_pixel_get(texture, texture_x, texture_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(vc->canva, ray->id, y, color);
		texture_pos += step;
		y++;
	}
	draw_floor_ceiling(vc, ray);
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
