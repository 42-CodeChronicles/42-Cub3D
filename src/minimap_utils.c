#include "../cub3D.h"

void	draw_tile(mlx_image_t *img, int x, int y, int color)
{
	for (int i = 0; i < TILE_SIZE; i++)
		for (int j = 0; j < TILE_SIZE; j++)
			mlx_put_pixel(img, x + i, y + j, color);
}

int	is_valid_pos(t_config *data, int x, int y)
{
	return (x >= 0 && x < data->map.width && y >= 0 && y < data->map.height);
}

int	check_collision(t_config *data, int new_x, int new_y)
{
	int	dot_size;
	int	t_l_x;
	int	t_l_y;
	int	t_r_x;
	int	t_r_y;
	int	b_l_x;
	int	b_l_y;
	int	b_r_x;
	int	b_r_y;

	dot_size = TILE_SIZE / 8;
	t_l_x = (new_x - dot_size) / TILE_SIZE;
	t_l_y = (new_y - dot_size) / TILE_SIZE;
	t_r_x = (new_x + dot_size) / TILE_SIZE;
	t_r_y = (new_y - dot_size) / TILE_SIZE;
	b_l_x = (new_x - dot_size) / TILE_SIZE;
	b_l_y = (new_y + dot_size) / TILE_SIZE;
	b_r_x = (new_x + dot_size) / TILE_SIZE;
	b_r_y = (new_y + dot_size) / TILE_SIZE;
	if (data->map.array_map[t_l_y][t_l_x] == '1')
		return (1);
	if (data->map.array_map[t_r_y][t_r_x] == '1')
		return (1);
	if (data->map.array_map[b_l_y][b_l_x] == '1')
		return (1);
	if (data->map.array_map[b_r_y][b_r_x] == '1')
		return (1);
	return (0);
}

void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}
