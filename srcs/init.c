/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:08:04 by dinda-si          #+#    #+#             */
/*   Updated: 2025/03/03 17:34:35 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	anotherinit(t_vc *vc)
{
	vc->minimap.player = mlx_xpm_file_to_image(vc->mlx.mlx, \
		"srcs/xpm/playerminimap.xpm", &vc->mlx.pixelx, &vc->mlx.pixely);
	vc->minimap.wall = mlx_xpm_file_to_image(vc->mlx.mlx, \
		"srcs/xpm/wallminimap.xpm", &vc->mlx.pixelx, &vc->mlx.pixely);
	vc->minimap.floor = mlx_xpm_file_to_image(vc->mlx.mlx, \
		"srcs/xpm/floorminimap.xpm", &vc->mlx.pixelx, &vc->mlx.pixely);
	vc->mlx.window = mlx_new_window(vc->mlx.mlx, vc->mlx.x, vc->mlx.y, "cub3d");
	placeplayer(vc);
	alloc_textures1(vc);
	valid_textures(vc, vc->map_info.no);
	valid_textures(vc, vc->map_info.so);
	valid_textures(vc, vc->map_info.ea);
	valid_textures(vc, vc->map_info.we);
	alloc_textures(vc);
	if (get_ceiling_color(&vc->map_info) == 1 || \
		get_floor_color(&vc->map_info) == 1)
	{
		free_game(vc);
		ft_putstr_fd("Invalid RGB on ceiling or floor\n", 2);
		exit(1);
	}
}

void	checkcolors(t_vc *vc)
{
	if (get_floor(&vc->map, &vc->map_info) == 1 || !vc->map.matrix || \
		!vc->map.file || get_ceiling(&vc->map, &vc->map_info) == 1)
	{
		free_game(vc);
		if (vc->map.matrix)
		{
			free(vc->map.matrix);
			vc->map.matrix = NULL;
		}
		if (vc->map.file)
		{
			free_split(vc->map.file);
			vc->map.file = NULL;
		}
		exit(1);
	}
}

int	get_floor_color(t_map_info *info)
{
	char	**floor;
	int		color;

	if (coma_counter(info->floor) > 2)
	{
		ft_putstr_fd("Nasty evaluator\n", 2);
		return (1);
	}
	floor = ft_split((info->floor + 2), ',');
	if (!floor[0] || !floor[1] || !floor[2] || \
			floor[3] || rgb_def_check(floor[0]) == 1
		|| rgb_def_check(floor[1]) == 1 || rgb_def_check(floor[2]) == 1)
		return (1);
	info->floor_color.r = ft_atoi(floor[0]);
	info->floor_color.g = ft_atoi(floor[1]);
	info->floor_color.b = ft_atoi(floor[2]);
	free_split(floor);
	if (info->floor_color.r < 0 || info->floor_color.r > 255 || \
	info->floor_color.g < 0 || info->floor_color.g > 255 || \
	info->floor_color.b < 0 || info->floor_color.b > 255)
		return (1);
	color = (info->floor_color.r << 16 | info->floor_color.g << 8 | \
			info->floor_color.b);
	return (color);
}

int	get_ceiling_color(t_map_info *info)
{
	char	**ceiling;
	int		color;

	if (coma_counter(info->ceiling) > 2)
	{
		ft_putstr_fd("Nasty evaluator\n", 2);
		return (1);
	}
	ceiling = ft_split((info->ceiling + 2), ',');
	if (!ceiling[0] || !ceiling[1] || !ceiling[2] || ceiling[3] || \
			rgb_def_check(ceiling[0]) == 1
		|| rgb_def_check(ceiling[1]) == 1 || rgb_def_check(ceiling[2]) == 1)
		return (1);
	info->ceiling_color.r = ft_atoi(ceiling[0]);
	info->ceiling_color.g = ft_atoi(ceiling[1]);
	info->ceiling_color.b = ft_atoi(ceiling[2]);
	free_split(ceiling);
	if (info->ceiling_color.r < 0 || info->ceiling_color.r > 255 || \
	info->ceiling_color.g < 0 || info->ceiling_color.g > 255 || \
		info->ceiling_color.b < 0 || info->ceiling_color.b > 255)
		return (1);
	color = (info->ceiling_color.r << 16 | info->ceiling_color.g << 8 | \
		info->ceiling_color.b);
	return (color);
}
