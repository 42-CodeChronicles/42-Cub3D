/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:00:16 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 10:57:18 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// Calculate how far the sprite is from player
double	get_sprite_distance(t_config *data, t_sprite *sprite)
{
	double	dx;
	double	dy;

	dx = sprite->x - (data->map.player_pos.x / TILE_SIZE);
	dy = sprite->y - (data->map.player_pos.y / TILE_SIZE);
	return (sqrt(dx * dx + dy * dy));
}

// Draw sprite in 3D world space (not as HUD)
void	draw_sprite(mlx_image_t *img, t_config *data, t_sprite *sprite)
{
	double dx;
	double dy;
	double distance;
	double angle_to_sprite;
	double sprite_angle;
	int screen_x;
	double sprite_height;
	double sprite_width;
	int start_y;
	int start_x;
	int end_x;
	mlx_texture_t *texture;

	// Get current animation frame
	texture = sprite->frames[sprite->current_frame];

	// Calculate relative position to player
	dx = sprite->x - (data->map.player_pos.x / TILE_SIZE);
	dy = sprite->y - (data->map.player_pos.y / TILE_SIZE);
	distance = sqrt(dx * dx + dy * dy);

	// Don't draw if too far or too close
	if (distance < 0.5 || distance > 20.0)
		return ;

	// Calculate angle to sprite from player
	angle_to_sprite = atan2(dy, dx);

	// Calculate relative angle (difference from player's view direction)
	sprite_angle = angle_to_sprite - data->map.player_pos.angle;

	// Normalize angle to [-PI, PI]
	while (sprite_angle > M_PI)
		sprite_angle -= 2 * M_PI;
	while (sprite_angle < -M_PI)
		sprite_angle += 2 * M_PI;

	// Check if sprite is in field of view (FOV is 60 degrees = ~1.047 radians)
	if (fabs(sprite_angle) > (FOV * M_PI / 180.0) / 2.0 + 0.3)
		return ;

	// Calculate screen position
	screen_x = (int)((SCREEN_WIDTH / 2) * (1.0 + tan(sprite_angle) / tan((FOV
						* M_PI / 180.0) / 2.0)));

	// Calculate sprite size based on distance (perspective)
	sprite_height = (SCREEN_HEIGHT / distance) * 0.8;
	sprite_width = (texture->width * sprite_height) / texture->height;

	// Calculate screen positions
	start_y = (SCREEN_HEIGHT - sprite_height) / 2;
	start_x = screen_x - (sprite_width / 2);
	end_x = start_x + sprite_width;

	// Draw sprite column by column
	int x = start_x;
	while (x < end_x)
	{
		if (x >= 0 && x < SCREEN_WIDTH)
		{
			int y = start_y;
			while (y < start_y + sprite_height)
			{
				if (y >= 0 && y < SCREEN_HEIGHT)
				{
					// Map screen coordinates to texture coordinates
					int tex_x = ((x - start_x) * texture->width) / sprite_width;
					int tex_y = ((y - start_y) * texture->height)
						/ sprite_height;

					if (tex_x >= 0 && tex_x < (int)texture->width && tex_y >= 0
						&& tex_y < (int)texture->height)
					{
						uint32_t color = get_texture_color(texture, tex_x,
								tex_y);

						// Don't draw transparent pixels (alpha channel check)
						if ((color & 0xFF) > 0)
							mlx_put_pixel(img, x, y, color);
					}
				}
				y++;
			}
		}
		x++;
	}
}