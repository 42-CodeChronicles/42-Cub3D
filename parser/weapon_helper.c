/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:00:00 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 15:54:55 by codespace        ###   ########.fr       */
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
	*start_x = SCREEN_WIDTH - weapon_width - 50;
	*start_y = SCREEN_HEIGHT - weapon_height - 20;
}
