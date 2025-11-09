/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:48:53 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 09:20:34 by codespace        ###   ########.fr       */
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
    char        *frames[41] = {
		"flame3/PNG/00.png", "flame3/PNG/01.png", "flame3/PNG/02.png",
        "flame3/PNG/03.png", "flame3/PNG/04.png", "flame3/PNG/05.png",
        "flame3/PNG/06.png", "flame3/PNG/07.png", "flame3/PNG/08.png",
        "flame3/PNG/09.png", "flame3/PNG/10.png", "flame3/PNG/11.png",
        "flame3/PNG/12.png", "flame3/PNG/13.png", "flame3/PNG/14.png",
        "flame3/PNG/15.png", "flame3/PNG/16.png", "flame3/PNG/17.png",
        "flame3/PNG/18.png", "flame3/PNG/19.png", "flame3/PNG/20.png",
        "flame3/PNG/21.png", "flame3/PNG/22.png", "flame3/PNG/23.png",
        "flame3/PNG/24.png", "flame3/PNG/25.png", "flame3/PNG/26.png",
        "flame3/PNG/27.png", "flame3/PNG/28.png", "flame3/PNG/29.png",
        "flame3/PNG/30.png", "flame3/PNG/31.png", "flame3/PNG/32.png",
        "flame3/PNG/33.png", "flame3/PNG/34.png", "flame3/PNG/35.png",
        "flame3/PNG/36.png", "flame3/PNG/37.png", "flame3/PNG/38.png",
        "flame3/PNG/39.png", "flame3/PNG/40.png"
    };
    t_sprite    *sprite;

    data->sprite_count = 0;
    data->sprites = NULL;
    
    // Create weapon sprite (position doesn't matter for HUD weapon)
    sprite = created_sprite(0.0, 0.0, frames, 41);
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
        printf("Info: No weapon sprite loaded (textures not found)\n");
    }
}
