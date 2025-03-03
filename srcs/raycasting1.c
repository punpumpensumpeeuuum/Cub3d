/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:03:05 by jomendes          #+#    #+#             */
/*   Updated: 2025/03/03 15:58:31 by jomendes         ###   ########.fr       */
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

void	compute_wall_texture_coords(t_vc *vc,
	t_data *texture, double *texture_pos, int *texture_x)
{
	double	wall_x;
	double	step;

	step = 1.0 * 64 / vc->ray.line_height;
	*texture_pos = (vc->ray.wall_start - \
		(Y_SCREEN / 2 + vc->ray.line_height / 2)) * step;
	if (*texture_pos < 0)
		*texture_pos = 0;
	if (vc->ray.side == 0)
		wall_x = vc->player.pos_y + vc->ray.real_size * vc->ray.direction_y;
	else
		wall_x = vc->player.pos_x + vc->ray.real_size * vc->ray.direction_x;
	wall_x -= floor(wall_x);
	*texture_x = (int)(wall_x * texture->img_size_x);
	if ((vc->ray.side == 0 && vc->ray.direction_x > 0)
		|| (vc->ray.side == 1 && vc->ray.direction_y < 0))
		*texture_x = texture->img_size_x - *texture_x - 1;
}

void	draw_wall_segment(t_vc *vc, t_data *texture,
	double texture_pos, int texture_x)
{
	int	texture_y;
	int	color;
	int	y;

	y = vc->ray.wall_start;
	while (y < vc->ray.wall_end)
	{
		texture_y = (int)texture_pos % texture->img_size_y;
		color = my_pixel_get(texture, texture_x, texture_y);
		if (vc->ray.side == 1)
			color = (color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(vc->canva, vc->ray.id, y, color);
		texture_pos += (1.0 * 64 / vc->ray.line_height);
		y++;
	}
	draw_floor_ceiling(vc, &vc->ray);
}

void	draw_walls(t_vc *vc, t_data *texture)
{
	double	texture_pos;
	int		texture_x;

	compute_wall_texture_coords(vc, texture, &texture_pos, &texture_x);
	draw_wall_segment(vc, texture, texture_pos, texture_x);
}
