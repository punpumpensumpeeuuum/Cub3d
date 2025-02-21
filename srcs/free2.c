/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:11:07 by dinda-si          #+#    #+#             */
/*   Updated: 2025/02/21 16:15:45 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_game_game(t_vc *vc)
{
	if (vc->map_info.ea_texture && vc->map_info.ea_texture->img_ptr)
	{
		mlx_destroy_image(vc->mlx.mlx, vc->map_info.ea_texture->img_ptr);
		free(vc->map_info.ea_texture);
	}
	if (vc->map_info.no_texture && vc->map_info.no_texture->img_ptr)
	{
		mlx_destroy_image(vc->mlx.mlx, vc->map_info.no_texture->img_ptr);
		free(vc->map_info.no_texture);
	}
	if (vc->map_info.so_texture && vc->map_info.so_texture->img_ptr)
	{
		mlx_destroy_image(vc->mlx.mlx, vc->map_info.so_texture->img_ptr);
		free(vc->map_info.so_texture);
	}
	if (vc->map_info.we_texture && vc->map_info.we_texture->img_ptr)
	{
		mlx_destroy_image(vc->mlx.mlx, vc->map_info.we_texture->img_ptr);
		free(vc->map_info.we_texture);
	}
	if (vc->canva && vc->canva->img_ptr)
		mlx_destroy_image(vc->mlx.mlx, vc->canva->img_ptr);
}

void	free_game(t_vc *vc)
{
	if (vc->map.matrix)
	{
		free(vc->map.matrix);
		vc->map.matrix = NULL;
	}
	if (vc->map.matrix_ff)
	{
		free_split(vc->map.matrix_ff);
		vc->map.matrix_ff = NULL;
	}
	if (vc->map.file)
	{
		free_split(vc->map.file);
		vc->map.file = NULL;
	}
	if (vc->minimap.floor)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.floor);
	if (vc->minimap.player)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.player);
	if (vc->minimap.wall)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.wall);
	free_game_game(vc);
	free_mlx(vc);
}

int	close_window(t_vc *vc)
{
	printf("close_window called\n");
	free_game(vc);
	exit(EXIT_SUCCESS);
	return (0);
}

void	destroy_map(t_vc *vc)
{
	if (vc->minimap.floor)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.floor);
	if (vc->minimap.player)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.player);
	if (vc->minimap.wall)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.wall);
}
