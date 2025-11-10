/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:39 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/10 02:26:38 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_player_dot(mlx_image_t *img, int x, int y)
{
	int	dot_size;
	int	i;
	int	j;

	dot_size = TILE_SIZE / 4;
	i = 0;
	while (i < dot_size)
	{
		j = 0;
		while (j < dot_size)
		{
			mlx_put_pixel(img, x + i - dot_size / 2, y + j - dot_size / 2,
				0xFF0000FF);
			j++;
		}
		i++;
	}
}

void	draw_line_dda(mlx_image_t *img, t_config *data, double angle,
		double distance)
{
	int		steps;
	double	dx;
	double	dy;
	double	x;
	double	y;

	dx = cos(angle);
	dy = sin(angle);
	steps = (int)distance;
	x = data->map.player_pos.x;
	y = data->map.player_pos.y;
	while (steps >= 0)
	{
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			mlx_put_pixel(img, (int)x, (int)y, 0xF0FF);
		x += dx;
		y += dy;
		steps--;
	}
}

void	draw_direction_line(mlx_image_t *img, t_config *data)
{
	draw_line_dda(img, data, data->map.player_pos.angle,
		TILE_SIZE * 2);
}

static void	draw_map_tiles(mlx_image_t *minimap_image, t_config *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (!is_valid_pos(data, x, y))
			{
				x++;
				continue ;
			}
			if (data->map.array_map[y][x] == '1')
				draw_tile(minimap_image, x * TILE_SIZE, y * TILE_SIZE,
					0x000000FF);
			else
				draw_tile(minimap_image, x * TILE_SIZE, y * TILE_SIZE,
					0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

void	draw_minimap(mlx_image_t *minimap_image, t_config *data)
{
	draw_map_tiles(minimap_image, data);
	cast_all_rays(minimap_image, data);
	draw_direction_line(minimap_image, data);
	draw_player_dot(minimap_image, data->map.player_pos.x,
		data->map.player_pos.y);
}
