/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:03:05 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/21 12:04:26 by jomendes         ###   ########.fr       */
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

int	get_raycolor(int tex_x, int tex_y, t_data *data)
{
	int	color;
	int	offset;

	offset = tex_y * data->line_length + tex_x * (data->bits_per_pixel / 8);
	color = *(int *)(data->addr + offset);
	return (color);
}

void	draw_walls(t_vc *vc, t_ray *ray, t_data *texture)
{
	double	step;
	double	texture_pos;
	int		texture_y;
	int		color;
	int		y;

	step = 1.0 * texture->img_size_y / ray->line_height;
	texture_pos = (ray->wall_start - Y_SCREEN / 2
			+ ray->line_height / 2) * step;
	y = ray->wall_start;
	while (y < ray->wall_end)
	{
		texture_y = (int)texture_pos & (texture->img_size_y - 1);
		color = my_pixel_get(texture, ray->id, texture_y);
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
