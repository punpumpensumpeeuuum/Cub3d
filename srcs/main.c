/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:19 by jomendes          #+#    #+#             */
/*   Updated: 2024/12/16 18:35:23 by jomendes         ###   ########.fr       */
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
    printf("Texture loaded successfully from %s Size: %dx%d\n", file_path, texture->img_size_x, texture->img_size_y);
}

void	alloc_textures(t_vc *vc)
{
	vc->map_info.no_texture = malloc(sizeof(t_data));
	vc->map_info.so_texture = malloc(sizeof(t_data));
	vc->map_info.ea_texture = malloc(sizeof(t_data));
	vc->map_info.we_texture = malloc(sizeof(t_data));
	if (!vc->map_info.no_texture || !vc->map_info.so_texture || !vc->map_info.ea_texture || !vc->map_info.we_texture)
	{
	    printf("Error: failed to allocate memory for textures.\n");
	    exit(1);
	}
	load_texture(vc->map_info.no_texture, vc->mlx.mlx, vc->map_info.no);
	load_texture(vc->map_info.so_texture, vc->mlx.mlx, vc->map_info.so);
	load_texture(vc->map_info.ea_texture, vc->mlx.mlx, vc->map_info.ea);
	load_texture(vc->map_info.we_texture, vc->mlx.mlx, vc->map_info.we);
}

float	degree_to_radian(int degree)
{
	return ((float)degree * (PI / 180.0f));
}

void init_vc(t_vc *vc)
{
    // Initialize mlx
    vc->mlx.window = NULL;
    vc->mlx.x = 0;
    vc->mlx.y = 0;
    vc->mlx.mlx = NULL;

    // Initialize player
    vc->player.facing = 0;
    vc->player.w = 0;
    vc->player.a = 0;
    vc->player.s = 0;
    vc->player.d = 0;
    vc->player.pos_x = 0;
    vc->player.pos_y = 0;
    vc->player.plane_x = 0.0;
    vc->player.plane_y = 0.0;
    vc->player.direction_x = 0.0;
    vc->player.direction_y = 0.0;
    vc->player.camera_x = 0.0;
    vc->player.camera_y = 0.0;

    // Initialize minimap
    vc->minimap.x = 0;
    vc->minimap.y = 0;
    vc->minimap.onoff = 0;

    // Initialize map
    vc->map.file = NULL;
    vc->map.matrix = NULL;
    vc->map.matrix_ff = NULL;
    vc->map.index = 0;
    vc->map.file_heigth = 0;
    vc->map.floor = NULL;
    vc->map.ceiling = NULL;
    vc->map.x = 0;
    vc->map.y = 0;

    // Initialize map_info
    vc->map_info.no = NULL;
    vc->map_info.so = NULL;
    vc->map_info.ea = NULL;
    vc->map_info.we = NULL;
    vc->map_info.no_texture = NULL;
    vc->map_info.so_texture = NULL;
    vc->map_info.we_texture = NULL;
    vc->map_info.ea_texture = NULL;
    vc->map_info.ceiling_color.r = 0;
    vc->map_info.ceiling_color.g = 0;
    vc->map_info.ceiling_color.b = 0;
    vc->map_info.floor_color.r = 0;
    vc->map_info.floor_color.g = 0;
    vc->map_info.floor_color.b = 0;

    // Initialize ray
    vc->ray.id = 0;
    vc->ray.pos_x = 0;
    vc->ray.pos_y = 0;
    vc->ray.direction_x = 0.0;
    vc->ray.direction_y = 0.0;
    vc->ray.delta_dist_x = 0.0;
    vc->ray.delta_dist_y = 0.0;
    vc->ray.distance_x = 0.0;
    vc->ray.distance_y = 0.0;
    vc->ray.real_size = 0.0;
    vc->ray.side = 0;
    vc->ray.line_height = 0;
    vc->ray.wall_start = 0;
    vc->ray.wall_end = 0;
    vc->ray.step_x = 0;
    vc->ray.step_y = 0;
    vc->ray.x_texture = 0;
    vc->ray.y_texture = 0;

    // Initialize data (assuming it will hold texture data or some other image data)
    vc->data.img_ptr = NULL;
    vc->data.addr = NULL;
    vc->data.bits_per_pixel = 0;
    vc->data.line_length = 0;
    vc->data.endian = 0;
    vc->data.img_size_x = 0;
    vc->data.img_size_y = 0;
}

void init(char *file)
{
    t_vc *vc;

    vc = get_data();
    //init_vc(vc);
	//vc = malloc (sizeof (t_vc));
	vc->mlx.x = X_SCREEN;
	vc->mlx.y = Y_SCREEN;
    vc->map.file = get_file(file, &vc->map);
    vc->map.matrix = get_map(&vc->map);
    if (get_floor(&vc->map) == 0)
        printf("floor = %s\n", vc->map.floor);
    if (get_ceiling(&vc->map) == 0)
        printf("ceiling = %s\n", vc->map.ceiling);

    int i = -1;
    while (vc->map.file[++i])
    {
        printf("%s", vc->map.file[i]);
    }
    printf("\n\n");
    get_width(&vc->map);
    second_map(&vc->map);
    if (check_map(&vc->map) == 1)
        exit(1);

    i = -1;
    while (vc->map.matrix_ff[++i])
    {
        printf("%s", vc->map.matrix_ff[i]);
    }
    vc->mlx.mlx = mlx_init();
    vc->mlx.window = mlx_new_window(vc->mlx.mlx, vc->mlx.x, vc->mlx.y, "cub3d");
    placeplayer(vc);
    alloc_textures1(vc);
    alloc_textures(vc);
    mlx_do_key_autorepeatoff(vc->mlx.mlx);
    //open_imgs(vc);
	dda_style(vc);
    mlx_hook(vc->mlx.window, 17, 1L << 17, closegame, vc);
    mlx_hook(vc->mlx.window, 2, 1L << 0, keypress, vc);
    mlx_hook(vc->mlx.window, 3, 1L << 1, keyunpress, vc);
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
