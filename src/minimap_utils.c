/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:43:04 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/21 16:11:15 by ayaarab          ###   ########.fr       */
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
	int	l;
	int	r;
	int	t;
	int	b;

	dot_size = TILE_SIZE / 8;
	l = (new_x - dot_size) / TILE_SIZE;
	r = (new_x + dot_size) / TILE_SIZE;
	t = (new_y - dot_size) / TILE_SIZE;
	b = (new_y + dot_size) / TILE_SIZE;
	if (!is_valid_pos(data, l, t) || !is_valid_pos(data, r, t)
		|| !is_valid_pos(data, l, b) || !is_valid_pos(data, r, b))
		return (1);
	if (data->map.array_map[t][l] == '1'
		|| data->map.array_map[t][r] == '1'
		|| data->map.array_map[t][l] == 'D'
		|| data->map.array_map[t][r] == 'D')
		return (1);
	if (data->map.array_map[b][l] == '1'
		|| data->map.array_map[b][r] == '1'
		|| data->map.array_map[b][l] == 'D'
		|| data->map.array_map[b][r] == 'D')
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
