/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:39 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/23 13:35:12 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_player_dot(mlx_image_t *img, int x, int y)
{
	int	dot_size;
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	dot_size = 8;
	i = 0;
	while (i < dot_size)
	{
		j = 0;
		while (j < dot_size)
		{
			pixel_x = x + i - dot_size / 2;
			pixel_y = y + j - dot_size / 2;
			if (pixel_x >= 0 && pixel_x < (int)img->width && pixel_y >= 0
				&& pixel_y < (int)img->height)
				mlx_put_pixel(img, pixel_x, pixel_y, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

static void	draw_scaled_tile(mlx_image_t *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 20 && x + i < (int)img->width)
	{
		j = 0;
		while (j < 20 && y + j < (int)img->height)
		{
			if (x + i >= 0 && y + j >= 0)
				mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_map_tiles(mlx_image_t *minimap_image, t_config *data)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;
	int	tile_size;
	int	player_tile_x;
	int	player_tile_y;
	int	tiles_radius;

	tile_size = 7;
	tiles_radius = (MINIMAP_SIZE / tile_size) / 2;
	player_tile_x = (int)(data->map.player_pos.x / TILE_SIZE);
	player_tile_y = (int)(data->map.player_pos.y / TILE_SIZE);
	y = player_tile_y - tiles_radius;
	while (y <= player_tile_y + tiles_radius)
	{
		x = player_tile_x - tiles_radius;
		while (x <= player_tile_x + tiles_radius)
		{
			screen_x = (x - (player_tile_x - tiles_radius)) * tile_size;
			screen_y = (y - (player_tile_y - tiles_radius)) * tile_size;
			if (x >= 0 && x < data->map.width && y >= 0 && y < data->map.height)
			{
				if (data->map.array_map[y][x] == '1')
					draw_scaled_tile(minimap_image, screen_x, screen_y,
						0x808080FF);
				else if (data->map.array_map[y][x] == 'D')
					draw_scaled_tile(minimap_image, screen_x, screen_y,
						0x00FF00FF);
				else
					draw_scaled_tile(minimap_image, screen_x, screen_y,
						0x000000FF);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(mlx_image_t *minimap_image, t_config *data)
{
	draw_map_tiles(minimap_image, data);
	draw_player_dot(minimap_image, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2);
}
