/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:39 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/21 00:01:27 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_player_dot(mlx_image_t *img, int x, int y)
{
	int	dot_size;
	int	i;
	int	j;
	int pixel_x;
	int pixel_y;
	
	dot_size = 6;
	i = 0;
	while (i < dot_size)
	{
		j = 0;
		while (j < dot_size)
		{
			pixel_x = x + i - dot_size / 2;
			pixel_y = y + j - dot_size / 2;
			
			 if (pixel_x >= 0 && pixel_x < (int)img->width &&
                pixel_y >= 0 && pixel_y < (int)img->height)
                mlx_put_pixel(img, pixel_x, pixel_y, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

void	draw_line_dda(mlx_image_t *img, t_config *data, double angle,
		double distance)
{
	(void)img;
	(void)data;
	(void)angle;
	(void)distance;
}

void	draw_direction_line(mlx_image_t *img, t_config *data)
{
	(void)img;
	(void)data;
}

static void	draw_scaled_tile(mlx_image_t *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size && x + i < (int)img->width)
	{
		j = 0;
		while (j < size && y + j < (int)img->height)
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
	int		x;
	int		y;
	int		map_x;
	int		map_y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			map_x = x * 7;
			map_y = y * 7;
			if (data->map.array_map[y][x] == '1')
				draw_scaled_tile(minimap_image, map_x, map_y, 7, 0x808080FF);
			else if (data->map.array_map[y][x] == 'D')
				draw_scaled_tile(minimap_image, map_x, map_y, 7, 0x00FF00FF);
			else
				draw_scaled_tile(minimap_image, map_x, map_y, 7, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	draw_minimap(mlx_image_t *minimap_image, t_config *data)
{
	int	player_x;
	int	player_y;
	
	draw_map_tiles(minimap_image, data);
	player_x = (int)((data->map.player_pos.x / TILE_SIZE) * 7);
	player_y = (int)((data->map.player_pos.y / TILE_SIZE) * 7);
	draw_player_dot(minimap_image, player_x, player_y);
}
