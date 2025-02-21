/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:38:37 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/10 17:22:51 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dda_style(t_vc *vc)
{
	int		x;
	double	ray_camera;

	x = 0;
	while (x < X_SCREEN)
	{
		ray_camera = ((2 * x) / (double)X_SCREEN - 1);
		vc->ray.id = x;
		vc->ray.pos_x = vc->player.pos_x;
		vc->ray.pos_y = vc->player.pos_y;
		vc->ray.direction_x = vc->player.direction_x + \
		vc->player.plane_x * ray_camera;
		vc->ray.direction_y = vc->player.direction_y + \
		vc->player.plane_y * ray_camera;
		vc->ray.delta_dist_x = fabs(1 / vc->ray.direction_x);
		vc->ray.delta_dist_y = fabs(1 / vc->ray.direction_y);
		dda_step_calc(vc);
		dda_real_distance_calc(vc);
		dda_wall_height(&vc->ray);
		dda_side_selector(vc, &vc->ray, &vc->player, &vc->map_info);
		x++;
	}
	mlx_put_image_to_window(vc->mlx.mlx, \
		vc->mlx.window, vc->canva->img_ptr, 0, 0);
}

void	dda_step_calc(t_vc *vc)
{
	if (vc->ray.direction_x < 0)
	{
		vc->ray.step_x = -1;
		vc->ray.distance_x = ((vc->player.pos_x) - (vc->ray.pos_x))
			* vc->ray.delta_dist_x;
	}
	else
	{
		vc->ray.step_x = 1;
		vc->ray.distance_x = ((vc->ray.pos_x) + 1.0 - (vc->player.pos_x))
			* vc->ray.delta_dist_x;
	}
	if (vc->ray.direction_y < 0)
	{
		vc->ray.step_y = -1;
		vc->ray.distance_y = ((vc->player.pos_y) - \
		(vc->ray.pos_y)) * vc->ray.delta_dist_y;
	}
	else
	{
		vc->ray.step_y = 1;
		vc->ray.distance_y = ((vc->ray.pos_y) + 1.0 - \
		(vc->player.pos_y))
			* vc->ray.delta_dist_y;
	}
}

void	dda_real_distance_calc(t_vc *vc)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vc->ray.distance_x < vc->ray.distance_y)
		{
			vc->ray.distance_x += vc->ray.delta_dist_x;
			vc->ray.pos_x += vc->ray.step_x;
			vc->ray.side = 0;
		}
		else
		{
			vc->ray.distance_y += vc->ray.delta_dist_y;
			vc->ray.pos_y += vc->ray.step_y;
			vc->ray.side = 1;
		}
		if (vc->map.matrix[(int)(vc->ray.pos_y)][(int)(vc->ray.pos_x)] == '1')
			hit = 1;
	}
	if (vc->ray.side == 0)
		vc->ray.real_size = (vc->ray.distance_x - vc->ray.delta_dist_x);
	else
		vc->ray.real_size = (vc->ray.distance_y - vc->ray.delta_dist_y);
}

void	dda_wall_height(t_ray *ray)
{
	ray->line_height = (int)(Y_SCREEN / ray->real_size);
	ray->wall_start = -ray->line_height / 2 + Y_SCREEN / 2;
	if (ray->wall_start < 0 || ray->line_height < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->line_height / 2 + Y_SCREEN / 2;
	if (ray->wall_end >= Y_SCREEN || ray->line_height < 0)
		ray->wall_end = Y_SCREEN - 1;
}

void	dda_side_selector(t_vc *vc, t_ray *ray, \
			t_player *player, t_map_info *info)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->pos_y + ray->real_size * ray->direction_y;
	else
		wall_x = player->pos_x + ray->real_size * ray->direction_x;
	wall_x -= floor(wall_x);
	ray->x_texture = (int)(wall_x * 64);
	if (ray->side == 0 && ray->direction_x > 0)
		ray->x_texture = 64 - ray->x_texture - 1;
	if (ray->side == 1 && ray->direction_y < 0)
		ray->x_texture = 64 - ray->x_texture - 1;
	if (ray->side == 0 && ray->direction_x > 0)
		draw_walls(vc, ray, info->ea_texture);
	else if (ray->side == 0 && ray->direction_x < 0)
		draw_walls(vc, ray, info->we_texture);
	else if (ray->side == 1 && ray->direction_y > 0)
		draw_walls(vc, ray, info->so_texture);
	else if (ray->side == 1 && ray->direction_y < 0)
		draw_walls(vc, ray, info->no_texture);
}
