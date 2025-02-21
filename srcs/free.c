/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:08:09 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/21 13:39:11 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(char *str)
{
	write (2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit(1);
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
