/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:19 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/13 14:02:18 by jomendes         ###   ########.fr       */
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
	if (vc->player.a == 1 &&
		vc->map.matrix[((vc->player.pos_x - 1) / (X_SCREEN / 80))] \
		[((vc->player.pos_y - 1) / (Y_SCREEN / 45)) - 1] != '1')
		vc->player.pos_y -= Y_SCREEN / 45;
	if (vc->player.w == 1 &&
		vc->map.matrix[((vc->player.pos_x + 1) / (X_SCREEN / 80)) - 2] \
		[((vc->player.pos_y + 1) / (Y_SCREEN / 45)) - 1] != '1')
		vc->player.pos_x -= X_SCREEN / 80;
	if (vc->player.d == 1 && 
		vc->map.matrix[((vc->player.pos_x - 1) / (X_SCREEN / 80))] \
		[((vc->player.pos_y + 1) / (Y_SCREEN / 45))] != '1')
		vc->player.pos_y += Y_SCREEN / 45;
	if (vc->player.s == 1 &&
		vc->map.matrix[((vc->player.pos_x + 1) / (X_SCREEN / 80))] \
		[((vc->player.pos_y - 1) / (Y_SCREEN / 45))] != '1')
		vc->player.pos_x += X_SCREEN / 80;
}

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
	movemnt(vc);
    if (vc->minimap.onoff == 1){
        drawminimap(vc);}
    // usleep(500000);
	// mlx_clear_window(vc->mlx.mlx, vc->mlx.window);
	draw_rectangle(vc, Y_SCREEN, vc->mlx.x, 0x0FFF00);
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
	printf("NO Texture Path: %s\n", file_path);
	if (access(file_path, F_OK) != 0)
	{
   		printf("Texture file not found: >%s<\n", file_path);
    	exit(1);
	}
    // Load the image into mlx and retrieve its properties
    texture->img_ptr = mlx_xpm_file_to_image(mlx, file_path, &texture->img_size_x, &texture->img_size_y);
    if (!texture->img_ptr)
    {
        printf("Error: failed to load texture: %s\n", file_path);
        exit(1);  // Exit if loading fails
    }

    // Get the address, bits per pixel, line length, and endian info of the image
    texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel,
                                      &texture->line_length, &texture->endian);
    if (texture->addr == NULL)
    {
        printf("Error: failed to get texture address: %s\n", file_path);
        exit(1);  // Exit if getting the address fails
    }

    printf("Texture loaded successfully from %s. Size: %dx%d\n", file_path, texture->img_size_x, texture->img_size_y);
}

void	alloc_textures(t_vc *vc)
{
    // Allocate memory for each texture data structure
    vc->map_info.no_texture = malloc(sizeof(t_data));
    vc->map_info.so_texture = malloc(sizeof(t_data));
    vc->map_info.ea_texture = malloc(sizeof(t_data));
    vc->map_info.we_texture = malloc(sizeof(t_data));
    if (!vc->map_info.no_texture || !vc->map_info.so_texture || !vc->map_info.ea_texture || !vc->map_info.we_texture)
    {
        printf("Error: failed to allocate memory for textures.\n");
        exit(1);  // Exit if memory allocation fails
    }
    // Load textures into their respective structures
    load_texture(vc->map_info.no_texture, vc->mlx.mlx, vc->map_info.no);
    load_texture(vc->map_info.so_texture, vc->mlx.mlx, vc->map_info.so);
    load_texture(vc->map_info.ea_texture, vc->mlx.mlx, vc->map_info.ea);
    load_texture(vc->map_info.we_texture, vc->mlx.mlx, vc->map_info.we);
}

float	degree_to_radian(int degree)
{
	return ((float)degree * (PI / 180.0f));
}



void	init(char *file)
{
	t_vc		*vc;
	t_mlx		mlx;
	t_player	player;
	t_map		map;
	t_minimap	minimap;

	vc = get_data();
	mlx.mlx = NULL;
	mlx.window = NULL;
	map.matrix = NULL;
	map.matrix_ff = NULL;
	mlx.x = 768; //3840
	mlx.y = 398; //1990
	player.pos_x = 0;
	player.pos_y = 0;
	player.w = 0;
	player.a = 0;
	player.s = 0;
	player.d = 0;
	minimap.onoff = 0;
	map.file = get_file(file, &map);
    map.matrix = get_map(&map);
	if (get_floor(&map) == 0)
		printf("floor = %s\n", map.floor);
	if (get_ceiling(&map) == 0)
		printf("celling = %s\n", map.ceiling);
    int i = -1;
    while (map.file[++i])
	{
		printf("%s", map.file[i]);
	}
	printf("\n\n");
    get_width(&map);
    second_map(&map);
	if (check_map(&map) == 1)
		exit(1);
	i = -1;
    while (map.matrix_ff[++i])
	{
		printf("%s", map.matrix_ff[i]);
	}
	vc->map = map;
	vc->mlx = mlx;
	vc->player = player;
	vc->minimap = minimap;
	
	vc->mlx.mlx = mlx_init();
	vc->mlx.window = mlx_new_window(vc->mlx.mlx, vc->mlx.x, vc->mlx.y, "cub3d");
	placeplayer(vc);
	alloc_textures1(vc);
	alloc_textures(vc);
	//open_imgs(vc);
	mlx_do_key_autorepeatoff(vc->mlx.mlx);
	dda_style(vc);
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
