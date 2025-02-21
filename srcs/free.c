/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:08:09 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/21 16:10:05 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(char *str)
{
	write (2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit(1);
}

int	closegame(t_vc *vc)
{
	close_window(vc);
	exit(0);
}

void	my_img_clear(t_data data)
{
	int	j;
	int	i;

	j = 0;
	while (j < Y_SCREEN)
	{
		i = 0;
		while (i < X_SCREEN)
		{
			my_mlx_pixel_put(&data, i, j, 0x000000);
			i++;
		}
		j++;
	}
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	free_mlx(t_vc *vc)
{
	if (vc->map_info.no)
		free(vc->map_info.no);
	if (vc->map_info.so)
		free(vc->map_info.so);
	if (vc->map_info.ea)
		free(vc->map_info.ea);
	if (vc->map_info.we)
		free(vc->map_info.we);
	if (vc->canva)
		free(vc->canva);
	if (vc->mlx.window)
		mlx_destroy_window(vc->mlx.mlx, vc->mlx.window);
	if (vc->mlx.mlx)
	{
		mlx_destroy_display(vc->mlx.mlx);
		free(vc->mlx.mlx);
	}
}
