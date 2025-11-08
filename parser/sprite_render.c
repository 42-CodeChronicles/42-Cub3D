/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:00:16 by codespace         #+#    #+#             */
/*   Updated: 2025/11/08 10:02:33 by codespace        ###   ########.fr       */
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

// Draw one sprite
void draw_sprite(mlx_image_t *img, t_config *data, t_sprite *sprite)
{
    double distance = get_sprite_distance(data, sprite);
    
    // Get current animation frame
    mlx_texture_t *texture = sprite->frames[sprite->current_frame];
    
    // Calculate where to draw it (like drawing walls)
    int sprite_height = (int)((WALL_HEIGHT / distance) * (SCREEN_HEIGHT / 2));
    int sprite_width = sprite_height; // Make it square
    
    // Calculate position on screen
    double angle_to_sprite = atan2(
        sprite->y - (data->map.player_pos.y / TILE_SIZE),
        sprite->x - (data->map.player_pos.x / TILE_SIZE)
    );
    
    double angle_diff = angle_to_sprite - data->map.player_pos.angle;
    
    // Normalize angle
    while (angle_diff < -M_PI) angle_diff += 2 * M_PI;
    while (angle_diff > M_PI) angle_diff -= 2 * M_PI;
    
    int screen_x = (SCREEN_WIDTH / 2) + (int)((angle_diff / (FOV * M_PI / 180)) * SCREEN_WIDTH);
    
    // Draw the sprite texture pixel by pixel
    int start_y = (SCREEN_HEIGHT - sprite_height) / 2;
    int start_x = screen_x - sprite_width / 2;
    
    for (int y = 0; y < sprite_height; y++)
    {
        for (int x = 0; x < sprite_width; x++)
        {
            int screen_y = start_y + y;
            int screen_x_pos = start_x + x;
            
            // Make sure we're drawing inside the screen
            if (screen_x_pos >= 0 && screen_x_pos < SCREEN_WIDTH &&
                screen_y >= 0 && screen_y < SCREEN_HEIGHT)
            {
                // Get color from texture
                int tex_x = (x * texture->width) / sprite_width;
                int tex_y = (y * texture->height) / sprite_height;
                
                uint32_t color = get_texture_color(texture, tex_x, tex_y);
                
                // Don't draw transparent pixels
                if ((color & 0xFF) > 0)
                    mlx_put_pixel(img, screen_x_pos, screen_y, color);
            }
        }
    }
}