/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:08:41 by dinda-si          #+#    #+#             */
/*   Updated: 2025/02/21 16:15:21 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
