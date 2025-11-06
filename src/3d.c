/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:40:10 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/05 18:41:21 by aychikhi         ###   ########.fr       */
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

	perp_distance = distance * cos(ray_angle - data->map.player_pos.angle);
	wall->line_height = (int)((WALL_HEIGHT / perp_distance) * (SCREEN_HEIGHT
				/ 2));
	wall->draw_start = (SCREEN_HEIGHT / 2) - (wall->line_height / 2);
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = (SCREEN_HEIGHT / 2) + (wall->line_height / 2);
	if (wall->draw_end >= SCREEN_HEIGHT)
		wall->draw_end = SCREEN_HEIGHT - 1;
}



static mlx_texture_t	*get_texture(t_config *data)
{
	if (data->wall_side == 0)
		return (data->no_texture);
	else if (data->wall_side == 1)
		return (data->so_texture);
	else if (data->wall_side == 2)
		return (data->ea_texture);
	else
		return (data->we_texture);
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
		t_config *data, double wall_x)
{
	mlx_texture_t	*texture;
	int				tex_x;
	double			tex_pos;
	int				tex_y;
	uint32_t		color;

	texture = get_texture(data);
	tex_x = (int)(wall_x * texture->width);
	for (int y = 0; y < wall->draw_start; y++)
		mlx_put_pixel(img, x, y, 0x87CEEBFF);
	for (int y = wall->draw_start; y < wall->draw_end; y++)
	{
		tex_pos = (y - wall->draw_start) / (double)wall->line_height;
		tex_y = (int)(tex_pos * texture->height);
		color = get_texture_color(texture, tex_x, tex_y);
		mlx_put_pixel(img, x, y, color);
	}
	for (int y = wall->draw_end; y < SCREEN_HEIGHT; y++)
		mlx_put_pixel(img, x, y, 0x2E8B57FF);
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

	fov_rad = (FOV * M_PI) / 180.0;
	angle_step = fov_rad / SCREEN_WIDTH;
	start_angle = data->map.player_pos.angle - (fov_rad / 2);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		ray_angle = start_angle + (x * angle_step);
		distance = cast_ray(data, ray_angle, &hit_vertical, &wall_x);
		calculate_wall_height(&wall, distance, ray_angle, data);
		draw_wall_slice_texture(img, x, &wall, data, wall_x);
	}
}
