/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:52:38 by codespace         #+#    #+#             */
/*   Updated: 2025/11/08 10:18:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    update_sprite_frame(t_sprite *sprite, double current_time)
{
    if (current_time - sprite->last_update >= sprite->frame_time)
    {
        sprite->current_frame++;
        if(sprite->current_frame >= sprite->frame_count)
            sprite->current_frame = 0;
        sprite->last_update = current_time;
    }
}

void    update_all_sprites(t_config *data, double current_time)
{
	int i ;
	
	i = 0;
	while (i < data->sprite_count)
	{
		update_sprite_frame(&data->sprites[i], current_time);
		i++;
	}
}
