/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:43:22 by dinda-si          #+#    #+#             */
/*   Updated: 2024/12/05 04:17:00 by elemesmo         ###   ########.fr       */
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
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_minimap
{
	char	**map;
	int		x;
	int		y;
	int		onoff;
}		t_minimap;

typedef struct s_map
{
	char	**matrix;
	char	**matrix_ff;
	int		x;
	int		y;
}		t_map;

typedef struct	s_mlx
{
	void			*window;
	int				x;
	int				y;
	void			*mlx;
}	t_mlx;

typedef struct s_player
{
	int				x;
	int				y;
}	t_play;


typedef struct s_voidcollector
{
	t_mlx			mlx;
	t_play			play;
	t_map			map;
	t_minimap		minimap;
}	t_vc;

int		check_args(int ac, char **av);
char	**get_map(char *file, t_map *map);
void	error(char *str);
void	drawminimap(t_vc *vc);
void	draw_rectangle(t_vc *vc, int h, int w, int color);

#endif