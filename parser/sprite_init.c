/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:48:53 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 10:57:16 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_sprite	*created_sprite(double x, double y, char **frame_path, int count)
{
	int			i;
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	sprite->x = x;
	sprite->y = y;
	sprite->frame_count = count;
	sprite->current_frame = 0;
	sprite->frame_time = 0.033; // ~30 FPS for smoother animation
	sprite->last_update = 0;
	sprite->frames = malloc(sizeof(mlx_texture_t *) * count);
	if (!sprite->frames)
	{
		free(sprite);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		sprite->frames[i] = mlx_load_png(frame_path[i]);
		if (!sprite->frames[i])
		{
			printf("Warning: Can't load sprite frame '%s', skipping sprite\n",
				frame_path[i]);
			// Free previously loaded frames
			while (--i >= 0)
				mlx_delete_texture(sprite->frames[i]);
			free(sprite->frames);
			free(sprite);
			return (NULL);
		}
		i++;
	}
	return (sprite);
}

static int	is_empty_tile(t_config *data, int x, int y)
{
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width)
		return (0);
	if (data->map.array_map[y][x] == '0')
		return (1);
	return (0);
}

static void	find_random_positions(t_config *data, int num_sprites,
		int *positions)
{
	int		attempts;
	int		x;
	int		y;
	int		i;
	int		j;
	int		duplicate;
	double	dx;
	double	dy;
	double	dist;

	i = 0;
	while (i < num_sprites)
	{
		attempts = 0;
		while (attempts < 1000)
		{
			x = rand() % data->map.width;
			y = rand() % data->map.height;
			// Check if it's an empty tile and not too close to player
			if (is_empty_tile(data, x, y))
			{
				dx = x + 0.5 - (data->map.player_pos.x / TILE_SIZE);
				dy = y + 0.5 - (data->map.player_pos.y / TILE_SIZE);
				dist = sqrt(dx * dx + dy * dy);
				// Not too close to player (at least 3 tiles away)
				if (dist > 3.0)
				{
					// Check for duplicates
					duplicate = 0;
					j = 0;
					while (j < i)
					{
						if (positions[j * 2] == x && positions[j * 2 + 1] == y)
						{
							duplicate = 1;
							break ;
						}
						j++;
					}
					if (!duplicate)
					{
						positions[i * 2] = x;
						positions[i * 2 + 1] = y;
						break ;
					}
				}
			}
			attempts++;
		}
		i++;
	}
}

void	sprite_init(t_config *data)
{
	data->sprite_count = 0;
	data->sprites = NULL;
	printf("Info: Sprite system initialized (no world sprites)\n");
}
