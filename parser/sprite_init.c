/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:48:53 by codespace         #+#    #+#             */
/*   Updated: 2025/11/08 09:43:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_sprite    *created_sprite(double x, double y, char **frame_path, int count)
{
    int         i;
    t_sprite    *sprite;

    sprite = malloc(sizeof(t_sprite));
    if (!sprite)
        return NULL;
    sprite->x = x;
    sprite->y = y;
    sprite->frame_count = count;
    sprite->current_sprite = 0;
    sprite->frame_time = 0.1; 
    sprite->last_update = 0;
    sprite->farmes = malloc(sizeof(mlx_texture_t *) * count);
    i = 0;
    while (i < count)
    {
        sprite->farmes[i] = mlx_load_png(frame_path[i]);
        if(!sprtie->frame[i])
        {
            printf("Error: Can't load sprite frame!\n");
            return NULL;
        }
        i++;
    }
    return sprite;
}

void    sprite_init(t_config *data)
{
    char *frames[3] = {"texture/fire1.png", "texture/fire2.png", "texture/fire3.png"};
    data->sprite_count = 1;
    data->sprites = malloc(sizeof(t_sprite) * 1);
    data->sprites[0] = *created_sprite(5.5, 5.5, fire_frames, 3);
}
