/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:55:22 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/30 15:58:31 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	validate_map(t_config *data)
{
	int	i;

	i = 0;
	while (i < data->map.width)
	{
		if (data->map.array_map[0][i] != '1'
			&& data->map.array_map[0][i] != ' ')
			return (0);
		if (data->map.array_map[data->map.height - 1][i] != '1'
			&& data->map.array_map[data->map.height - 1][i] != ' ')
			return (0);
		i++;
	}
	i = 0;
	while (i < data->map.height)
	{
		if (data->map.array_map[i][0] != '1'
			&& data->map.array_map[i][0] != ' ')
			return (0);
		if (data->map.array_map[i][data->map.width - 1] != '1'
			&& data->map.array_map[i][data->map.width - 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	flood_fill(char **map, int x, int y, t_map *map_data)
{
	if (x < 0 || y < 0 || x >= map_data->width || y >= map_data->height)
		print_error_map();
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (map[y][x] == ' ')
		print_error_map();
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, map_data);
	flood_fill(map, x - 1, y, map_data);
	flood_fill(map, x, y + 1, map_data);
	flood_fill(map, x, y - 1, map_data);
}
