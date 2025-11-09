/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:48:53 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 08:54:30 by codespace        ###   ########.fr       */
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
    sprite->frame_time = 0.033; // ~30 FPS for smoother animation
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
    char        *frames[49] = {
        "flame3/png/flame_00.png", "flame3/png/flame_01.png", "flame3/png/flame_02.png",
        "flame3/png/flame_03.png", "flame3/png/flame_04.png", "flame3/png/flame_05.png",
        "flame3/png/flame_06.png", "flame3/png/flame_07.png", "flame3/png/flame_08.png",
        "flame3/png/flame_09.png", "flame3/png/flame_10.png", "flame3/png/flame_11.png",
        "flame3/png/flame_12.png", "flame3/png/flame_13.png", "flame3/png/flame_14.png",
        "flame3/png/flame_15.png", "flame3/png/flame_16.png", "flame3/png/flame_17.png",
        "flame3/png/flame_18.png", "flame3/png/flame_19.png", "flame3/png/flame_20.png",
        "flame3/png/flame_21.png", "flame3/png/flame_22.png", "flame3/png/flame_23.png",
        "flame3/png/flame_24.png", "flame3/png/flame_25.png", "flame3/png/flame_26.png",
        "flame3/png/flame_27.png", "flame3/png/flame_28.png", "flame3/png/flame_29.png",
        "flame3/png/flame_30.png", "flame3/png/flame_31.png", "flame3/png/flame_32.png",
        "flame3/png/flame_33.png", "flame3/png/flame_34.png", "flame3/png/flame_35.png",
        "flame3/png/flame_36.png", "flame3/png/flame_37.png", "flame3/png/flame_38.png",
        "flame3/png/flame_39.png", "flame3/png/flame_40.png", "flame3/png/flame_41.png",
        "flame3/png/flame_42.png", "flame3/png/flame_43.png", "flame3/png/flame_44.png",
        "flame3/png/flame_45.png", "flame3/png/flame_46.png", "flame3/png/flame_47.png",
        "flame3/png/flame_48.png"
    };
    t_sprite    *sprite;

    data->sprite_count = 0;
    data->sprites = NULL;
    
    // Try to create sprite, but don't fail if textures don't exist
    sprite = created_sprite(5.5, 5.5, frames, 49);
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
