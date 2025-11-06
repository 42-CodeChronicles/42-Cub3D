/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:21:19 by aychikhi          #+#    #+#             */
/*   Updated: 2025/11/06 18:21:41 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static mlx_texture_t	*get_texture(t_config *data, int y, int x)
{
	if (data->map.array_map[y][x] == 'D')
		return (data->door_texture);
	if (data->wall_side == 0)
		return (data->no_texture);
	else if (data->wall_side == 1)
		return (data->so_texture);
	else if (data->wall_side == 2)
		return (data->ea_texture);
	else
		return (data->we_texture);
}

t_door	*get_door_state(t_config *data, int x, int y)
{
	int	i;

	if (!data->doors)
		return (NULL);
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

static uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	int		index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)texture->height)
		tex_y = texture->height - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	index = (tex_y * texture->width + tex_x) * 4;
	r = texture->pixels[index + 0];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

typedef struct s_tex_data
{
	mlx_texture_t	*texture;
	int				tex_x;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
}	t_tex_data;

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
