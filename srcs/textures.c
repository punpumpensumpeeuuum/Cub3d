/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:41:52 by jomendes          #+#    #+#             */
/*   Updated: 2025/02/21 15:51:04 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_trim_and_strdup(const char *str, int start)
{
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	return (ft_strdup(str + start));
}

void	alloc_textures1(t_vc *vc)
{
	int	y;
	int	len;

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

void	load_texture(t_data *texture, void *mlx, char *file_path)
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
	texture->img_ptr = mlx_xpm_file_to_image(mlx, file_path,
			&texture->img_size_x, &texture->img_size_y);
	if (!texture->img_ptr)
	{
		printf("Error: failed to load texture: %s\n", file_path);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img_ptr, \
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (texture->addr == NULL)
	{
		printf("Error: failed to get texture address: %s\n", file_path);
		exit(1);
	}
}

void	alloc_textures(t_vc *vc)
{
	vc->map_info.no_texture = malloc(sizeof(t_data));
	vc->map_info.so_texture = malloc(sizeof(t_data));
	vc->map_info.ea_texture = malloc(sizeof(t_data));
	vc->map_info.we_texture = malloc(sizeof(t_data));
	vc->canva = malloc(sizeof(t_data));
	if (!vc->map_info.no_texture || !vc->map_info.so_texture || \
			!vc->map_info.ea_texture || !vc->map_info.we_texture)
	{
		printf("Error: failed to allocate memory for textures.\n");
		exit(1);
	}
	vc->canva->img_ptr = mlx_new_image(vc->mlx.mlx, X_SCREEN, Y_SCREEN);
	vc->canva->addr = mlx_get_data_addr(vc->canva->img_ptr, \
			&vc->canva->bits_per_pixel, &vc->canva->line_length, \
				&vc->canva->endian);
	vc->canva->img_size_x = X_SCREEN;
	vc->canva->img_size_y = Y_SCREEN;
	load_texture(vc->map_info.no_texture, vc->mlx.mlx, vc->map_info.no);
	load_texture(vc->map_info.so_texture, vc->mlx.mlx, vc->map_info.so);
	load_texture(vc->map_info.ea_texture, vc->mlx.mlx, vc->map_info.ea);
	load_texture(vc->map_info.we_texture, vc->mlx.mlx, vc->map_info.we);
}

int	rgb_def_check(char *str)
{
	int	i;

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
