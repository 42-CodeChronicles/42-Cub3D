/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:21:19 by aychikhi          #+#    #+#             */
/*   Updated: 2025/11/09 10:01:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	init_tex_data(t_tex_data *tex, t_config *data, t_wall_pos *pos)
{
	t_door	*door;
	double	door_offset;

	tex->texture = get_texture(data, pos->map_y, pos->map_x);
	door_offset = 0.0;
	if (data->map.array_map[pos->map_y][pos->map_x] == 'D')
	{
		door = get_door_state(data, pos->map_x, pos->map_y);
		if (door)
			door_offset = door->open_amount;
	}
	pos->wall_x += door_offset;
	if (pos->wall_x > 1.0)
		pos->wall_x -= 1.0;
	tex->tex_x = (int)(pos->wall_x * tex->texture->width);
	tex->ceiling_color = (data->c[0] << 24) | (data->c[1] << 16)
		| (data->c[2] << 8) | 0xFF;
	tex->floor_color = (data->f[0] << 24) | (data->f[1] << 16)
		| (data->f[2] << 8) | 0xFF;
}

static void	draw_ceiling(mlx_image_t *img, int x, int end, uint32_t color)
{
	int	y;

	y = 0;
	while (y < end)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

static void	draw_wall(mlx_image_t *img, t_draw_params *params, t_tex_data *tex)
{
	double		tex_pos;
	int			tex_y;
	uint32_t	color;
	int			y;

	y = params->wall->draw_start;
	while (y < params->wall->draw_end)
	{
		tex_pos = (y - params->wall->draw_start
				+ params->wall->tex_start_offset)
			/ (double)params->wall->line_height;
		tex_y = (int)(tex_pos * tex->texture->height);
		color = get_texture_color(tex->texture, tex->tex_x, tex_y);
		mlx_put_pixel(img, params->x, y, color);
		y++;
	}
}

static void	draw_floor(mlx_image_t *img, int x, int start, uint32_t color)
{
	int	y;

	y = start;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void	draw_wall_slice_texture(mlx_image_t *img, t_draw_params *params)
{
	t_tex_data	tex;

	init_tex_data(&tex, params->data, params->pos);
	draw_ceiling(img, params->x, params->wall->draw_start, tex.ceiling_color);
	draw_wall(img, params, &tex);
	draw_floor(img, params->x, params->wall->draw_end, tex.floor_color);
}
