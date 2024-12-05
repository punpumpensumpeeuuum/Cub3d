/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:19 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/05 05:29:32 by elemesmo         ###   ########.fr       */
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
            vc->minimap.onoff = 0;
        else
            vc->minimap.onoff = 1;
    }
    return (0);
	// else if (keycode == 'w')
	// 	vc->player.w = 1;
	// else if (keycode == 'a')
	// 	vc->player.a = 1;
	// else if (keycode == 's')
	// 	vc->player.s = 1;
	// else if (keycode == 'd')
	// 	vc->player.d = 1;
}

// int	keyunpress(int keycode, t_vc *vc)
// {
// 	if (keycode == 'm')
// 		vc->minimap.onoff = 0;
// 	// if (keycode == 'w')
// 	// 	img->player.w = 0;
// 	// else if (keycode == 'a')
// 	// 	img->player.a = 0;
// 	// else if (keycode == 's')
// 	// 	img->player.s = 0;
// 	// else if (keycode == 'd')
// 	// 	img->player.d = 0;
// 	return (0);
// }

// void	movimento(t_vc *vc)
// {
// 	if (img->player.w == 1)
// 		colup(img);
// 	if (img->player.a == 1)
// 		colleft(img);
// 	if (img->player.s == 1)
// 		coldown(img);
// 	if (img->player.d == 1)
// 		colright(img);
// }

// void	animation(t_vc *vc)
// {
// 	if (img->player.red == 1)
// 		red(img);
// 	else if (img->player.green == 1)
// 		green(img);
// 	else if (img->player.blue == 1)
// 		blue(img);
// 	else
// 		white(img);
// }

int andar(t_vc *vc)
{
	// printf("777> %d\n", vc->minimap.onoff);
    mlx_clear_window(vc->mlx.mlx, vc->mlx.window);
    if (vc->minimap.onoff)
        drawminimap(vc);
    usleep(50000 / 30);
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
	mlx.x = 1200; //3840
	mlx.y = 600; //1990
	play.x = 0;
	play.y = 0;
	minimap.onoff = 0;
	map.matrix = get_map(file, &map);
	map.matrix_ff = get_map(file, &map);
	vc->map = map;
	vc->mlx = mlx;
	vc->play = play;
	vc->minimap = minimap;
	vc->mlx.mlx = mlx_init();
	vc->mlx.window = mlx_new_window(vc->mlx.mlx, vc->mlx.x, vc->mlx.y, "cub3d");
	mlx_do_key_autorepeatoff(vc->mlx.mlx);
	draw_rectangle(vc, 10, 10, 0xFF0000);
	mlx_hook(vc->mlx.window, 17, 1L << 17, closegame, &vc);
	mlx_hook(vc->mlx.window, 2, 1L << 0, keypress, &vc);
	// mlx_hook(vc->mlx.window, 3, 1L << 1, keyunpress, &vc);
	mlx_hook(vc->mlx.window, 17, 1L << 17, closegame, &vc);
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
