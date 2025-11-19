/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:43:04 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/19 14:35:43 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_tile(mlx_image_t *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int	is_valid_pos(t_config *data, int tx, int ty)
{
	if (tx < 0 || tx >= data->map.width || ty < 0 || ty >= data->map.height)
		return (0);
	return (1);
}

int	check_collision(t_config *data, int new_x, int new_y)
{
	int	dot_size;
	int	left;
	int	right;
	int	top;
	int	bottom;

	dot_size = TILE_SIZE / 8;
	left = (new_x - dot_size) / TILE_SIZE;
	right = (new_x + dot_size) / TILE_SIZE;
	top = (new_y - dot_size) / TILE_SIZE;
	bottom = (new_y + dot_size) / TILE_SIZE;
	if (!is_valid_pos(data, left, top) || !is_valid_pos(data, right, top)
		|| !is_valid_pos(data, left, bottom)
		|| !is_valid_pos(data, right, bottom))
		return (1);
	if (data->map.array_map[top][left] == '1'
		|| data->map.array_map[top][right] == '1'
		|| data->map.array_map[top][left] == 'D'
		|| data->map.array_map[top][right] == 'D')
		return (1);
	if (data->map.array_map[bottom][left] == '1'
		|| data->map.array_map[bottom][right] == '1'
		||	data->map.array_map[bottom][left] == 'D'
		|| data->map.array_map[bottom][right] == 'D'
	)
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
