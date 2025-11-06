/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:37:17 by aychikhi          #+#    #+#             */
/*   Updated: 2025/11/06 16:15:31 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	count_doors(t_config *data)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.array_map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	init_doors(t_config *data)
{
	int	door_index;
	int	x;
	int	y;

	data->door_count = count_doors(data);
	if (!data->door_count)
	{
		data->doors = NULL;
		return ;
	}
	data->doors = malloc(sizeof(t_door) * data->door_count);
	if (!data->doors)
	{
		printf("Error: Can't allocate memory for doors\n");
		return ;
	}
	door_index = 0;
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.array_map[y][x] == 'D')
			{
				data->doors[door_index].x = x;
				data->doors[door_index].y = y;
				data->doors[door_index].is_open = 0;
				data->doors[door_index].open_amount = 0.0;
				door_index++;
			}
			x++;
		}
		y++;
	}
	data->door_texture = mlx_load_png("./textures/door.png");
	if (!data->door_texture)
	{
		printf("Error: Can't load Door texture\n");
		data->door_texture = data->no_texture;
	}
}

int	check_door(t_config *data, int x, int y)
{
	int i;

	if (!data->doors)
		return (0);
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}