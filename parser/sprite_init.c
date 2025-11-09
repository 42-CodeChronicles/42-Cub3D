/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:48:53 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 08:35:45 by codespace        ###   ########.fr       */
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
    sprite->current_frame = 0;
    sprite->frame_time = 0.1; 
    sprite->last_update = 0;
    sprite->frames = malloc(sizeof(mlx_texture_t *) * count);
    if (!sprite->frames)
    {
        free(sprite);
        return NULL;
    }
    i = 0;
    while (i < count)
    {
        sprite->frames[i] = mlx_load_png(frame_path[i]);
        if(!sprite->frames[i])
        {
            printf("Warning: Can't load sprite frame '%s', skipping sprite\n", frame_path[i]);
            // Free previously loaded frames
            while (--i >= 0)
                mlx_delete_texture(sprite->frames[i]);
            free(sprite->frames);
            free(sprite);
            return NULL;
        }
        i++;
    }
    return sprite;
}

void    sprite_init(t_config *data)
{
    char        *frames[3] = {"textures/fire1.png", "textures/fire2.png", "textures/fire3.png"};
    t_sprite    *sprite;

    data->sprite_count = 0;
    data->sprites = NULL;
    
    // Try to create sprite, but don't fail if textures don't exist
    sprite = created_sprite(5.5, 5.5, frames, 3);
    if (sprite)
    {
        data->sprite_count = 1;
        data->sprites = malloc(sizeof(t_sprite) * 1);
        if (data->sprites)
            data->sprites[0] = *sprite;
        free(sprite);
    }
    else
    {
        printf("Info: No sprites loaded (sprite textures not found)\n");
    }
}
