/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:39:52 by aychikhi          #+#    #+#             */
/*   Updated: 2025/10/24 10:45:09 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

uint32_t	get_pixel_color(mlx_texture_t *texture, int x, int y)
{
	int	index;
	int	r;
	int	g;
	int	b;
	int	a;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	index = (y * texture->width + x) * 4;
	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

mlx_texture_t	*get_wall_texture(t_config *data, t_ray *ray)
{
	double	ray_angle;

	ray_angle = ray->angle;
	normalize_angle(&ray_angle);
	if (ray->hit_vertical)
	{
		if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
			return (data->w_texture);
		else
			return (data->e_texture);
	}
	else
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			return (data->s_texture);
		else
			return (data->n_texture);
	}
}

void	render_3d_view(mlx_image_t *img, t_config *data)
{
	double	fov_rad;
	double	angle_step;
	double	start_angle;
	t_ray	ray;
	int		x;

	fov_rad = (FOV * M_PI) / 180.0;
	angle_step = fov_rad / SCREEN_WIDTH;
	start_angle = data->map.player_pos.angle - (fov_rad / 2);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray.angle = start_angle + (x * angle_step);
		ray.distance = cast_ray(data, ray.angle, &ray.hit_vertical);
		calculate_wall_height(&ray.wall, ray.distance, ray.angle, data);
		draw_wall_slice(data, img, &ray, x);
		x++;
	}
}
