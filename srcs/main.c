/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:19 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/21 15:06:24 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	coma_counter(char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return (counter);
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
	info->floor_color.b =  ft_atoi(floor[2]);
	free_split(floor);
	if (info->floor_color.r < 0 || info->floor_color.r > 255 ||
	info->floor_color.g < 0 || info->floor_color.g > 255 ||
	info->floor_color.b < 0 || info->floor_color.b > 255)
		return (1);
	color = (info->floor_color.r << 16 | info->floor_color.g << 8 | info->floor_color.b);
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
	if (!ceiling[0] || !ceiling[1] || !ceiling[2] || ceiling[3] || rgb_def_check(ceiling[0]) == 1
	|| rgb_def_check(ceiling[1]) == 1 || rgb_def_check(ceiling[2]) == 1)
		return (1);
	info->ceiling_color.r = ft_atoi(ceiling[0]);
	info->ceiling_color.g = ft_atoi(ceiling[1]);
	info->ceiling_color.b =  ft_atoi(ceiling[2]);
	free_split(ceiling);
	if (info->ceiling_color.r < 0 || info->ceiling_color.r > 255 ||
	info->ceiling_color.g < 0 || info->ceiling_color.g > 255 ||
	info->ceiling_color.b < 0 || info->ceiling_color.b > 255)
		return (1);
	color = (info->ceiling_color.r << 16 | info->ceiling_color.g << 8 | info->ceiling_color.b);
	return (color);
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

void	free_game(t_vc *vc)
{
	if (vc->map.matrix) {
		free(vc->map.matrix);
		vc->map.matrix = NULL;
	}
	if (vc->map.matrix_ff) {
		free_split(vc->map.matrix_ff);
		vc->map.matrix_ff = NULL;
	}
	if (vc->map.file) {
		free_split(vc->map.file);
		vc->map.file = NULL;
	}
	if (vc->minimap.floor)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.floor);
	if (vc->minimap.player)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.player);
	if (vc->minimap.wall)
		mlx_destroy_image(vc->mlx.mlx, vc->minimap.wall);
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
	free_mlx(vc);
}

int	close_window(t_vc *vc)
{
	printf("close_window called\n");
	free_game(vc);
	exit(EXIT_SUCCESS);
	return (0);
}

void init(char *file)
{
	t_vc *vc;

	vc = get_data();
	vc->mlx.x = X_SCREEN;
	vc->mlx.y = Y_SCREEN;
	vc->mlx.pixelx = vc->mlx.x / 16;
	vc->mlx.pixely = vc->mlx.y / 16;
	vc->map.y = 0;
	vc->map.x = 0;
	vc->map.file = get_file(file, &vc->map);
	vc->map.matrix = get_map(&vc->map);
	if (get_floor(&vc->map, &vc->map_info) == 1 || !vc->map.matrix || !vc->map.file)
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
	if (get_ceiling(&vc->map, &vc->map_info) == 1)
	{
		// free_game(vc);
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
	int i = -1;
	while (vc->map.matrix[++i])
	{
		printf("%s", vc->map.matrix[i]);
	}
	printf("\n\n --------------------------------- \n\n");
	get_width(&vc->map);
	second_map(&vc->map);
	printf("%s", vc->map.matrix_ff[0]);
	printf("%s", vc->map.matrix_ff[1]);
	printf("%s", vc->map.matrix_ff[2]);
	printf("%s", vc->map.matrix_ff[3]);
	printf("%s", vc->map.matrix_ff[4]);
	if (check_map(&vc->map) == 1)
	{
		free_game(vc);
		dprintf(2, "HALLOHA\n");
		exit(1);
	}
	vc->mlx.mlx = mlx_init();
	vc->minimap.player = mlx_xpm_file_to_image(vc->mlx.mlx, "srcs/xpm/playerminimap.xpm", &vc->mlx.pixelx, &vc->mlx.pixely);
	vc->minimap.wall = mlx_xpm_file_to_image(vc->mlx.mlx, "srcs/xpm/wallminimap.xpm", &vc->mlx.pixelx, &vc->mlx.pixely);
	vc->minimap.floor = mlx_xpm_file_to_image(vc->mlx.mlx, "srcs/xpm/floorminimap.xpm", &vc->mlx.pixelx, &vc->mlx.pixely);
	vc->mlx.window = mlx_new_window(vc->mlx.mlx, vc->mlx.x, vc->mlx.y, "cub3d");
	placeplayer(vc);
	alloc_textures1(vc);
	alloc_textures(vc);
	if (get_ceiling_color(&vc->map_info) == 1)
	{
		free_game(vc);
		ft_putstr_fd("Invalid RGB on ceiling\n", 2);
		exit(1);
	}
	else if (get_floor_color(&vc->map_info) == 1)
	{
		free_game(vc);
		ft_putstr_fd("Invalid RGB on floor\n", 2);
		exit(1);
	}
	printf("\n");
	printf("cealing r = %d\n", vc->map_info.ceiling_color.r);
	printf("cealing g = %d\n", vc->map_info.ceiling_color.g);
	printf("cealing b = %d\n", vc->map_info.ceiling_color.b);
	printf("floor r = %d\n", vc->map_info.floor_color.r);
	printf("floor g = %d\n", vc->map_info.floor_color.g);
	printf("floor b = %d\n", vc->map_info.floor_color.b);
	mlx_hook(vc->mlx.window, 17, 1L << 17, closegame, vc);
	mlx_hook(vc->mlx.window, 2, 1L << 0, keypress, vc);
	mlx_hook(vc->mlx.window, 3, 1L << 1, keyunpress, vc);
	mlx_loop_hook(vc->mlx.mlx, andar, vc);
	printf("Configuring close_window with vc: %p\n", vc);
	mlx_hook(vc->mlx.window, 17, 0L, close_window, vc);
	mlx_do_key_autorepeatoff(vc->mlx.mlx);
	mlx_loop(vc->mlx.mlx);
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

int main(int ac, char **av)
{
	t_vc *vc;

	vc = get_data();
	if (!check_args(ac, av))
		return (0);
	init(av[1]);
	destroy_map(vc);
	return (0);
}
