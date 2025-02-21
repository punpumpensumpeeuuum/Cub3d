/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:43:22 by dinda-si          #+#    #+#             */
/*   Updated: 2025/02/21 16:24:44 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <time.h>
# include <sys/time.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# define PI 3.14159265358979323846
# define PLAYERCOLOR 0xff0000
# define FOV 720
# define MOVE_SPEED 0.1
# define L_ARROW 65361
# define R_ARROW 65363
# define X_SCREEN 720 //3840 3840 768
# define Y_SCREEN 480 //1990 1990 398
# define MAX_ENEMIES 2

typedef struct s_minimap
{
	int				a;
	int				onoff;
	void			*player;
	void			*wall;
	void			*floor;
}			t_minimap;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}	t_rgb;

typedef struct s_data
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_size_x;
	int				img_size_y;
}			t_data;

typedef struct s_map
{
	char			**file;
	char			**matrix;
	char			**matrix_ff;
	int				index;
	int				file_heigth;
	int				x;
	int				y;
}		t_map;

typedef struct s_mlx
{
	void			*window;
	void			*mlx;
	int				x;
	int				y;
	int				pixelx;
	int				pixely;
}	t_mlx;

typedef struct s_player
{
	int				facing;
	int				w;
	int				a;
	int				s;
	int				d;
	int				o;
	double			pos_x;
	double			pos_y;
	int				grid_x;
	int				grid_y;
	double			plane_x;
	double			plane_y;
	double			direction_x;
	double			direction_y;
	double			angle;
}	t_player;

typedef struct s_ray
{
	int				id;
	int				pos_x;
	int				pos_y;
	double			direction_x;
	double			direction_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			distance_x;
	double			distance_y;
	double			real_size;
	int				side;
	int				line_height;
	int				wall_start;
	int				wall_end;
	int				step_x;
	int				step_y;
	int				x_texture;
	int				y_texture;
}					t_ray;

typedef struct s_map_info
{
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	char			*floor;
	char			*ceiling;
	t_data			*no_texture;
	t_data			*so_texture;
	t_data			*we_texture;
	t_data			*ea_texture;
	t_rgb			ceiling_color;
	t_rgb			floor_color;
}					t_map_info;

typedef struct s_enemy
{
	double	x;
	double	y;
}	t_enemy;

typedef struct s_voidcollector
{
	t_mlx			mlx;
	t_player		player;
	t_map			map;
	t_minimap		minimap;
	t_map_info		map_info;
	t_ray			ray;
	t_data			data;
	t_data			*canva;
	t_enemy			enemies[MAX_ENEMIES];
	int				enemy_count;
	void			**bees;
	int				current_bee_image;
}	t_vc;

int		check_closed(t_map *map);
int		where_is_player(t_map *map);
char	*ft_trim_and_strdup(const char *str, int start);
int		check_textures(t_map *map);
int		my_pixel_get(t_data *data, int x, int y);
int		valid_chars(t_map *map);
void	free_split(char **str);
int		close_window(t_vc *vc);
int		coma_counter(char *str);
int		rgb_def_check(char *str);
int		check_args(int ac, char **av);
char	**get_map(t_map *map);
void	error(char *str);
void	drawminimap(t_vc *vc);
void	draw_rectangle(t_vc *vc, char c, int i, int j);
char	**get_file(char *file, t_map *map);
int		get_file_heigth(char *file);
void	get_width(t_map *map);
char	*create_top_bottom(t_map *map);
void	second_map(t_map *map);
int		check_map_x(t_map *map, int y);
int		check_map(t_map *map, t_vc *vc);
int		check_0(t_map *map);
void	map_index(t_map *map);
void	placeplayer(t_vc *vc);
int		get_floor(t_map *map, t_map_info *info);
int		get_ceiling(t_map *map, t_map_info *info);
int		get_floor_color(t_map_info *info);
int		get_ceiling_color(t_map_info *info);
void	place_player_aux(t_vc *vc, int *i, int *j);
void	player_south(t_vc *vc, int i, int j);
void	player_east(t_vc *vc, int i, int j);
void	player_west(t_vc *vc, int i, int j);
void	my_img_clear(t_data data);
char	*ft_trim_and_strdup(const char *str, int start);
void	alloc_textures1(t_vc *vc);
void	load_texture(t_data *texture, void *mlx, char *file_path);
void	alloc_textures(t_vc *vc);
int		rgb_def_check(char *str);
int		closegame(t_vc *vc);
int		keypress(int keycode, t_vc *vc);
int		keyunpress(int keycode, t_vc *vc);
void	my_img_clear(t_data data);
void	checkcolors(t_vc *vc);
void	anotherinit(t_vc *vc);
void	free_game(t_vc *vc);
void	destroy_map(t_vc *vc);
void	free_mlx(t_vc *vc);

// raycasting
void	dda_style(t_vc *vc);
void	dda_step_calc(t_vc *vc);
void	dda_real_distance_calc(t_vc *vc);
void	dda_wall_height(t_ray *ray);
void	dda_side_selector(t_vc *vc, t_ray *ray, t_player *player,
			t_map_info *info);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_raycolor(int tex_x, int tex_y, t_data *data);
void	draw_walls(t_vc *vc, t_ray *ray, t_data *texture);
void	draw_floor_ceiling(t_vc *vc, t_ray *ray);

// movement

void	move_camera(t_vc *vc);
void	movemnt(t_vc *vc);
void	frente_movimento(t_vc *vc);
void	lado_movimento(t_vc *vc);

#endif