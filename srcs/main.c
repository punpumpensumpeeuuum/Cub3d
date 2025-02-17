/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:19 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/10 13:26:07 by jomendes         ###   ########.fr       */
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
	close_window(vc);
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
	else if (keycode == L_ARROW)
		vc->player.o = 1;
	else if (keycode == R_ARROW)
		vc->player.o = 2;
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
	else if (keycode == L_ARROW)
		vc->player.o = 0;
	else if (keycode == R_ARROW)
		vc->player.o = 0;
	return (0);
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

long	get_time_in_microseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int andar(t_vc *vc)
{
	static long last_time = 0;
	long current_time = get_time_in_microseconds();

	if (current_time - last_time > 20000)
	{
		if (vc->current_bee_image == 0)
			vc->current_bee_image = 1;
		else
			vc->current_bee_image = 0;
	}
	last_time = current_time;
	movemnt(vc);
	move_bees(vc);
	my_img_clear(*vc->canva);
	dda_style(vc);
	draw_bees(vc);
	// mlx_clear_window(vc->mlx.mlx, vc->mlx.window);
	if (vc->minimap.onoff == 1)
		drawminimap(vc);
    // usleep(500000);
	// mlx_clear_window(vc->mlx.mlx, vc->mlx.window);
	// draw_minimap_background(vc, vc->map.x + 100, vc->map.y + 100, 0xFF00FF);
	return (0);
}

char	*ft_trim_and_strdup(const char *str, int start)
{
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	return (ft_strdup(str + start));
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
			vc->map_info.no = ft_trim_and_strdup(vc->map.file[y], 2);
		else if (ft_strncmp(vc->map.file[y], "SO", 2) == 0)
			vc->map_info.so = ft_trim_and_strdup(vc->map.file[y], 2);
		else if (ft_strncmp(vc->map.file[y], "EA", 2) == 0)
			vc->map_info.ea = ft_trim_and_strdup(vc->map.file[y], 2);
		else if (ft_strncmp(vc->map.file[y], "WE", 2) == 0)
			vc->map_info.we = ft_trim_and_strdup(vc->map.file[y], 2);
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
   		printf("Textureeee file not found: >%s<\n", file_path);
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

int	rgb_def_check(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		while (ft_isdigit(str[i]))
			i++;
		while (str[i] == ' ')
			i++;
		if (ft_isprint(str[i]))
		{
			ft_putstr_fd("Tryharder to break this\n", 2);
			return (1);
		}
			
	}
	return (0);
}

int	coma_counter(char *str)
{
	int counter;
	int i;

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
	char **floor;
	int	color;

	if (coma_counter(info->floor) > 2)
	{
		ft_putstr_fd("Nasty evaluator\n", 2);
		return (1);
	}
	floor = ft_split((info->floor + 2), ',');
	if (!floor[0] || !floor[1] || !floor[2] || floor[3] || rgb_def_check(floor[0]) == 1
	|| rgb_def_check(floor[1]) == 1 || rgb_def_check(floor[2]) == 1)
		return (1);
	info->floor_color.r = ft_atoi(floor[0]);
	info->floor_color.g = ft_atoi(floor[1]);
	info->floor_color.b =  ft_atoi(floor[2]);
	if (info->floor_color.r < 0 || info->floor_color.r > 255 ||
    info->floor_color.g < 0 || info->floor_color.g > 255 ||
    info->floor_color.b < 0 || info->floor_color.b > 255)
		return (1);
	color = (info->floor_color.r << 16 | info->floor_color.g << 8 | info->floor_color.b);
	free_split(floor);
	return (color);
}

int	get_ceiling_color(t_map_info *info)
{
	char **ceiling;
	int	color;
	
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
	if (info->ceiling_color.r < 0 || info->ceiling_color.r > 255 ||
    info->ceiling_color.g < 0 || info->ceiling_color.g > 255 ||
    info->ceiling_color.b < 0 || info->ceiling_color.b > 255)
		return (1);
	color = (info->ceiling_color.r << 16 | info->ceiling_color.g << 8 | info->ceiling_color.b);
	free_split(ceiling);
	return (color);
}

void	free_split(char **str)
{
	int i;

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
	str = NULL;
}

void free_mlx(t_vc *vc)
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
	if (vc->mlx.mlx)
	{
		mlx_destroy_window(vc->mlx.mlx, vc->mlx.window);
		mlx_destroy_display(vc->mlx.mlx);
		free(vc->mlx.mlx);
	}
}

void	free_game(t_vc *vc)
{
    if (vc->map.matrix) {
        free_split(vc->map.matrix);
        vc->map.matrix = NULL;
    }
    if (vc->map.matrix_ff) {
        free_split(vc->map.matrix_ff);
        vc->map.matrix_ff = NULL;
    }
	if (vc->map_info.ea_texture && vc->map_info.ea_texture->img_ptr)
		mlx_destroy_image(vc->mlx.mlx, vc->map_info.ea_texture->img_ptr);
	if (vc->map_info.no_texture && vc->map_info.no_texture->img_ptr)
		mlx_destroy_image(vc->mlx.mlx, vc->map_info.no_texture->img_ptr);
	if (vc->map_info.so_texture && vc->map_info.so_texture->img_ptr)
		mlx_destroy_image(vc->mlx.mlx, vc->map_info.so_texture->img_ptr);
	if (vc->map_info.we_texture && vc->map_info.we_texture->img_ptr)
		mlx_destroy_image(vc->mlx.mlx, vc->map_info.we_texture->img_ptr);
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
    if (get_floor(&vc->map, &vc->map_info) == 1)
        exit(1);
    if (get_ceiling(&vc->map, &vc->map_info) == 1)
		exit(1);
    int i = -1;
    while (vc->map.file[++i])
    {
        printf("%s", vc->map.file[i]);
    }
    printf("\n\n --------------------------------- \n\n");
    get_width(&vc->map);
    second_map(&vc->map);
	i = -1;
    while (vc->map.matrix_ff[++i])
    {
        printf("%s", vc->map.matrix_ff[i]);
    }
    if (check_map(&vc->map) == 1)
	{
		dprintf(2, "HALLOHA\n");
        exit(1);
	}
	printf("oi\n");
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
	init_images(vc);
	find_enemies(vc);
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
	// mlx_hook(vc->mlx.window, 17, 0L, close_window, vc);
	if (!vc->mlx.window) {
    printf("Window creation failed!\n");
	} else {
	    printf("Window created successfully!\n");
	}
	int result = mlx_hook(vc->mlx.window, 17, 0L, close_window, vc);

	printf("mlx_hook result: %d\n", result);
	mlx_do_key_autorepeatoff(vc->mlx.mlx);
    mlx_loop(vc->mlx.mlx);
	if (vc->map.file) {
        free_split(vc->map.file);
        vc->map.file = NULL;
	}
}


int main(int ac, char **av)
{
	if (!check_args(ac, av))
		return (0);
	init(av[1]);
	return (0);
}

// mapa nao funciona sem espaços na frente e texturas!