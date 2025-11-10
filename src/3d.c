/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:40:10 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/10 01:27:34 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculate_wall_height(t_wall *wall, double distance, double ray_angle,
		t_config *data)
{
	double	perp_distance;
	double	fov_rad;
	double	screen_dist;
	int		original_start;

	perp_distance = distance * cos(ray_angle - data->map.player_pos.angle);
	if (perp_distance < 0.1)
		perp_distance = 0.1;
	fov_rad = (FOV * M_PI) / 180;
	screen_dist = (SCREEN_WIDTH / 2.0) / tan(fov_rad / 2.0);
	wall->line_height = (int)((WALL_HEIGHT * screen_dist) / perp_distance);
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

void	render_3d_view(mlx_image_t *img, t_config *data)
{
	double			fov_rad;
	double			angle_step;
	double			start_angle;
	double			ray_angle;
	int				hit_vertical;
	double			distance;
	t_wall			wall;
	t_wall_pos		pos;
	t_draw_params	params;
	int				x;

	fov_rad = (FOV * M_PI) / 180.0;
	angle_step = fov_rad / SCREEN_WIDTH;
	start_angle = data->map.player_pos.angle - (fov_rad / 2);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_angle = start_angle + (x * angle_step);
		distance = cast_ray(data, ray_angle, &hit_vertical, &pos.wall_x,
				&pos.map_x, &pos.map_y);
		calculate_wall_height(&wall, distance, ray_angle, data);
		params.x = x;
		params.wall = &wall;
		params.data = data;
		params.pos = &pos;
		draw_wall_slice_texture(img, &params);
		x++;
	}
}
