/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:40:10 by ayoub             #+#    #+#             */
/*   Updated: 2025/12/03 19:44:28 by ayaarab          ###   ########.fr       */
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
	t_3d			three_d;
	t_wall			wall;
	t_wall_pos		pos;
	t_draw_params	params;

	three_d.fov_rad = (FOV * M_PI) / 180.0;
	three_d.angle_step = three_d.fov_rad / SCREEN_WIDTH;
	three_d.start_angle = data->map.player_pos.angle - (three_d.fov_rad / 2);
	three_d.x = 0;
	while (three_d.x < SCREEN_WIDTH)
	{
		three_d.ray_angle = three_d.start_angle + (three_d.x
				* three_d.angle_step);
		three_d.distance = cast_ray(data, three_d.ray_angle,
				&three_d.hit_vertical, &pos);
		calculate_wall_height(&wall, three_d.distance, three_d.ray_angle, data);
		params.x = three_d.x;
		params.wall = &wall;
		params.data = data;
		params.pos = &pos;
		draw_wall_slice_texture(img, &params);
		three_d.x++;
	}
}
