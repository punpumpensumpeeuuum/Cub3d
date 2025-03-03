/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:19 by jomendes          #+#    #+#             */
/*   Updated: 2025/03/03 16:52:08 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_width(t_map *map)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	width = 0;
	while (map->matrix[i])
	{
		j = 0;
		while (map->matrix[i][j] != '\0' && map->matrix[i][j] != '\n')
			j++;
		if (width < j)
			width = j;
		i++;
	}
	map->x = width;
}

t_vc	*get_data(void)
{
	static t_vc	data;

	return (&data);
}

int	andar(t_vc *vc)
{
	movemnt(vc);
	my_img_clear(*vc->canva);
	dda_style(vc);
	if (vc->minimap.onoff == 1)
		drawminimap(vc);
	return (0);
}

void	init(char *file)
{
	t_vc	*vc;

	vc = get_data();
	vc->mlx.x = X_SCREEN;
	vc->mlx.y = Y_SCREEN;
	vc->mlx.pixelx = vc->mlx.x / 16;
	vc->mlx.pixely = vc->mlx.y / 16;
	vc->map.y = 0;
	vc->map.x = 0;
	vc->map.file = get_file(file, &vc->map);
	vc->map.matrix = get_map(&vc->map);
	checkcolors(vc);
	get_width(&vc->map);
	second_map(&vc->map);
	check_map(&vc->map, vc);
	vc->mlx.mlx = mlx_init();
	anotherinit(vc);
	mlx_hook(vc->mlx.window, 17, 1L << 17, closegame, vc);
	mlx_hook(vc->mlx.window, 2, 1L << 0, keypress, vc);
	mlx_hook(vc->mlx.window, 3, 1L << 1, keyunpress, vc);
	mlx_loop_hook(vc->mlx.mlx, andar, vc);
	mlx_hook(vc->mlx.window, 17, 0L, close_window, vc);
	mlx_do_key_autorepeatoff(vc->mlx.mlx);
	mlx_loop(vc->mlx.mlx);
}

int	main(int ac, char **av)
{
	t_vc	*vc;

	vc = get_data();
	if (!check_args(ac, av))
		return (0);
	init(av[1]);
	destroy_map(vc);
	return (0);
}
