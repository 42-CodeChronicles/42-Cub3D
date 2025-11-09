/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:00:00 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 09:51:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	weapon_init(t_config *data)
{
	char	*frames[6] = {
		"weapon/0.png", "weapon/1.png", "weapon/2.png",
		"weapon/3.png", "weapon/4.png", "weapon/5.png"
	};
	int		i;

	data->weapon.frame_count = 6;
	data->weapon.current_frame = 0;
	data->weapon.is_shooting = 0;
	data->weapon.frame_time = 0.05;  // 50ms per frame for shooting animation
	data->weapon.last_update = 0;
	
	data->weapon.frames = malloc(sizeof(mlx_texture_t *) * 6);
	if (!data->weapon.frames)
	{
		printf("Error: Failed to allocate memory for weapon frames\n");
		exit(1);
	}
	
	i = 0;
	while (i < 6)
	{
		data->weapon.frames[i] = mlx_load_png(frames[i]);
		if (!data->weapon.frames[i])
		{
			printf("Error: Can't load weapon frame '%s'\n", frames[i]);
			while (--i >= 0)
				mlx_delete_texture(data->weapon.frames[i]);
			free(data->weapon.frames);
			exit(1);
		}
		i++;
	}
	printf("Weapon loaded successfully with %d frames\n", data->weapon.frame_count);
}

void	update_weapon_frame(t_weapon *weapon, double current_time)
{
	if (!weapon->is_shooting)
	{
		weapon->current_frame = 0;  // Idle frame
		return;
	}
	
	if (current_time - weapon->last_update >= weapon->frame_time)
	{
		weapon->current_frame++;
		if (weapon->current_frame >= weapon->frame_count)
		{
			weapon->current_frame = 0;
			weapon->is_shooting = 0;  // Animation complete
		}
		weapon->last_update = current_time;
	}
}

void	draw_weapon(mlx_image_t *img, t_config *data)
{
	mlx_texture_t	*texture;
	int				weapon_width;
	int				weapon_height;
	int				start_x;
	int				start_y;
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	uint32_t		color;

	texture = data->weapon.frames[data->weapon.current_frame];
	
	// Scale weapon to smaller size - adjust scale factor here (0.8 = 80% of original)
	weapon_width = texture->width * 0.8;
	weapon_height = texture->height * 0.8;
	
	// Position weapon at bottom-right corner (with small margin)
	start_x = SCREEN_WIDTH - weapon_width - 50;  // 50px margin from right
	start_y = SCREEN_HEIGHT - weapon_height - 20;  // 20px margin from bottom
	
	// Draw weapon pixel by pixel
	y = 0;
	while (y < weapon_height)
	{
		x = 0;
		while (x < weapon_width)
		{
			// Map screen coordinates to texture coordinates
			tex_x = (x * texture->width) / weapon_width;
			tex_y = (y * texture->height) / weapon_height;
			
			if (tex_x >= 0 && tex_x < (int)texture->width &&
				tex_y >= 0 && tex_y < (int)texture->height)
			{
				color = get_texture_color(texture, tex_x, tex_y);
				
				// Don't draw transparent pixels (alpha channel check)
				if ((color & 0xFF) > 0)
				{
					int screen_x = start_x + x;
					int screen_y = start_y + y;
					
					if (screen_x >= 0 && screen_x < SCREEN_WIDTH &&
						screen_y >= 0 && screen_y < SCREEN_HEIGHT)
						mlx_put_pixel(img, screen_x, screen_y, color);
				}
			}
			x++;
		}
		y++;
	}
}
