/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:37:17 by aychikhi          #+#    #+#             */
/*   Updated: 2025/11/19 16:06:25 by ayaarab          ###   ########.fr       */
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

static void	populate_doors(t_config *data)
{
	int	door_index;
	int	x;
	int	y;

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
				data->doors[door_index].is_door = 1;
				door_index++;
			}
			x++;
		}
		y++;
	}
}

static void	load_door_texture(t_config *data)
{
	data->door_texture = mlx_load_png("./textures/door.png");
	if (!data->door_texture)
	{
		printf("Error: Can't load Door texture\n");
		data->door_texture = data->no_texture;
	}
}

void	init_doors(t_config *data)
{
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
	populate_doors(data);
	load_door_texture(data);
}

int	check_door(t_config *data, int x, int y)
{
	int	i;

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
