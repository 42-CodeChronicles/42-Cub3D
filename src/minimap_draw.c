/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:39 by ayaarab           #+#    #+#             */
/*   Updated: 2025/12/03 14:42:46 by ayaarab          ###   ########.fr       */
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

static void	draw_map_tiles_helper(mlx_image_t *minimap_image,
	t_config *data, t_minimap_draw vars)
{
	if (data->map.array_map[vars.y][vars.x] == '1')
		draw_scaled_tile(minimap_image, vars.screen_x, vars.screen_y,
			0x808080FF);
	else if (data->map.array_map[vars.y][vars.x] == 'D')
		draw_scaled_tile(minimap_image, vars.screen_x, vars.screen_y,
			0x00FF00FF);
	else
		draw_scaled_tile(minimap_image, vars.screen_x, vars.screen_y,
			0x000000FF);
}

static void	draw_map_tiles(mlx_image_t *minimap_image, t_config *data)
{
	t_minimap_draw	vars;
	int				player_tile_x;
	int				player_tile_y;

	vars.tile_size = 7;
	vars.tiles_radius = (MINIMAP_SIZE / vars.tile_size) / 2;
	player_tile_x = (int)(data->map.player_pos.x / TILE_SIZE);
	player_tile_y = (int)(data->map.player_pos.y / TILE_SIZE);
	vars.y = player_tile_y - vars.tiles_radius;
	while (vars.y <= player_tile_y + vars.tiles_radius)
	{
		vars.x = player_tile_x - vars.tiles_radius;
		while (vars.x <= player_tile_x + vars.tiles_radius)
		{
			vars.screen_x = (vars.x - (player_tile_x - vars.tiles_radius))
				* vars.tile_size;
			vars.screen_y = (vars.y - (player_tile_y - vars.tiles_radius))
				* vars.tile_size;
			if (vars.x >= 0 && vars.x < data->map.width && vars.y >= 0
				&& vars.y < data->map.height)
				draw_map_tiles_helper(minimap_image, data, vars);
			vars.x++;
		}
		vars.y++;
	}
}

void	draw_minimap(mlx_image_t *minimap_image, t_config *data)
{
	draw_map_tiles(minimap_image, data);
	draw_player_dot(minimap_image, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2);
}
