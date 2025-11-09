/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:00:16 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 09:20:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


// Calculate how far the sprite is from player
double get_sprite_distance(t_config *data, t_sprite *sprite)
{
    double dx = sprite->x - (data->map.player_pos.x / TILE_SIZE);
    double dy = sprite->y - (data->map.player_pos.y / TILE_SIZE);
    return (sqrt(dx * dx + dy * dy));
}

// Draw weapon/punch sprite as HUD element (first-person view)
void draw_sprite(mlx_image_t *img, t_config *data, t_sprite *sprite)
{
    // Get current animation frame
    mlx_texture_t *texture = sprite->frames[sprite->current_frame];
    
    // Scale the weapon sprite (adjust these values to your liking)
    int weapon_height = SCREEN_HEIGHT * 0.6;  // 60% of screen height
    int weapon_width = (texture->width * weapon_height) / texture->height; // Maintain aspect ratio
    
    // Position at bottom-center of screen (like FPS weapon view)
    int start_x = (SCREEN_WIDTH - weapon_width) / 2;
    int start_y = SCREEN_HEIGHT - weapon_height;
    
    // Draw the weapon sprite pixel by pixel
    for (int y = 0; y < weapon_height; y++)
    {
        for (int x = 0; x < weapon_width; x++)
        {
            int screen_y = start_y + y;
            int screen_x_pos = start_x + x;
            
            // Make sure we're drawing inside the screen
            if (screen_x_pos >= 0 && screen_x_pos < SCREEN_WIDTH &&
                screen_y >= 0 && screen_y < SCREEN_HEIGHT)
            {
                // Get color from texture (map sprite coordinates to texture)
                int tex_x = (x * texture->width) / weapon_width;
                int tex_y = (y * texture->height) / weapon_height;
                
                uint32_t color = get_texture_color(texture, tex_x, tex_y);
                
                // Don't draw transparent pixels (alpha channel check)
                if ((color & 0xFF) > 0)
                    mlx_put_pixel(img, screen_x_pos, screen_y, color);
            }
        }
    }
}