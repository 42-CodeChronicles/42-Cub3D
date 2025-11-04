/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:40:10 by ayoub             #+#    #+#             */
/*   Updated: 2025/11/04 04:07:56 by ayaarab          ###   ########.fr       */
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

void	draw_wall_slice(mlx_image_t *img, int x, t_wall *wall, int hit_vertical)
{
	int	y;

	if (hit_vertical)
		wall->color = 0xAAAAAAFF;
	else
		wall->color = 0x777777FF;
	y = 0;
	while (y < wall->draw_start)
	{
		mlx_put_pixel(img, x, y, 0x87CEEBFF);
		y++;
	}
	y = wall->draw_start;
	while (y < wall->draw_end)
	{
		mlx_put_pixel(img, x, y, wall->color);
		y++;
	}
	y = wall->draw_end;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(img, x, y, 0x2E8B57FF);
		y++;
	}
}

void	render_3d_view(mlx_image_t *img, t_config *data)
{
	double fov_rad;
	double angle_step;
	double start_angle;
	double ray_angle;
	int hit_vertical;
	double distance;
	t_wall wall;

	fov_rad = (FOV * M_PI) / 180.0;
	angle_step = fov_rad / SCREEN_WIDTH;
	start_angle = data->map.player_pos.angle - (fov_rad / 2);

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		double wall_x;
		ray_angle = start_angle + (x * angle_step);
		distance = cast_ray(data, ray_angle, &hit_vertical, &wall_x);

		calculate_wall_height(&wall, distance, ray_angle, data);
		draw_wall_slice(img, x, &wall, hit_vertical);
	}
}
