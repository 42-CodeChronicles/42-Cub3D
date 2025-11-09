/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:48:53 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 15:54:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	init_sprite_fields(t_sprite *sprite, double x, double y, int count)
{
	sprite->x = x;
	sprite->y = y;
	sprite->frame_count = count;
	sprite->current_frame = 0;
	sprite->frame_time = 0.033;
	sprite->last_update = 0;
}

static int	load_sprite_frames(t_sprite *sprite, char **frame_path, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		sprite->frames[i] = mlx_load_png(frame_path[i]);
		if (!sprite->frames[i])
		{
			printf("Warning: Can't load sprite frame '%s', skipping sprite\n",
				frame_path[i]);
			while (--i >= 0)
				mlx_delete_texture(sprite->frames[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

t_sprite	*created_sprite(double x, double y, char **frame_path, int count)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	init_sprite_fields(sprite, x, y, count);
	sprite->frames = malloc(sizeof(mlx_texture_t *) * count);
	if (!sprite->frames)
	{
		free(sprite);
		return (NULL);
	}
	if (!load_sprite_frames(sprite, frame_path, count))
	{
		free(sprite->frames);
		free(sprite);
		return (NULL);
	}
	return (sprite);
}

void	sprite_init(t_config *data)
{
	data->sprite_count = 0;
	data->sprites = NULL;
	printf("Info: Sprite system initialized (no world sprites)\n");
}
