/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:19 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/20 17:45:16 by dinda-si         ###   ########.fr       */
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
		vc->player.w = 1;
	else if (keycode == 'a')
		vc->player.a = 1;
	else if (keycode == 's')
		vc->player.s = 1;
	else if (keycode == 'd')
		vc->player.d = 1;
	return (0);
}

int	keyunpress(int keycode, t_vc *vc)
{
	if (keycode == 'w')
		vc->player.w = 0;
	else if (keycode == 'a')
		vc->player.a = 0;
	else if (keycode == 's')
		vc->player.s = 0;
	else if (keycode == 'd')
		vc->player.d = 0;
	return (0);
}

void	movemnt(t_vc *vc)
{
	printf("%d\n", vc->player.pos_x);
printf("%d\n", vc->player.pos_y);
	if (vc->player.w == 1 && vc->map.matrix[((vc->player.pos_y - 1) / 16) - 1][((vc->player.pos_x - 1) / \
		16)] != '1' && vc->map.matrix[((vc->player.pos_y - 1) / 16) - 1][((vc->player.pos_x - 14) / 16)] != '1')
		vc->player.pos_y--;
	if (vc->player.a == 1 && vc->map.matrix[((vc->player.pos_y + 1) / 16) - 1][((vc->player.pos_x - 1) / \
		16) - 1] != '1' && vc->map.matrix[((vc->player.pos_y + 14) /	16) - 1][((vc->player.pos_x - 1) / 16) - 1] != '1')
		vc->player.pos_x--;
	if (vc->player.d == 1 && vc->map.matrix[((vc->player.pos_y - 1) / 16)][((vc->player.pos_x) / \
		16)] != '1' && vc->map.matrix[((vc->player.pos_y - 14) / 16)][((vc->player.pos_x) / 16)] != '1')
		vc->player.pos_x++;
	if (vc->player.s == 1 && vc->map.matrix[((vc->player.pos_y) / 16)][((vc->player.pos_x - 1) / \
		16)] != '1' && vc->map.matrix[((vc->player.pos_y) / 16)][((vc->player.pos_x - 14) / 16)] != '1')
		vc->player.pos_y++;
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

void	alloc_textures1(t_vc *vc)
{
	int y;
	int len;

	y = 0;
	while (vc->map.file[y])
	{
		len = ft_strlen(vc->map.file[y]);
		if (vc->map.file[y][len - 1] == '\n')
			vc->map.file[y][len - 1] = '\0';
		if (ft_strncmp(vc->map.file[y], "NO", 2) == 0)
			vc->map_info.no = ft_strdup(vc->map.file[y] + 3);
		else if (ft_strncmp(vc->map.file[y], "SO", 2) == 0)
			vc->map_info.so = ft_strdup(vc->map.file[y] + 3);
		else if (ft_strncmp(vc->map.file[y], "EA", 2) == 0)
			vc->map_info.ea = ft_strdup(vc->map.file[y] + 3);
		else if (ft_strncmp(vc->map.file[y], "WE", 2) == 0)
			vc->map_info.we = ft_strdup(vc->map.file[y] + 3);
		y++;
	}
}

void load_texture(t_data *texture, void *mlx, char *file_path)
{
	if (file_path == NULL || *file_path == '\0')
	{
   		printf("Error: Invalid texture file path.\n");
    	exit(1);
	}
	if (access(file_path, F_OK) != 0)
	{
   		printf("Texture file not found: >%s<\n", file_path);
    	exit(1);
	}
    texture->img_ptr = mlx_xpm_file_to_image(mlx, file_path, &texture->img_size_x, &texture->img_size_y);
    if (!texture->img_ptr)
    {
        printf("Error: failed to load texture: %s\n", file_path);
        exit(1);
    }
    texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel,
                                      &texture->line_length, &texture->endian);
    if (texture->addr == NULL)
    {
        printf("Error: failed to get texture address: %s\n", file_path);
        exit(1);
	}
	dprintf(2, "adrr = %p\n", texture->addr);
	dprintf(2, "img = %p\n", texture->img_ptr);
    printf("Texture loaded successfully from %s Size: %dx%d\n", file_path, texture->img_size_x, texture->img_size_y);
}

void	alloc_textures(t_vc *vc)
{
	vc->map_info.no_texture = malloc(sizeof(t_data));
	vc->map_info.so_texture = malloc(sizeof(t_data));
	vc->map_info.ea_texture = malloc(sizeof(t_data));
	vc->map_info.we_texture = malloc(sizeof(t_data));
	vc->canva = malloc(sizeof(t_data));
	if (!vc->map_info.no_texture || !vc->map_info.so_texture || !vc->map_info.ea_texture || !vc->map_info.we_texture)
	{
	    printf("Error: failed to allocate memory for textures.\n");
	    exit(1);
	}
	vc->canva->img_ptr = mlx_new_image(vc->mlx.mlx, X_SCREEN, Y_SCREEN);
	vc->canva->addr = mlx_get_data_addr(vc->canva->img_ptr, &vc->canva->bits_per_pixel, &vc->canva->line_length, &vc->canva->endian);
    vc->canva->img_size_x = X_SCREEN;
    vc->canva->img_size_y = Y_SCREEN;
	load_texture(vc->map_info.no_texture, vc->mlx.mlx, vc->map_info.no);
	load_texture(vc->map_info.so_texture, vc->mlx.mlx, vc->map_info.so);
	load_texture(vc->map_info.ea_texture, vc->mlx.mlx, vc->map_info.ea);
	load_texture(vc->map_info.we_texture, vc->mlx.mlx, vc->map_info.we);
}

float	degree_to_radian(int degree)
{
	return ((float)degree * (PI / 180.0f));
}

int	get_floor_color(t_map_info *info)
{
	char **floor;
	int	color;
	
	floor = ft_split((info->floor + 2), ',');
	info->floor_color.r = ft_atoi(floor[0]);
	info->floor_color.g = ft_atoi(floor[1]);
	info->floor_color.b =  ft_atoi(floor[2]);
	if (info->floor_color.r < 0 || info->floor_color.r > 255 ||
    info->floor_color.g < 0 || info->floor_color.g > 255 ||
    info->floor_color.b < 0 || info->floor_color.b > 255)
		return (1);
	color = (info->floor_color.r << 16 | info->floor_color.g << 8 | info->floor_color.b);
	return (color);
}

int	get_ceiling_color(t_map_info *info)
{
	char **ceiling;
	int	color;
	
	ceiling = ft_split((info->ceiling + 2), ',');
	info->ceiling_color.r = ft_atoi(ceiling[0]);
	info->ceiling_color.g = ft_atoi(ceiling[1]);
	info->ceiling_color.b =  ft_atoi(ceiling[2]);
	if (info->ceiling_color.r < 0 || info->ceiling_color.r > 255 ||
    info->ceiling_color.g < 0 || info->ceiling_color.g > 255 ||
    info->ceiling_color.b < 0 || info->ceiling_color.b > 255)
		return (1);
	color = (info->ceiling_color.r << 16 | info->ceiling_color.g << 8 | info->ceiling_color.b);
	return (color);
}

void init(char *file)
{
    t_vc *vc;

	vc = get_data();
	vc->mlx.x = X_SCREEN;
	vc->mlx.y = Y_SCREEN;
	vc->mlx.pixelx = vc->mlx.x / 16;
	vc->mlx.pixely = vc->mlx.y / 16;
    vc->map.file = get_file(file, &vc->map);
    vc->map.matrix = get_map(&vc->map);
    if (get_floor(&vc->map, &vc->map_info) == 0)
        printf("floor = %s\n", vc->map_info.floor);
    if (get_ceiling(&vc->map, &vc->map_info) == 0)
        printf("ceiling = %s\n", vc->map_info.ceiling);
    int i = -1;
    while (vc->map.file[++i])
    {
        printf("%s", vc->map.file[i]);
    }
    printf("\n\n");
    get_width(&vc->map);
    second_map(&vc->map);
    if (check_map(&vc->map) == 1)
	{
		dprintf(2, "HALLOHA\n");
        exit(1);
	}
	i = -1;
	while (vc->map.matrix_ff[++i])
	{
		printf("%s", vc->map.matrix_ff[i]);
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
		ft_putstr_fd("Invalid RGB on ceiling\n", 2);
		return ;
	}
	else if (get_floor_color(&vc->map_info) == 1)
	{
		ft_putstr_fd("Invalid RGB on floor\n", 2);
		return ;
	}
	dda_style(vc);
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
	mlx_do_key_autorepeatoff(vc->mlx.mlx);
    mlx_loop(vc->mlx.mlx);
}


int main(int ac, char **av)
{
	if (!check_args(ac, av))
		return (0);
	init(av[1]);
	return (0);
}
