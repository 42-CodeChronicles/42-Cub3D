/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:00:00 by codespace         #+#    #+#             */
/*   Updated: 2025/11/19 17:07:09 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_weapon_dimensions(mlx_texture_t *texture, int *w, int *h)
{
	*w = texture->width * 0.4;
	*h = texture->height * 0.4;
}

void	get_weapon_position(int weapon_width, int weapon_height,
		int *start_x, int *start_y)
{
	*start_x = SCREEN_WIDTH - weapon_width - 400 ;
	*start_y = SCREEN_HEIGHT - weapon_height ;
}

void	update_weapon_frame(t_weapon *weapon, double current_time)
{
	if (!weapon->is_shooting)
	{
		weapon->current_frame = 0;
		return ;
	}
	if (current_time - weapon->last_update >= weapon->frame_time)
	{
		weapon->current_frame++;
		if (weapon->current_frame >= weapon->frame_count)
		{
			weapon->current_frame = 0;
			weapon->is_shooting = 0;
		}
		weapon->last_update = current_time;
	}
}
