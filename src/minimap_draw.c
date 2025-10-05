#include "../cub3D.h"

void	draw_player_dot(mlx_image_t *img, int x, int y)
{
	int	dot_size;

	dot_size = TILE_SIZE / 4;
	for (int i = 0; i < dot_size; i++)
		for (int j = 0; j < dot_size; j++)
			mlx_put_pixel(img, x + i - dot_size / 2, y + j - dot_size / 2,
				0xFF0000FF);
}

void	draw_direction_line(mlx_image_t *img, t_config *data)
{
	int		line_length;
	int		end_x;
	int		end_y;
	int		dx;
	int		dy;
	int		steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;

	line_length = TILE_SIZE * 2;
	end_x = data->map.player_pos.x + cos(data->map.player_pos.angle)
		* line_length;
	end_y = data->map.player_pos.y + sin(data->map.player_pos.angle)
		* line_length;
	dx = end_x - data->map.player_pos.x;
	dy = end_y - data->map.player_pos.y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x_inc = dx / (double)steps;
	y_inc = dy / (double)steps;
	x = data->map.player_pos.x;
	y = data->map.player_pos.y;
	for (int i = 0; i <= steps; i++)
	{
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			mlx_put_pixel(img, (int)x, (int)y, 0x00FF00FF);
		x += x_inc;
		y += y_inc;
	}
}

void	draw_minimap(mlx_image_t *minimap_image, t_config *data)
{
	for (int y = 0; y < data->map.height; y++)
	{
		for (int x = 0; x < data->map.width; x++)
		{
			if (!is_valid_pos(data, x, y))
				continue ;
			if (data->map.array_map[y][x] == '1')
				draw_tile(minimap_image, x * TILE_SIZE, y * TILE_SIZE,
					0x000000FF);
			else
				draw_tile(minimap_image, x * TILE_SIZE, y * TILE_SIZE,
					0xFFFFFFFF);
		}
	}
	draw_direction_line(minimap_image, data);
	draw_player_dot(minimap_image, data->map.player_pos.x,
		data->map.player_pos.y);
}
