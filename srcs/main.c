/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:19 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/12 16:42:32 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vc	*get_data()
{
	static t_vc data;

	return (&data);
}

int	closegame(t_vc *vc)
{
	vc->map.matrix_ff = NULL;
	exit(0);
}

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
		vc->play.w = 1;
	else if (keycode == 'a')
		vc->play.a = 1;
	else if (keycode == 's')
		vc->play.s = 1;
	else if (keycode == 'd')
		vc->play.d = 1;
	return (0);
}

int	keyunpress(int keycode, t_vc *vc)
{
	if (keycode == 'w')
		vc->play.w = 0;
	else if (keycode == 'a')
		vc->play.a = 0;
	else if (keycode == 's')
		vc->play.s = 0;
	else if (keycode == 'd')
		vc->play.d = 0;
	return (0);
}

void	movemnt(t_vc *vc)
{
	if (vc->play.w == 1)
		vc->play.y--;
	if (vc->play.a == 1)
		vc->play.x--;
	if (vc->play.d == 1)
		vc->play.x++;
	if (vc->play.s == 1)
		vc->play.y++;
}

int andar(t_vc *vc)
{
	movemnt(vc);
	// mlx_clear_window(vc->mlx.mlx, vc->mlx.window);
	if (vc->minimap.onoff == 1)
		drawminimap(vc);
    // usleep(500000);
	// mlx_clear_window(vc->mlx.mlx, vc->mlx.window);
	// draw_minimap_background(vc, vc->map.x + 100, vc->map.y + 100, 0xFF00FF);
	return (0);
}

void	init(char *file)
{
	t_vc		*vc;
	t_mlx		mlx;
	t_play		play;
	t_map		map;
	t_minimap	minimap;

	vc = get_data();
	mlx.mlx = NULL;
	mlx.window = NULL;
	map.matrix = NULL;
	map.matrix_ff = NULL;
	mlx.x = 3840; //768
	mlx.y = 1990; //398
	mlx.pixelx = mlx.x / 80;
	mlx.pixely = mlx.y / 45;
	play.x = 0;
	play.y = 0;
	play.w = 0;
	play.a = 0;
	play.s = 0;
	play.d = 0;
	minimap.onoff = 0;
	map.file = get_file(file, &map);
    map.matrix = get_map(&map);
    int i = -1;
    while (map.file[++i])
        printf("%s", map.file[i]);
    get_width(&map);
    second_map(&map);
	vc->map = map;
	vc->mlx = mlx;
	vc->minimap = minimap;
	vc->mlx.mlx = mlx_init();
	play.sprite = mlx_xpm_file_to_image(vc->mlx.mlx, "srcs/red.xpm", &vc->mlx.pixelx, &vc->mlx.pixely);
	vc->mlx.window = mlx_new_window(vc->mlx.mlx, vc->mlx.x, vc->mlx.y, "cub3d");
	vc->play = play;
	placeplayer(vc);
	mlx_do_key_autorepeatoff(vc->mlx.mlx);
	mlx_hook(vc->mlx.window, 17, 1L << 17, closegame, vc);
	mlx_hook(vc->mlx.window, 2, 1L << 0, keypress, vc);
	mlx_hook(vc->mlx.window, 3, 1L << 1, keyunpress, vc);
	mlx_hook(vc->mlx.window, 17, 1L << 17, closegame, vc);
	mlx_loop_hook(vc->mlx.mlx, andar, vc);
	mlx_loop(vc->mlx.mlx);
}

int main(int ac, char **av)
{
	if (!check_args(ac, av))
		return (0);
	init(av[1]);
	return (0);
}
