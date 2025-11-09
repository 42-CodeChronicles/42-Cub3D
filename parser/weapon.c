/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:00:00 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 15:55:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

typedef struct s_weapon_draw
{
	int		weapon_width;
	int		weapon_height;
	int		start_x;
	int		start_y;
	int		x;
	int		y;
}			t_weapon_draw;

static void	init_weapon_fields(t_config *data)
{
	data->weapon.frame_count = 6;
	data->weapon.current_frame = 0;
	data->weapon.is_shooting = 0;
	data->weapon.frame_time = 0.05;
	data->weapon.last_update = 0;
}

static int	load_weapon_frames(t_config *data, char **frames)
{
	int	i;

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
	return (1);
}

void	weapon_init(t_config *data)
{
	char	*frames[6];

	frames[0] = "weapon/0.png";
	frames[1] = "weapon/1.png";
	frames[2] = "weapon/2.png";
	frames[3] = "weapon/3.png";
	frames[4] = "weapon/4.png";
	frames[5] = "weapon/5.png";
	init_weapon_fields(data);
	data->weapon.frames = malloc(sizeof(mlx_texture_t *) * 6);
	if (!data->weapon.frames)
	{
		printf("Error: Failed to allocate memory for weapon frames\n");
		exit(1);
	}
	load_weapon_frames(data, frames);
	printf("Weapon loaded successfully with %d frames\n",
		data->weapon.frame_count);
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

static void	draw_weapon_pixel(mlx_image_t *img, t_weapon_draw *wd,
		mlx_texture_t *texture)
{
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	int			screen_x;
	int			screen_y;

	tex_x = (wd->x * texture->width) / wd->weapon_width;
	tex_y = (wd->y * texture->height) / wd->weapon_height;
	if (tex_x >= 0 && tex_x < (int)texture->width && tex_y >= 0
		&& tex_y < (int)texture->height)
	{
		color = get_texture_color(texture, tex_x, tex_y);
		if ((color & 0xFF) > 0)
		{
			screen_x = wd->start_x + wd->x;
			screen_y = wd->start_y + wd->y;
			if (screen_x >= 0 && screen_x < SCREEN_WIDTH && screen_y >= 0
				&& screen_y < SCREEN_HEIGHT)
				mlx_put_pixel(img, screen_x, screen_y, color);
		}
	}
}

void	draw_weapon(mlx_image_t *img, t_config *data)
{
	t_weapon_draw	wd;
	mlx_texture_t	*texture;

	texture = data->weapon.frames[data->weapon.current_frame];
	get_weapon_dimensions(texture, &wd.weapon_width, &wd.weapon_height);
	get_weapon_position(wd.weapon_width, wd.weapon_height, &wd.start_x,
		&wd.start_y);
	wd.y = 0;
	while (wd.y < wd.weapon_height)
	{
		wd.x = 0;
		while (wd.x < wd.weapon_width)
		{
			draw_weapon_pixel(img, &wd, texture);
			wd.x++;
		}
		wd.y++;
	}
}
