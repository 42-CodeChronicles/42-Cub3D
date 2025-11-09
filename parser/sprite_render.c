/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:00:16 by codespace         #+#    #+#             */
/*   Updated: 2025/11/09 10:01:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

typedef struct s_sprite_params
{
	double	dx;
	double	dy;
	double	distance;
	double	angle_to_sprite;
	double	sprite_angle;
	int		screen_x;
	double	sprite_height;
	double	sprite_width;
	int		start_y;
	int		start_x;
	int		end_x;
}	t_sprite_params;

double	get_sprite_distance(t_config *data, t_sprite *sprite)
{
	double	dx;
	double	dy;

	dx = sprite->x - (data->map.player_pos.x / TILE_SIZE);
	dy = sprite->y - (data->map.player_pos.y / TILE_SIZE);
	return (sqrt(dx * dx + dy * dy));
}

static void	init_sprite_params(t_sprite_params *p, t_config *data,
		t_sprite *sprite)
{
	p->dx = sprite->x - (data->map.player_pos.x / TILE_SIZE);
	p->dy = sprite->y - (data->map.player_pos.y / TILE_SIZE);
	p->distance = sqrt(p->dx * p->dx + p->dy * p->dy);
	p->angle_to_sprite = atan2(p->dy, p->dx);
	p->sprite_angle = p->angle_to_sprite - data->map.player_pos.angle;
	while (p->sprite_angle > M_PI)
		p->sprite_angle -= 2 * M_PI;
	while (p->sprite_angle < -M_PI)
		p->sprite_angle += 2 * M_PI;
}

static int	calc_screen_pos(t_sprite_params *p, mlx_texture_t *texture)
{
	double	fov_rad;

	if (p->distance < 0.5 || p->distance > 20.0)
		return (0);
	fov_rad = (FOV * M_PI / 180.0) / 2.0;
	if (fabs(p->sprite_angle) > fov_rad + 0.3)
		return (0);
	p->screen_x = (int)((SCREEN_WIDTH / 2) * (1.0 + tan(p->sprite_angle)
				/ tan(fov_rad)));
	p->sprite_height = (SCREEN_HEIGHT / p->distance) * 0.8;
	p->sprite_width = (texture->width * p->sprite_height) / texture->height;
	p->start_y = (SCREEN_HEIGHT - p->sprite_height) / 2;
	p->start_x = p->screen_x - (p->sprite_width / 2);
	p->end_x = p->start_x + p->sprite_width;
	return (1);
}

static void	draw_sprite_column(mlx_image_t *img, t_sprite_params *p,
		mlx_texture_t *tex, int x)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	if (x >= 0 && x < SCREEN_WIDTH)
	{
		y = p->start_y;
		while (y < p->start_y + p->sprite_height)
		{
			if (y >= 0 && y < SCREEN_HEIGHT)
			{
				tex_x = ((x - p->start_x) * tex->width) / p->sprite_width;
				tex_y = ((y - p->start_y) * tex->height) / p->sprite_height;
				if (tex_x >= 0 && tex_x < (int)tex->width && tex_y >= 0
					&& tex_y < (int)tex->height)
				{
					color = get_texture_color(tex, tex_x, tex_y);
					if ((color & 0xFF) > 0)
						mlx_put_pixel(img, x, y, color);
				}
			}
			y++;
		}
	}
}

void	draw_sprite(mlx_image_t *img, t_config *data, t_sprite *sprite)
{
	t_sprite_params	p;
	mlx_texture_t	*texture;
	int				x;

	texture = sprite->frames[sprite->current_frame];
	init_sprite_params(&p, data, sprite);
	if (!calc_screen_pos(&p, texture))
		return ;
	x = p.start_x;
	while (x < p.end_x)
	{
		draw_sprite_column(img, &p, texture, x);
		x++;
	}
}