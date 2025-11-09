/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:00:00 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 15:54:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_empty_tile(t_config *data, int x, int y)
{
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width)
		return (0);
	if (data->map.array_map[y][x] == '0')
		return (1);
	return (0);
}

int	is_valid_distance(t_config *data, int x, int y)
{
	double	dx;
	double	dy;
	double	dist;

	dx = x + 0.5 - (data->map.player_pos.x / TILE_SIZE);
	dy = y + 0.5 - (data->map.player_pos.y / TILE_SIZE);
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 3.0)
		return (1);
	return (0);
}

int	check_duplicate(int *positions, int i, int x, int y)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (positions[j * 2] == x && positions[j * 2 + 1] == y)
			return (1);
		j++;
	}
	return (0);
}

int	try_position(t_config *data, int *positions, int i)
{
	int	x;
	int	y;

	x = rand() % data->map.width;
	y = rand() % data->map.height;
	if (is_empty_tile(data, x, y) && is_valid_distance(data, x, y))
	{
		if (!check_duplicate(positions, i, x, y))
		{
			positions[i * 2] = x;
			positions[i * 2 + 1] = y;
			return (1);
		}
	}
	return (0);
}

void	find_random_positions(t_config *data, int num_sprites, int *positions)
{
	int	attempts;
	int	i;

	i = 0;
	while (i < num_sprites)
	{
		attempts = 0;
		while (attempts < 1000)
		{
			if (try_position(data, positions, i))
				break ;
			attempts++;
		}
		i++;
	}
}
