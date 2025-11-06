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

void	draw_wall_slice_texture(mlx_image_t *img, int x, t_wall *wall,
		t_config *data, double wall_x, int map_x, int map_y)
{
	mlx_texture_t	*texture;
	int				tex_x;
	double			tex_pos;
	int				tex_y;
	uint32_t		color;
	t_door			*door;
	double			door_offset;
	uint32_t		ceiling_color;
	uint32_t		floor_color;

	texture = get_texture(data, map_y, map_x);
	door_offset = 0.0;
	if (data->map.array_map[map_y][map_x] == 'D')
	{
		door = get_door_state(data, map_x, map_y);
		if (door)
			door_offset = door->open_amount;
	}
	wall_x += door_offset;
	if (wall_x > 1.0)
		wall_x -= 1.0;
	tex_x = (int)(wall_x * texture->width);
	ceiling_color = (data->c[0] << 24) | (data->c[1] << 16) | (data->c[2] << 8) | 0xFF;
	floor_color = (data->f[0] << 24) | (data->f[1] << 16) | (data->f[2] << 8) | 0xFF;
	for (int y = 0; y < wall->draw_start; y++)
		mlx_put_pixel(img, x, y, ceiling_color);
	for (int y = wall->draw_start; y < wall->draw_end; y++)
	{
		tex_pos = (y - wall->draw_start + wall->tex_start_offset)
			/ (double)wall->line_height;
		tex_y = (int)(tex_pos * texture->height);
		color = get_texture_color(texture, tex_x, tex_y);
		mlx_put_pixel(img, x, y, color);
	}
	for (int y = wall->draw_end; y < SCREEN_HEIGHT; y++)
		mlx_put_pixel(img, x, y, floor_color);
}
