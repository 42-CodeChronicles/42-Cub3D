/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:40:10 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/06 16:29:34 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// void	calculate_wall_height(t_wall *wall, double distance, double ray_angle,
// 		t_config *data)
// {
// 	double	perp_distance;
// 	double fov_rad;
// 	double screen_dist;

// 	perp_distance = distance * cos(ray_angle - data->map.player_pos.angle);
// 	fov_rad = (FOV * M_PI) / 180;
// 	screen_dist = (SCREEN_WIDTH / 2.0) / tan(fov_rad / 2.0);

// 	wall->line_height = (int)((WALL_HEIGHT * screen_dist) / perp_distance);

// 	wall->draw_start = (SCREEN_HEIGHT / 2) - (wall->line_height / 2);
// 	if (wall->draw_start < 0)
// 		wall->draw_start = 0;
// 	wall->draw_end = (SCREEN_HEIGHT / 2) + (wall->line_height / 2);
// 	if (wall->draw_end >= SCREEN_HEIGHT)
// 		wall->draw_end = SCREEN_HEIGHT - 1;
// }
void	calculate_wall_height(t_wall *wall, double distance, double ray_angle,
		t_config *data)
{
	double	perp_distance;
	int		original_start;

	perp_distance = distance * cos(ray_angle - data->map.player_pos.angle);
	wall->line_height = (int)((WALL_HEIGHT / perp_distance) * (SCREEN_HEIGHT
				/ 2));
	original_start = (SCREEN_HEIGHT / 2) - (wall->line_height / 2);
	wall->draw_start = original_start;
	wall->tex_start_offset = 0;
	if (wall->draw_start < 0)
	{
		wall->tex_start_offset = -wall->draw_start;
		wall->draw_start = 0;
	}
	wall->draw_end = (SCREEN_HEIGHT / 2) + (wall->line_height / 2);
	if (wall->draw_end >= SCREEN_HEIGHT)
		wall->draw_end = SCREEN_HEIGHT - 1;
}

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

t_door *get_door_state(t_config *data, int x, int y)
{
    int i;
    
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
	for (int y = 0; y < wall->draw_start; y++)
		mlx_put_pixel(img, x, y, 0x0000ff);
	for (int y = wall->draw_start; y < wall->draw_end; y++)
	{
		tex_pos = (y - wall->draw_start + wall->tex_start_offset)
			/ (double)wall->line_height;
		tex_y = (int)(tex_pos * texture->height);
		color = get_texture_color(texture, tex_x, tex_y);
		mlx_put_pixel(img, x, y, color);
	}
	for (int y = wall->draw_end; y < SCREEN_HEIGHT; y++)
		mlx_put_pixel(img, x, y, 0x000000);
}

void	render_3d_view(mlx_image_t *img, t_config *data)
{
	double	fov_rad;
	double	angle_step;
	double	start_angle;
	double	ray_angle;
	int		hit_vertical;
	double	distance;
	t_wall	wall;
	double	wall_x;
	int		map_x;
	int		map_y;

	fov_rad = (FOV * M_PI) / 180.0;
	angle_step = fov_rad / SCREEN_WIDTH;
	start_angle = data->map.player_pos.angle - (fov_rad / 2);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		ray_angle = start_angle + (x * angle_step);
		distance = cast_ray(data, ray_angle, &hit_vertical, &wall_x, &map_x, &map_y);
		calculate_wall_height(&wall, distance, ray_angle, data);
		draw_wall_slice_texture(img, x, &wall, data, wall_x, map_x, map_y);
	}
}
