/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:23 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/10 13:27:21 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	placeplayer(t_vc *vc)
{
	int	i;
	int	j;

	i = 0;
	while (vc->map.matrix[i])
	{
		j = 0;
		while (j < vc->map.matrix[i][j])
		{
			if (vc->map.matrix[i][j] == 'N')
			{
				vc->player.grid_x = j;
				vc->player.grid_y = i;	
				vc->player.facing = 270;
				vc->player.pos_x = j + 0.5;
				vc->player.pos_y = i + 0.5;
				vc->player.angle = 270 * (PI / 180);
				vc->player.direction_x = 0.00;
				vc->player.direction_y = -1.00;
				vc->player.plane_x = 0.66;
				vc->player.plane_y = 0.00;
			}
			if (vc->map.matrix[i][j] == 'S')
			{
				vc->player.grid_x = j;
				vc->player.grid_y = i;		
				vc->player.pos_x = j + 0.5;
				vc->player.pos_y = i + 0.5;
				vc->player.angle = 90 * (PI / 180);
				vc->player.direction_x = 0.00;
				vc->player.direction_y = 1.00;
				vc->player.plane_x = -0.66;
				vc->player.plane_y = 0.00;
			}
			if (vc->map.matrix[i][j] == 'E')
			{
				vc->player.grid_x = j;
				vc->player.grid_y = i;		
				vc->player.pos_x = j + 0.5;
				vc->player.pos_y = i + 0.5;
				vc->player.angle = 0 * (PI / 180);
				vc->player.direction_x = 1.00;
				vc->player.direction_y = 0.00;
				vc->player.plane_x = 0.00;
				vc->player.plane_y = 0.66;
			}
			if (vc->map.matrix[i][j] == 'W')
			{
				vc->player.grid_x = j;
				vc->player.grid_y = i;		
				vc->player.pos_x = j + 0.5;
				vc->player.pos_y = i + 0.5;
				vc->player.angle = 180 * (PI / 180);
				vc->player.direction_x = -1.00;
				vc->player.direction_y = 0.00;
				vc->player.plane_x = 0.00;
				vc->player.plane_y = -0.66;
			}
			j++;
		}
		i++;
	}
}

void init_images(t_vc *vc)
{
    int width;
	int height;

	vc->current_bee_image = 0;
    vc->bees = ft_calloc(2, sizeof(void *));
    if (!vc->bees)
    {
        printf("Erro ao alocar memória para as imagens das abelhas.\n");
        return;
    }
    vc->bees[0] = mlx_xpm_file_to_image(vc->mlx.mlx, "srcs/xpm/abelha.xpm", &width, &height);
    if (!vc->bees[0])
        printf("Erro ao carregar a imagem da abelha.\n");
    else
        printf("Imagem da abelha carregada com sucesso. Tamanho: %d x %d\n", width, height);
    vc->bees[1] = mlx_xpm_file_to_image(vc->mlx.mlx, "srcs/xpm/abelha1.xpm", &width, &height);
    if (!vc->bees[1])
        printf("Erro ao carregar a imagem do segurança.\n");
    else
        printf("Imagem do segurança carregada com sucesso. Tamanho: %d x %d\n", width, height);
}

void find_enemies(t_vc *vc)
{
	int y;
	int x;

	y = 0;
	vc->enemy_count = 0;
	while (vc->map.matrix[y])
	{
		x = 0;
        while (vc->map.matrix[y][x])
        {
            if (vc->map.matrix[y][x] == 'B')
            {
                vc->enemies[vc->enemy_count].x = x + 0.5;
                vc->enemies[vc->enemy_count].y = y + 0.5;
                vc->enemy_count++;
                
                if (vc->enemy_count >= MAX_ENEMIES)
                    return;
            }
			x++;
        }
		y++;
    }
}

void draw_bees(t_vc *vc)
{
	if (!vc->bees[0])
		return;
    for (int i = 0; i < vc->enemy_count; i++)
    {
        double dx = vc->enemies[i].x - vc->player.pos_x;
        double dy = vc->enemies[i].y - vc->player.pos_y;

        double inv_det = 1.0 / (vc->player.plane_x * vc->player.direction_y - vc->player.direction_x * vc->player.plane_y);

        double transform_x = inv_det * (vc->player.direction_y * dx - vc->player.direction_x * dy);
        double transform_y = inv_det * (-vc->player.plane_y * dx + vc->player.plane_x * dy);

        if (transform_y <= 0)
            continue;

        int sprite_screen_x = (X_SCREEN / 2) * (1 + transform_x / transform_y);
        int sprite_height = abs((int)(Y_SCREEN / transform_y));

        int draw_start_y = -sprite_height / 2 + Y_SCREEN / 2;
        if (draw_start_y < 0)
            draw_start_y = 0;
        int draw_end_y = sprite_height / 2 + Y_SCREEN / 2;
        if (draw_end_y >= Y_SCREEN)
            draw_end_y = Y_SCREEN - 1;
        mlx_put_image_to_window(vc->mlx.mlx, vc->mlx.window, vc->bees[vc->current_bee_image], sprite_screen_x, draw_start_y);
    }
}

void move_bees(t_vc *vc)
{
    for (int i = 0; i < vc->enemy_count; i++)
    {
        double dx = vc->player.pos_x - vc->enemies[i].x;
        double dy = vc->player.pos_y - vc->enemies[i].y;

        double distance = sqrt(dx * dx + dy * dy);
        double move_speed = 0.3;

        if (distance > 3)
        {
            if (dy > 0)
                vc->enemies[i].y += move_speed;
            else if (dy < 0) 
                vc->enemies[i].y -= move_speed;
        }
		// printf("Bee %d - x: %.2f, y: %.2f\n", i, vc->enemies[i].x, vc->enemies[i].y);
    }
}
